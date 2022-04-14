#include "Base.h"

#include <iosfwd>
#include <cmath>

#include "ArcBallCameraComponent.h"

#include "Game/Game.h"
#include "Maths/Matrix4.h"
#include "StringUtils.h"
#include "Entities/ComponentTypeEnum.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"
#include "Game/Input.h"

namespace CasaEngine
{
	ArcBallCameraComponent::ArcBallCameraComponent(BaseEntity* pEntity_)
		: Camera3DComponent(pEntity_, CAMERA_ARC_BALL),
		m_fDistance(5.0f),
		m_fInputDistanceRate(3.0f),
		m_fInputTurnRate(0.06f),
		m_fInputDisplacementRate(2.0f),
		m_fArcBallPitch(0.0f),
		m_fArcBallYaw(PI)
	{
		//orientation quaternion assumes a PI rotation so you're facing the "front"
		//of the model (looking down the +Z axis)
		m_ArcBallOrientation.FromAxisAngle(Vector3::Up(), PI);
		m_Target = Vector3::Zero();
	}

	void ArcBallCameraComponent::Initialize()
	{

	}

	void ArcBallCameraComponent::Update(const GameTime& gameTime_)
	{
		float rightAxis = 0.0f;
		float upAxis = 0.0f;
		float forwardAxis = 0.0f;
		float horizontalOrbit = 0.0f;
		float verticalOrbit = 0.0f;
		float rollOrbit = 0.0f;
		float zoom = 0.0f;

		const float step = 1.0f;

		//Keyboard
		if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Right) == true)
		{
			rightAxis = step;
		}
		else if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Left) == true)
		{
			rightAxis = -step;
		}

		if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Up) == true)
		{
			forwardAxis = step;
		}
		else if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Down) == true)
		{
			forwardAxis = -step;
		}

		if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::PageUp) == true)
		{
			upAxis = step;
		}
		else if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::PageDown) == true)
		{
			upAxis = -step;
		}

		if (Game::Instance().GetInput().IsMouseButtonDown(sf::Mouse::Right) == true)
		{
			horizontalOrbit = static_cast<float>(-Game::Instance().GetInput().GetDeltaMouseX());
			verticalOrbit = static_cast<float>(-Game::Instance().GetInput().GetDeltaMouseY());
		}

		//Touch
		if (Game::Instance().GetInput().IsTouchMove(0) == true)
		{
			horizontalOrbit = -Game::Instance().GetInput().TouchMoveDeltaX(0);
			verticalOrbit = -Game::Instance().GetInput().TouchMoveDeltaY(0);
			CA_TRACE("TouchMove x:%f y=%f\n", horizontalOrbit, verticalOrbit);
		}

		//
		HandleControls(gameTime_, rightAxis, upAxis, forwardAxis, horizontalOrbit, verticalOrbit, rollOrbit, zoom);
	}

	/**
	 * <param name="gameTime"></param>
	 * <param name="horizontalAxis_"> value between -1.0 and 1.0 </param>
	 * <param name="verticalAxis_"> value between -1.0 and 1.0 </param>
	 * <param name="rollAxis_"> value between -1.0 and 1.0 </param>
	 * <param name="zoom"> zoom value </param>
	*/
	void ArcBallCameraComponent::HandleControls(const GameTime& gameTime_,
		float rightAxis_, float upAxis_, float forwardAxis_,
		float horizontalOrbit_, float verticalOrbit_, float rollOrbit_, float zoom_)
	{
		float r = rightAxis_ * gameTime_.FrameTime() * m_fInputDisplacementRate;
		float u = upAxis_ * gameTime_.FrameTime() * m_fInputDisplacementRate;
		float f = forwardAxis_ * gameTime_.FrameTime() * m_fInputDisplacementRate;

		float dH = horizontalOrbit_ * gameTime_.FrameTime() * m_fInputTurnRate;
		float dV = verticalOrbit_ * gameTime_.FrameTime() * m_fInputTurnRate;
		//float dR = rollOrbit_ * gameTime_.FrameTime() * m_fInputTurnRate;

		if (dH != 0.0f)
		{
			RotateTargetRight(dH);
			OrbitRight(dH);
		}
		if (dV != 0.0f)
		{
			RotateTargetUp(dV);
			OrbitUp(-dV);
		}
		//if ( dR != 0.0f ) RotateClockwise( dR );

		//decrease distance to target
		m_fDistance += zoom_ * gameTime_.FrameTime() * m_fInputDistanceRate;

		if (m_fDistance < 0.001f)
		{
			m_fDistance = 0.001f;
		}

		if (r != 0.0f || u != 0.0f || f != 0.0f)
		{
			Vector3 pos = Target() + Right() * r + Up() * u + Direction() * f;
			Target(pos);
		}

		m_needToComputeViewMatrix = true;
	}

	float ArcBallCameraComponent::ArcBallPitch() const
	{
		return m_fArcBallPitch;
	}

	void ArcBallCameraComponent::ArcBallPitch(float val)
	{
		m_fArcBallPitch = val;
		m_needToComputeViewMatrix = true;
		Quaternion q1, q2;
		q1.FromAxisAngle(Vector3::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3::Right(), m_fArcBallPitch);
		m_ArcBallOrientation = q1 * q2;
	}

	float ArcBallCameraComponent::ArcBallYaw() const
	{
		return m_fArcBallYaw;
	}

	void ArcBallCameraComponent::ArcBallYaw(float val)
	{
		m_fArcBallYaw = val;
		m_needToComputeViewMatrix = true;
		Quaternion q1, q2;
		q1.FromAxisAngle(Vector3::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3::Right(), m_fArcBallPitch);
		m_ArcBallOrientation = q1 * q2;
	}

	Vector3 ArcBallCameraComponent::Direction() const
	{
		//R v R' where v = (0,0,-1,0)
		//The equation can be reduced because we know the following things:
		//  1.  We're using unit quaternions
		//  2.  The initial aspect does not change
		//The reduced form of the same equation follows
		Vector3 dir = Vector3::Zero();
		dir.x = -2.0f * (m_ArcBallOrientation.x * m_ArcBallOrientation.z + m_ArcBallOrientation.w * m_ArcBallOrientation.y);
		dir.y = 2.0f * (m_ArcBallOrientation.w * m_ArcBallOrientation.x - m_ArcBallOrientation.y * m_ArcBallOrientation.z);
		dir.z =
			m_ArcBallOrientation.x * m_ArcBallOrientation.x + m_ArcBallOrientation.y * m_ArcBallOrientation.y -
			(m_ArcBallOrientation.z * m_ArcBallOrientation.z + m_ArcBallOrientation.w * m_ArcBallOrientation.w);
		dir.Normalize();
		return dir;
	}

	Vector3 ArcBallCameraComponent::Right() const
	{
		//R v R' where v = (1,0,0,0)
		//The equation can be reduced because we know the following things:
		//  1.  We're using unit quaternions
		//  2.  The initial aspect does not change
		//The reduced form of the same equation follows
		Vector3 right = Vector3::Zero();
		right.x = 
			m_ArcBallOrientation.x * m_ArcBallOrientation.x + m_ArcBallOrientation.w * m_ArcBallOrientation.w -
			(m_ArcBallOrientation.z * m_ArcBallOrientation.z + m_ArcBallOrientation.y * m_ArcBallOrientation.y);
		right.y = 2.0f * (m_ArcBallOrientation.x * m_ArcBallOrientation.y + m_ArcBallOrientation.z * m_ArcBallOrientation.w);
		right.z = 2.0f * (m_ArcBallOrientation.x * m_ArcBallOrientation.z - m_ArcBallOrientation.y * m_ArcBallOrientation.w);

		return right;
	}

	Vector3 ArcBallCameraComponent::Up() const
	{
		//R v R' where v = (0,1,0,0)
		//The equation can be reduced because we know the following things:
		//  1.  We're using unit quaternions
		//  2.  The initial aspect does not change
		//The reduced form of the same equation follows
		Vector3 up = Vector3::Zero();
		up.x = 2.0f * (m_ArcBallOrientation.x * m_ArcBallOrientation.y - m_ArcBallOrientation.z * m_ArcBallOrientation.w);
		up.y =
			m_ArcBallOrientation.y * m_ArcBallOrientation.y + m_ArcBallOrientation.w * m_ArcBallOrientation.w -
			(m_ArcBallOrientation.z * m_ArcBallOrientation.z + m_ArcBallOrientation.x * m_ArcBallOrientation.x);
		up.z = 2.0f * (m_ArcBallOrientation.y * m_ArcBallOrientation.z + m_ArcBallOrientation.x * m_ArcBallOrientation.w);
		return up;
	}

	Vector3 ArcBallCameraComponent::Position() const
	{
		return m_Target - Direction() * m_fDistance;
	}

	void ArcBallCameraComponent::Position(Vector3 val_)
	{
		SetCamera(val_, m_Target, Up());
	}

	void ArcBallCameraComponent::ComputeViewMatrix()
	{
		const auto position = m_Target - Direction() * m_fDistance;
		m_ViewMatrix = Matrix4::CreateLookAt(position, m_Target, Up());
	}

	Vector3 ArcBallCameraComponent::Target() const
	{
		return m_Target;
	}

	void ArcBallCameraComponent::Target(Vector3 val)
	{
		m_needToComputeViewMatrix = true;
		m_Target = val;
	}

	float ArcBallCameraComponent::Distance() const
	{
		return m_fDistance;
	}

	void ArcBallCameraComponent::Distance(float val)
	{
		m_fDistance = val;
		m_needToComputeViewMatrix = true;
	}

	float ArcBallCameraComponent::InputDistanceRate() const
	{
		return m_fInputDistanceRate;
	}

	void ArcBallCameraComponent::InputDistanceRate(float val)
	{
		m_fInputDistanceRate = val;
	}

	float ArcBallCameraComponent::InputDisplacementRate() const
	{
		return m_fInputDisplacementRate;
	}

	void ArcBallCameraComponent::InputDisplacementRate(float val)
	{
		m_fInputDisplacementRate = val;
	}

	/// <summary>
	/// Orbit directly upwards in Free camera or on
	/// the longitude line when roll constrained
	/// </summary>
	void ArcBallCameraComponent::OrbitUp(float angle)
	{
		m_needToComputeViewMatrix = true;

		Quaternion q1, q2;

		//update the yaw
		m_fArcBallPitch -= angle;

		//constrain pitch to vertical to avoid confusion
		Clamp<float, float, float>(
			m_fArcBallPitch,
			-PI_OVER_2 + 0.0001f,
			PI_OVER_2 - 0.0001f);

		q1.FromAxisAngle(Vector3::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3::Right(), m_fArcBallPitch);
		//create a new aspect based on pitch and yaw
		m_ArcBallOrientation = q1 * q2;
		//normalize to reduce errors
		//orientation.Normalize(); ??
	}

	/// <summary>
	/// Orbit towards the Right vector in Free camera
	/// or on the latitude line when roll constrained
	/// </summary>
	void ArcBallCameraComponent::OrbitRight(float angle)
	{
		m_needToComputeViewMatrix = true;

		Quaternion q1, q2;

		//update the yaw
		m_fArcBallYaw -= angle;

		//float mod yaw to avoid eventual precision errors
		//as we move away from 0
		m_fArcBallYaw = fmod(m_fArcBallYaw, MATH_2PI);

		q1.FromAxisAngle(Vector3::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3::Right(), m_fArcBallPitch);
		//create a new aspect based on pitch and yaw
		m_ArcBallOrientation = q1 * q2;
		//normalize to reduce errors
		m_ArcBallOrientation.Normalize();
	}

	/// <summary>
	/// Rotate around the Forward vector 
	/// in free-look camera only
	/// </summary>
	void ArcBallCameraComponent::RotateClockwise(float /*angle*/)
	{
		/*
		m_bRecomputeViewMatrix = true;

		Quaternion q1;

		q1.FromAxisAngle(Vector3::Forward(), angle);
		//rotate the aspect by the angle
		m_ArcBallOrientation = m_ArcBallOrientation * q1;
		//normalize to reduce errors
		//m_ArcBallOrientation.Normalize();
		*/
	}

	void ArcBallCameraComponent::RotateTargetUp(float angle_)
	{
		m_needToComputeViewMatrix = true;

		Quaternion rot;
		rot.FromAxisAngle(Right(), angle_);
		Vector3 dir = Direction() * m_fDistance;
		Vector3 vec;
		rot.Transform(dir, vec);
		//Vector3::Transform(dir, rot, vec);
		m_Target += vec - dir;

		//OrbitUp(-angle_);
	}

	void ArcBallCameraComponent::RotateTargetRight(float angle_)
	{
		m_needToComputeViewMatrix = true;

		Quaternion rot;
		rot.FromAxisAngle(Up(), angle_);
		Vector3 dir = Direction() * m_fDistance;
		Vector3 vec;
		rot.Transform(dir, vec);
		//Vector3::Transform(dir, rot, vec);
		m_Target += vec - dir;

		//OrbitRight(angle_);
	}

	void ArcBallCameraComponent::SetCamera(Vector3 position, Vector3 target, Vector3 up)
	{
		m_needToComputeViewMatrix = true;

		Matrix4 temp = Matrix4::CreateLookAt(position, target, up);
		temp = Matrix4::Invert(temp);
		m_ArcBallOrientation.FromMatrix(temp);

		m_Target = target;
		m_fDistance = (target - position).Length();

		//When setting a new eye-view direction 
		//in one of the gamble-locked modes, the yaw and
		//pitch gimble must be calculated.

		//first, get the direction projected on the x/z plne
		Vector3 dir = Direction();
		dir.y = 0.0f;
		if (dir.Length() == 0.0f)
		{
			dir = Vector3::Forward();
		}
		dir.Normalize();

		//find the yaw of the direction on the x/z plane
		//and use the sign of the x-component since we have 360 degrees
		//of freedom
		//m_fArcBallYaw = ;
		ArcBallYaw(acosf(-dir.z) * Sign(dir.x));

		//Get the pitch from the angle formed by the Up vector and the 
		//the forward direction, then subtracting PI / 2, since 
		//we pitch is zero at Forward, not Up.
		//m_fArcBallPitch = ;
		ArcBallPitch(-(acosf(Vector3::Dot(Up(), Direction())) - PI_OVER_2));
	}

	void ArcBallCameraComponent::Write(std::ostream& /*os*/) const
	{

	}

	void ArcBallCameraComponent::Read(std::ifstream& /*is*/)
	{

	}
}
