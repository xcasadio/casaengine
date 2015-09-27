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
#include "CompilationMacro.h"


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
		Matrix4 GetViewMatrix() const;
		Matrix4 GetProjectionMatrix() const;	
	
		void Update(const GameTime& gameTime_);

#if EDITOR

		/**
		 * Draw icon only in editor mode
		 */
		void Draw();

#endif // EDITOR

		ICameraController * CameraController() const;
		void CameraController(ICameraController * val);

		bool OnWindowResized(const EventArgs& e_);

		/**
		 * Viewport with ratio value [0.0;1.0]
		 */
		Viewport& GetViewport();
		float GetViewDistance() const;
		
		virtual void Read (const tinyxml2::XMLElement& xmlElt) OVERRIDE;
		virtual void Read (std::ifstream& is) OVERRIDE;
		virtual void Write(tinyxml2::XMLElement& xmlElt) OVERRIDE;
		virtual void Write(std::ostream& os) OVERRIDE;

	protected:
		CameraComponent(BaseEntity* pEntity_, int type_);
		virtual ~CameraComponent();

		virtual void ComputeProjectionMatrix() = 0;

	protected:
		mutable Matrix4 m_ViewMatrix;
		Matrix4 m_ProjectionMatrix;
		Viewport m_Viewport;
		float m_ViewDistance; // distance between the camera and the near far clip plane

	private:
		ICameraController *m_pCameraController;
		Event::Connection m_WindowResizedConnection;
	};

}

#endif // CAMERACOMPONENT_H_


