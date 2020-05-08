#ifndef CAMERA2DCONTROLLER_H_
#define CAMERA2DCONTROLLER_H_

#include <iosfwd>
#include <string>

#include "CA_Export.h"
#include "CameraController.h"
#include "GameTime.h"
#include "Maths/Matrix4.h"
#include "Entities/Components/CameraComponent.h"


namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT Camera2DController : public ICameraController
	{
	public:
		Camera2DController(CameraComponent* pCamera);
		virtual ~Camera2DController();

		//all entities must implement an update function
		void Initialize();

		//all entities must implement an update function
		void  Update(const GameTime& gameTime_);

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		void ViewMatrix(Matrix4& viewMatrix_);		

		void Read (std::ifstream& is) override;
		void Write(std::ostream& os) override;
		void Read (const tinyxml2::XMLElement& xmlElt) override;
		void Write(tinyxml2::XMLElement& xmlElt) override;
	
	protected:		
		
	private:
		Matrix4 m_ViewMatrix;
		//bool m_bRecomputeViewMatrix;
		Vector3F m_vPosition;
		float m_fRotation;
	};
}

#endif // CAMERA2DCONTROLLER_H_


