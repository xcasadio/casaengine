#ifndef CAMERACONTROLLER_H_
#define CAMERACONTROLLER_H_

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Components/CameraComponent.h"
#include <string>
#include "Maths/Matrix4.h"
#include "Entities/Events/BaseEntityEvents.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT ICameraController :
		public AllocatedObject<ICameraController>
	{
	public:
		virtual ~ICameraController();

		//all entities must implement an update function
		virtual void Initialize() = 0;

		//all entities must implement an update function
		virtual void  Update(const GameTime& gameTime_) = 0;

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);
		 
		virtual Matrix4 ViewMatrix(Matrix4 &viewMatrix_) = 0;

		virtual void Write(std::ostream&  os);
		virtual void Read (std::ifstream& is);
		virtual void Read (const tinyxml2::XMLElement& xmlElt);
		virtual void Write(tinyxml2::XMLElement& xmlElt);
	
	protected:
		ICameraController(CameraComponent* pCamera);

		CameraComponent* Camera() const;
		
	private:
		CameraComponent* m_pCamera;
	};
}

#endif // CAMERACONTROLLER_H_


