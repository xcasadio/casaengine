#pragma once

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>

#include "Camera3DComponent.h"
#include "Maths/Quaternion.h"
#include "Maths/Vector3.h"

namespace CasaEngine
{
	class CA_EXPORT ArcBallCameraComponent :
		public Camera3DComponent
	{
	public:
		ArcBallCameraComponent(BaseEntity* pEntity_);

		void Initialize() override;
		void  Update(const GameTime& gameTime_) override;

		Vector3F Direction() const;
		Vector3F Right() const;
		Vector3F Up() const;
		Vector3F Position() const;
		void Position(Vector3F val);

		void ComputeViewMatrix() override;

		Vector3F Target() const;
		void Target(Vector3F val);
		float Distance() const;
		void Distance(float val);
		float InputDistanceRate() const;
		void InputDistanceRate(float val);
		float InputDisplacementRate() const;
		void InputDisplacementRate(float val);

		/// <summary>
		/// Orbit directly upwards in Free camera or on
		/// the longitude line when roll constrained
		/// </summary>
		void OrbitUp(float angle);
		void OrbitRight(float angle);
		void RotateClockwise(float angle);
		void RotateTargetUp(float angle_);
		void RotateTargetRight(float angle_);
		void SetCamera(Vector3F position, Vector3F target, Vector3F up);

		float ArcBallPitch() const;
		void ArcBallPitch(float val);
		float ArcBallYaw() const;
		void ArcBallYaw(float val);

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream& os)const;
		void Read (std::ifstream& is);		

	private:
		void HandleControls(const GameTime& gameTime_,
			float rightAxis_, float upAxis_, float forwardAxis_,
			float horizontalOrbit_, float verticalOrbit_, float rollOrbit_, float zoom_);

	private:
		Vector3F m_Target;
		float m_fDistance{};

		Quaternion m_ArcBallOrientation;

		float m_fInputDistanceRate;		
		float m_fInputTurnRate, m_fInputDisplacementRate;
		float m_fArcBallYaw{}, m_fArcBallPitch{};
	};
}
