#include "Base.h"

#include <iosfwd>
#include <string>
#include <math.h>

#include "ArcBallCameraController.h"
#include "CameraController.h"
#include "Game/Game.h"
#include "Maths/Matrix4.h"
#include "StringUtils.h"
#include "Entities/Components/Camera3DComponent.h"
#include "Maths/Math.h"
#include "Maths/Quaternion.h"
#include "Game/GameInfo.h"
#include "Game/Input.h"

namespace CasaEngine
{

	/**
	 *
	 */
	ArcBallCameraController::ArcBallCameraController(CameraComponent* pCamera)
		: ICameraController(pCamera)
	{
		m_fInputTurnRate = 0.5f;
		m_fInputDisplacementRate = 2.0f;

		m_fInputDistanceRate = 4.0f;
		m_bRecomputeViewMatrix = true;

		ReInit();
	}

	/**
	 *
	 */
	ArcBallCameraController::~ArcBallCameraController()
	{
	}

	/**
	 *
	 */
	void ArcBallCameraController::Initialize()
	{
	}

	/**
	 *
	 */
	void ArcBallCameraController::Update(const GameTime& gameTime_)
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
			rightAxis = -step;
		}
		else if (Game::Instance().GetInput().IsKeyDown(sf::Keyboard::Left) == true)
		{
			rightAxis = step;
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

		if (Game::Instance().GetInput().IsMouseButtonDown(sf::Mouse::Middle) == true)
		{
			horizontalOrbit = (float)-Game::Instance().GetInput().GetDeltaMouseX();
			verticalOrbit = (float)-Game::Instance().GetInput().GetDeltaMouseY();
		}

		//Touch
		if (Game::Instance().GetInput().IsTouchMove(0) == true)
		{
			horizontalOrbit = (float)-Game::Instance().GetInput().TouchMoveDeltaX(0);
			verticalOrbit = (float)-Game::Instance().GetInput().TouchMoveDeltaY(0);
			CA_TRACE("TouchMove x:%f y=%f\n", horizontalOrbit, verticalOrbit);
		}

		//
		HandleControls(gameTime_, rightAxis, upAxis, forwardAxis,
			horizontalOrbit, verticalOrbit, rollOrbit, zoom);
	}

	/**
	 * <param name="gameTime"></param>
	 * <param name="horizontalAxis_"> value between -1.0 and 1.0 </param>
	 * <param name="verticalAxis_"> value between -1.0 and 1.0 </param>
	 * <param name="rollAxis_"> value between -1.0 and 1.0 </param>
	 * <param name="zoom"> zoom value </param>
	*/
	void ArcBallCameraController::HandleControls(const GameTime& gameTime_,
		float rightAxis_, float upAxis_, float forwardAxis_,
		float horizontalOrbit_, float verticalOrbit_, float /*rollOrbit_*/, float zoom_)
	{
		float r = rightAxis_ * gameTime_.FrameTime() * m_fInputDisplacementRate;
		float u = upAxis_ * gameTime_.FrameTime() * m_fInputDisplacementRate;
		float f = forwardAxis_ * gameTime_.FrameTime() * m_fInputDisplacementRate;

		float dH = horizontalOrbit_ * gameTime_.FrameTime() * m_fInputTurnRate;
		float dV = verticalOrbit_ * gameTime_.FrameTime() * m_fInputTurnRate;
		//float dR = rollOrbit_ * gameTime_.FrameTime() * m_fInputTurnRate;

		if (dH != 0.0f) RotateTargetRight(dH);//OrbitUp( dH );
		if (dV != 0.0f) RotateTargetUp(dV); //OrbitRight( dV );
		//if ( dR != 0.0f ) RotateClockwise( dR );

		//decrease distance to target
		m_fDistance += zoom_ * gameTime_.FrameTime() * m_fInputDistanceRate;

		if (m_fDistance < 0.001f) m_fDistance = 0.001f;

		if (r != 0.0f || u != 0.0f || f != 0.0f)
		{
			Vector3F pos = Target() + (Right() * r) + (Up() * u) + (Direction() * f);
			Target(pos);

			/*Vector3F target = pos;
			target.Normalize();
			target *= m_fDistance;
			target += pos;

			SetCamera(pos, target, Up());*/
		}
	}

	/**
	 * Reset the camera to the defaults set in the constructor
	 */
	void ArcBallCameraController::ReInit()
	{
		//orientation quaternion assumes a Pi rotation so you're facing the "front"
		//of the model (looking down the +Z axis)
		m_ArcBallOrientation.FromAxisAngle(Vector3F::Up(), Pi);
		m_Target = Vector3F::Zero();
		m_fDistance = 5.0f;
		m_fArcBallYaw = Pi;
		m_fArcBallPitch = 0.0f;
	}

	/**
	 *
	 */
	 /*void ArcBallCameraController::HandleEvent(const Event* pEvent_)
	 {

	 }*/

	 /**
	  *
	  */
	float ArcBallCameraController::ArcBallPitch() const
	{
		return m_fArcBallPitch;
	}

	/**
	 *
	 */
	void ArcBallCameraController::ArcBallPitch(float val)
	{
		m_fArcBallPitch = val;
		m_bRecomputeViewMatrix = true;
		Quaternion q1, q2;
		q1.FromAxisAngle(Vector3F::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3F::Right(), m_fArcBallPitch);
		m_ArcBallOrientation = q1 * q2;
	}

	/**
	 *
	 */
	float ArcBallCameraController::ArcBallYaw() const
	{
		return m_fArcBallYaw;
	}

	/**
	 *
	 */
	void ArcBallCameraController::ArcBallYaw(float val)
	{
		m_fArcBallYaw = val;
		m_bRecomputeViewMatrix = true;
		Quaternion q1, q2;
		q1.FromAxisAngle(Vector3F::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3F::Right(), m_fArcBallPitch);
		m_ArcBallOrientation = q1 * q2;
	}

	/**
	 *
	 */
	Vector3F ArcBallCameraController::Direction() const
	{
		//R v R' where v = (0,0,-1,0)
		//The equation can be reduced because we know the following things:
		//  1.  We're using unit quaternions
		//  2.  The initial aspect does not change
		//The reduced form of the same equation follows
		Vector3F dir = Vector3F::Zero();
		dir.x = -2.0f *
			((m_ArcBallOrientation.x * m_ArcBallOrientation.z) + (m_ArcBallOrientation.w * m_ArcBallOrientation.y));
		dir.y = 2.0f *
			((m_ArcBallOrientation.w * m_ArcBallOrientation.x) - (m_ArcBallOrientation.y * m_ArcBallOrientation.z));
		dir.z =
			((m_ArcBallOrientation.x * m_ArcBallOrientation.x) + (m_ArcBallOrientation.y * m_ArcBallOrientation.y)) -
			((m_ArcBallOrientation.z * m_ArcBallOrientation.z) + (m_ArcBallOrientation.w * m_ArcBallOrientation.w));
		dir.Normalize();
		return dir;
	}

	/**
	 *
	 */
	CasaEngine::Vector3F ArcBallCameraController::Right() const
	{
		//R v R' where v = (1,0,0,0)
		//The equation can be reduced because we know the following things:
		//  1.  We're using unit quaternions
		//  2.  The initial aspect does not change
		//The reduced form of the same equation follows
		Vector3F right = Vector3F::Zero();
		right.x =
			((m_ArcBallOrientation.x * m_ArcBallOrientation.x) + (m_ArcBallOrientation.w * m_ArcBallOrientation.w)) -
			((m_ArcBallOrientation.z * m_ArcBallOrientation.z) + (m_ArcBallOrientation.y * m_ArcBallOrientation.y));
		right.y = 2.0f *
			((m_ArcBallOrientation.x * m_ArcBallOrientation.y) + (m_ArcBallOrientation.z * m_ArcBallOrientation.w));
		right.z = 2.0f *
			((m_ArcBallOrientation.x * m_ArcBallOrientation.z) - (m_ArcBallOrientation.y * m_ArcBallOrientation.w));

		return right;
	}

	/**
	 *
	 */
	CasaEngine::Vector3F ArcBallCameraController::Up() const
	{
		//R v R' where v = (0,1,0,0)
		//The equation can be reduced because we know the following things:
		//  1.  We're using unit quaternions
		//  2.  The initial aspect does not change
		//The reduced form of the same equation follows
		Vector3F up = Vector3F::Zero();
		up.x = 2.0f *
			((m_ArcBallOrientation.x * m_ArcBallOrientation.y) - (m_ArcBallOrientation.z * m_ArcBallOrientation.w));
		up.y =
			((m_ArcBallOrientation.y * m_ArcBallOrientation.y) + (m_ArcBallOrientation.w * m_ArcBallOrientation.w)) -
			((m_ArcBallOrientation.z * m_ArcBallOrientation.z) + (m_ArcBallOrientation.x * m_ArcBallOrientation.x));
		up.z = 2.0f *
			((m_ArcBallOrientation.y * m_ArcBallOrientation.z) + (m_ArcBallOrientation.x * m_ArcBallOrientation.w));
		return up;
	}

	/**
	 *
	 */
	Vector3F ArcBallCameraController::Position() const
	{
		return m_Target - (Direction() * m_fDistance);
	}

	/**
	 *
	 */
	void ArcBallCameraController::Position(Vector3F val_)
	{
		SetCamera(val_, m_Target, Up());
	}

	/**
	 *
	 */
	void ArcBallCameraController::ViewMatrix(Matrix4& viewMatrix_)
	{
		if (m_bRecomputeViewMatrix == true)
		{
			m_bRecomputeViewMatrix = false;
			viewMatrix_.LookAt(m_Target - (Direction() * m_fDistance), m_Target, Up());
		}
	}


	void ArcBallCameraController::ProjectionMatrix(Matrix4& projectionMatrix_)
	{
		auto& viewport = this->Camera()->GetViewport();

		float ratio = static_cast<float>(viewport.Width() * Game::Instance().GetWindowSize().x) /
			static_cast<float>(viewport.Height() * Game::Instance().GetWindowSize().y);

		projectionMatrix_.PerspectiveFOV(
			dynamic_cast<Camera3DComponent*>(Camera())->FOV(),
			ratio/*m_Viewport.AspectRatio()*/,
			viewport.NearClipPlane(),
			viewport.FarClipPlane());
	}

	Vector3F ArcBallCameraController::Target() const
	{
		return m_Target;
	}
	
	void ArcBallCameraController::Target(CasaEngine::Vector3F val)
	{
		m_bRecomputeViewMatrix = true;
		m_Target = val;
	}
	
	float ArcBallCameraController::Distance() const
	{
		return m_fDistance;
	}
	
	void ArcBallCameraController::Distance(float val)
	{
		m_fDistance = val;
		m_bRecomputeViewMatrix = true;
	}
	
	float ArcBallCameraController::InputDistanceRate() const
	{
		return m_fInputDistanceRate;
	}
	
	void ArcBallCameraController::InputDistanceRate(float val)
	{
		m_fInputDistanceRate = val;
	}

	/// <summary>
	/// Orbit directly upwards in Free camera or on
	/// the longitude line when roll constrained
	/// </summary>
	void ArcBallCameraController::OrbitUp(float angle)
	{
		m_bRecomputeViewMatrix = true;

		Quaternion q1, q2;

		//update the yaw
		m_fArcBallPitch -= angle;

		//constrain pitch to vertical to avoid confusion
		Clamp<float, float, float>(
			m_fArcBallPitch,
			-(MATH_PI_DIV_2)+0.0001f,
			(MATH_PI_DIV_2)-0.0001f);

		q1.FromAxisAngle(Vector3F::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3F::Right(), m_fArcBallPitch);
		//create a new aspect based on pitch and yaw
		m_ArcBallOrientation = q1 * q2;
		//normalize to reduce errors
		//orientation.Normalize(); ??
	}

	/// <summary>
	/// Orbit towards the Right vector in Free camera
	/// or on the latitude line when roll constrained
	/// </summary>
	void ArcBallCameraController::OrbitRight(float angle)
	{
		m_bRecomputeViewMatrix = true;

		Quaternion q1, q2;

		//update the yaw
		m_fArcBallYaw -= angle;

		//float mod yaw to avoid eventual precision errors
		//as we move away from 0
		m_fArcBallYaw = fmod(m_fArcBallYaw, MATH_2PI);

		q1.FromAxisAngle(Vector3F::Up(), -m_fArcBallYaw);
		q2.FromAxisAngle(Vector3F::Right(), m_fArcBallPitch);
		//create a new aspect based on pitch and yaw
		m_ArcBallOrientation = q1 * q2;
		//normalize to reduce errors
		m_ArcBallOrientation.Normalize();
	}

	/// <summary>
	/// Rotate around the Forward vector 
	/// in free-look camera only
	/// </summary>
	void ArcBallCameraController::RotateClockwise(float /*angle*/)
	{
		/*
		m_bRecomputeViewMatrix = true;

		Quaternion q1;

		q1.FromAxisAngle(Vector3F::Forward(), angle);
		//rotate the aspect by the angle
		m_ArcBallOrientation = m_ArcBallOrientation * q1;
		//normalize to reduce errors
		//m_ArcBallOrientation.Normalize();
		*/
	}

	/**
	 *
	 */
	void ArcBallCameraController::RotateTargetUp(float angle_)
	{
		m_bRecomputeViewMatrix = true;

		Quaternion rot;
		rot.FromAxisAngle(Right(), angle_);
		Vector3F dir = Direction() * m_fDistance;
		Vector3F vec;
		rot.Transform(dir, vec);
		//Vector3F::Transform(dir, rot, vec);
		m_Target += vec - dir;

		OrbitUp(-angle_);
	}

	/**
	 *
	 */
	void ArcBallCameraController::RotateTargetRight(float angle_)
	{
		m_bRecomputeViewMatrix = true;

		Quaternion rot;
		rot.FromAxisAngle(Up(), -angle_);
		Vector3F dir = Direction() * m_fDistance;
		Vector3F vec;
		rot.Transform(dir, vec);
		//Vector3F::Transform(dir, rot, vec);
		m_Target += vec - dir;

		OrbitRight(-angle_);
	}

	/// <summary>
	/// Sets up a quaternion & position from vector camera components
	/// and oriented the camera up
	/// </summary>
	/// <param name="eye">The camera position</param>
	/// <param name="lookAt">The camera's look-at point</param>
	/// <param name="up"></param>
	void ArcBallCameraController::SetCamera(Vector3F position, Vector3F target, Vector3F up)
	{
		m_bRecomputeViewMatrix = true;

		//Create a look at matrix, to simplify matters a bit
		Matrix4 temp;
		temp.LookAt(position, target, up);

		//invert the matrix, since we're determining the
		//orientation from the rotation matrix in RH coords
		temp.Invert();

		//set the position
		m_Target = target;

		//set distance
		m_fDistance = (target - position).Length();

		//create the new aspect from the look-at matrix
		m_ArcBallOrientation.FromMatrix(temp);

		//When setting a new eye-view direction 
		//in one of the gamble-locked modes, the yaw and
		//pitch gimble must be calculated.

		//first, get the direction projected on the x/z plne
		Vector3F dir = Direction();
		dir.y = 0.0f;
		if (dir.Length() == 0.0f)
		{
			dir = Vector3F::Forward();
		}
		dir.Normalize();

		//find the yaw of the direction on the x/z plane
		//and use the sign of the x-component since we have 360 degrees
		//of freedom
		m_fArcBallYaw = (acosf(-dir.z) * Sign(dir.x));

		//Get the pitch from the angle formed by the Up vector and the 
		//the forward direction, then subtracting Pi / 2, since 
		//we pitch is zero at Forward, not Up.
		m_fArcBallPitch = -(acosf(Vector3F::Dot(Vector3F::Up(), Direction())) - MATH_PI_DIV_2);
	}


	/**
	 *
	 */
	void ArcBallCameraController::Write(std::ostream& /*os*/) const
	{

	}

	/**
	 *
	 */
	void ArcBallCameraController::Read(std::ifstream& /*is*/)
	{

	}

}
