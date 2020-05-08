#ifndef CAMERACOMPONENT_H_
#define CAMERACOMPONENT_H_


#include "CA_Export.h"
#include "GameTime.h"
#include "Entities/Component.h"
#include "Entities/BaseEntity.h"
#include "Maths/Matrix4.h"
#include "Graphics/Viewport.h"
#include "Entities/Events/BaseEntityEvents.h"
#include "EventHandler/EventArgs.h"

#include <iosfwd>
#include <string>
#include "Parsers/Xml/tinyxml2.h"



namespace CasaEngine
{
	class ICameraController;

	/*
	 *	
	 */
	class CA_EXPORT CameraComponent :
		public Component
	{
	public:
		Matrix4 GetViewMatrix();
		Matrix4 GetProjectionMatrix();	

		virtual void Initialize() override;
		void Update(const GameTime& gameTime_);

		ICameraController * CameraController() const;
		void CameraController(ICameraController * val);

		bool OnWindowResized(const EventArgs& e_);

		/**
		 * Viewport with ratio value [0.0;1.0]
		 */
		Viewport& GetViewport();
		float GetViewDistance() const;
		
		virtual void Read (const tinyxml2::XMLElement& xmlElt) override;
		virtual void Read (std::ifstream& is) override;
		virtual void Write(tinyxml2::XMLElement& xmlElt) override;
		virtual void Write(std::ostream& os) override;

	protected:
		CameraComponent(BaseEntity* pEntity_, int type_);
		virtual ~CameraComponent();

		virtual void ComputeProjectionMatrix() = 0;
		virtual void ComputeViewMatrix() = 0;

	protected:
		Matrix4 m_ViewMatrix;
		Matrix4 m_ProjectionMatrix;
		Viewport m_Viewport;
		float m_ViewDistance; // distance between the camera and the near far clip plane
		bool m_needToComputeProjectionMatrix;
		bool m_needToComputeViewMatrix;

	private:
		ICameraController *m_pCameraController;
		Event::Connection m_WindowResizedConnection;

#if EDITOR
	public:
		/**
		 * Draw icon only in editor mode
		 */
		void Draw();

#endif // EDITOR
	};

}

#endif // CAMERACOMPONENT_H_


