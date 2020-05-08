#ifndef _ARCBALLCAMERACONTROLLER_H_
#define _ARCBALLCAMERACONTROLLER_H_

#include "CA_Export.h"
#include "GameTime.h"
#include "CameraController.h"
#include <iosfwd>
#include <string>
#include "Maths/Quaternion.h"
#include "Maths/Vector3.h"
#include "Game/Input.h"
#include "Maths/Matrix4.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT ArcBallCameraController :
		public ICameraController
	{
	public:
		ArcBallCameraController(CameraComponent* pCamera);
		virtual ~ArcBallCameraController();

		//all entities must implement an update function
		void Initialize();

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_);

		Vector3F Direction() const;
		Vector3F Right() const;
		Vector3F Up() const;
		Vector3F Position() const;
		void Position(Vector3F val);

		void ViewMatrix(Matrix4& viewMatrix_) override;
		void ProjectionMatrix(Matrix4& projectionMatrix_) override;

		Vector3F Target() const;
		void Target(Vector3F val);
		float Distance() const;
		void Distance(float val);
		float InputDistanceRate() const;
		void InputDistanceRate(float val);

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

		void ReInit();

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
		/// <summary>
		/// The location of the look-at target
		/// </summary>
		Vector3F m_Target;
		
		/// <summary>
		/// The distance between the camera and the target
		/// </summary>
		float m_fDistance;
		
		/// <summary>
		/// The orientation of the camera relative to the target
		/// </summary>
		Quaternion m_ArcBallOrientation;

		bool m_bRecomputeViewMatrix;
		float m_fInputDistanceRate;		
		float m_fInputTurnRate, m_fInputDisplacementRate;
		float m_fArcBallYaw, m_fArcBallPitch;
	};
}

#endif // _ARCBALLCAMERACONTROLLER_H_
