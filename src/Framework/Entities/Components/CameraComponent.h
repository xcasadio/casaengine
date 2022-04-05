#ifndef CAMERACOMPONENT_H_
#define CAMERACOMPONENT_H_

#include "CA_Export.h"
#include "GameTime.h"
#include "Entities/Component.h"
#include "Entities/BaseEntity.h"
#include "Maths/Matrix4.h"
#include "Graphics/Viewport.h"

namespace CasaEngine
{
	class ICameraController;

	class CA_EXPORT CameraComponent :
		public Component
	{
	public:
		Matrix4 GetViewMatrix();
		Matrix4 GetProjectionMatrix();

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;

		ICameraController * CameraController() const;
		void CameraController(ICameraController * val);

		bool OnWindowResized(const EventArgs& e_);

		Viewport& GetViewport();
		float GetViewDistance() const;

	protected:
		CameraComponent(BaseEntity* pEntity_, int type_);
		~CameraComponent() override;

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
		void Draw();
#endif
	};

}

#endif


