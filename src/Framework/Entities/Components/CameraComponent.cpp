#include "Base.h"

#include "Entities/BaseEntity.h"
#include "CameraComponent.h"

#include "Game/Game.h"
#include "Maths/Matrix4.h"
#include "Transform2DComponent.h"

#include "Entities/Components/CameraControllers/CameraController.h"
#include "EventHandler/GlobalEventSet.h"
#include "EventHandler/Event.h"


namespace CasaEngine
{
	CameraComponent::CameraComponent(BaseEntity* pEntity_, int type_)
		: Component(pEntity_, type_),
		m_needToComputeProjectionMatrix(true),
		m_needToComputeViewMatrix(true),
		m_pCameraController(nullptr)
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
		m_Viewport.FarClipPlane(1000.0f);
	}

	CameraComponent::~CameraComponent()
	{
		m_WindowResizedConnection->disconnect();
		delete m_pCameraController;
	}

	void CameraComponent::Initialize()
	{
		if (m_pCameraController != nullptr)
		{
			m_pCameraController->Initialize();
		}
	}

	void CameraComponent::Update(const GameTime& gameTime_)
	{
		if (m_pCameraController != nullptr)
		{
			m_pCameraController->Update(gameTime_);
		}
	}

	Matrix4 CameraComponent::GetProjectionMatrix()
	{
		if (m_pCameraController != nullptr)
		{
			m_pCameraController->ProjectionMatrix(m_ProjectionMatrix);
		}
		else
		{
			ComputeProjectionMatrix();
		}
		
		return m_ProjectionMatrix;
	}

	Matrix4 CameraComponent::GetViewMatrix()
	{
		if (m_pCameraController != nullptr)
		{
			m_pCameraController->ViewMatrix(m_ViewMatrix);
		}
		else
		{
			ComputeViewMatrix();
		}

		return m_ViewMatrix;
	}

	ICameraController* CameraComponent::CameraController() const
	{
		return m_pCameraController;
	}

	void CameraComponent::CameraController(ICameraController* val)
	{
		m_pCameraController = val;
		m_needToComputeProjectionMatrix = true;
		m_needToComputeViewMatrix = true;
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
