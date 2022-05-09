#include "Base.h"

#include "Entities/BaseEntity.h"
#include "CameraComponent.h"

#include "Game/Game.h"

#include "EventHandler/GlobalEventSet.h"
#include "EventHandler/Event.h"
#include "../Events/BaseEntityEvents.h"

namespace CasaEngine
{
	CameraComponent::CameraComponent(BaseEntity* pEntity_, int type_)
		: Component(pEntity_, type_),
		m_needToComputeProjectionMatrix(true),
		m_needToComputeViewMatrix(true)
	{
		//registerEventFunc(this, &CameraComponent::OnWindowResized);
		m_WindowResizedConnection = Game::Instance().GetGlobalEventSet().subscribeEvent(
			WindowResizeEvent::GetEventName(),
			Event::Subscriber(&CameraComponent::OnWindowResized, this));

		m_Viewport.X(0);
		m_Viewport.Y(0);
		m_Viewport.Width(1.0f);
		m_Viewport.Height(1.0f);
		m_Viewport.NearClipPlane(0.1f);
		m_Viewport.FarClipPlane(100000.0f);
	}

	CameraComponent::~CameraComponent()
	{
		m_WindowResizedConnection->disconnect();
	}

	Matrix4 CameraComponent::GetViewMatrix()
	{
		if (m_needToComputeViewMatrix)
		{
			ComputeViewMatrix();
			m_needToComputeViewMatrix = false;
		}

		return m_ViewMatrix;
	}

	Matrix4 CameraComponent::GetProjectionMatrix()
	{
		if (m_needToComputeProjectionMatrix)
		{
			ComputeProjectionMatrix();
			m_needToComputeProjectionMatrix = false;
		}

		return m_ProjectionMatrix;
	}

	void CameraComponent::Update(const GameTime& gameTime_)
	{
	}

	bool CameraComponent::OnWindowResized(const EventArgs& e_)
	{
		m_needToComputeProjectionMatrix = true;

		const float d_yfov_tan = 0.267949192431123f;

		const float w = m_Viewport.Width() * Game::Instance().GetWindowSize().x;
		const float h = m_Viewport.Height() * Game::Instance().GetWindowSize().y;
		const float aspect = w / h;
		const float midx = w * 0.5f;
		//const float midy = h * 0.5f;
		m_ViewDistance = midx / (aspect * d_yfov_tan);

		return false;
	}

	Viewport& CameraComponent::GetViewport()
	{
		return m_Viewport;
	}

	float CameraComponent::GetViewDistance() const
	{
		return m_ViewDistance;
	}

#if EDITOR

	void CameraComponent::Draw()
	{

	}

#endif

}
