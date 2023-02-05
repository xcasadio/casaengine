#pragma once

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

		void Update(const GameTime& gameTime_) override;

		bool OnWindowResized(const EventArgs& e_);

		Viewport& GetViewport();
		float GetViewDistance() const;

	protected:
		CameraComponent(BaseEntity* entity, int type_);
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
		Event::Connection m_WindowResizedConnection;

#if EDITOR
	public:
		void Draw();
#endif
	};

}
