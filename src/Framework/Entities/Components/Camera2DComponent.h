#ifndef CAMERA2DCOMPONENT_H_
#define CAMERA2DCOMPONENT_H_

#include <string>

#include "CA_Export.h"
#include "GameTime.h"
#include <iosfwd>
#include "Entities/Components/CameraComponent.h"
#include <string>
#include "Transform2DComponent.h"


namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT Camera2DComponent :
		public CameraComponent
	{
	public:
		Camera2DComponent(BaseEntity* pEntity_);
		virtual ~Camera2DComponent();

		/**
		 * 
		 */
		void Initialize() override;	

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		void Read (const tinyxml2::XMLElement& xmlElt) override;
		void Read (std::ifstream& is) override;
		void Write(tinyxml2::XMLElement& xmlElt) override;
		void Write(std::ostream& os) override;


	protected:
		void ComputeProjectionMatrix() override;
		void ComputeViewMatrix() override;
	private:
		Transform2DComponent* m_pTransform;
		Vector2F m_Position;
		float m_Zoom;
	};

}

#endif // CAMERA2DCOMPONENT_H_


