#include <string>

#include "Base.h"

#include "Entities/BaseEntity.h"
#include "Entities/ComponentTypeEnum.h"
#include "CameraComponent.h"

#include "Game/Game.h"
#include "Maths/Matrix4.h"
#include "Resources/ResourceManager.h"
#include "Transform2DComponent.h"

#include "StringUtils.h"
#include "Maths/Math.h"

#include "Entities/Components/CameraControllers/CameraController.h"
#include "EventHandler/GlobalEventSet.h"
#include "EventHandler/Event.h"
#include "Macro.h"

namespace CasaEngine
{
	/**
	 *
	 */
	CameraComponent::CameraComponent(BaseEntity* pEntity_, int type_)
		: Component(pEntity_, type_),
		m_needToComputeProjectionMatrix(true),
		m_needToComputeViewMatrix(true),
		m_pCameraController(nullptr)
	{
		//registerEventFunc(this, &CameraComponent::OnWindowResized);
		m_WindowResizedConnection = GlobalEventSet::Instance().subscribeEvent(
			WindowResizeEvent::GetEventName(),
			Event::Subscriber(&CameraComponent::OnWindowResized, this));

		m_ViewMatrix.LookAt(Vector3F(0.0f, 10.0f, -10.0f), Vector3F::Zero());
		
		m_Viewport.X(0);
		m_Viewport.Y(0);
		m_Viewport.Width(1.0f);
		m_Viewport.Height(1.0f);
		m_Viewport.NearClipPlane(0.0f);
		m_Viewport.FarClipPlane(1000.0f);
	}

	/**
	 *
	 */
	CameraComponent::~CameraComponent()
	{
		m_WindowResizedConnection->disconnect();
		DELETE_AO m_pCameraController;
	}

	void CameraComponent::Initialize()
	{
		if (m_pCameraController != nullptr)
		{
			m_pCameraController->Initialize();
		}
	}

	/**
	 *
	 */
	void CameraComponent::Update(const GameTime& gameTime_)
	{
		if (m_pCameraController != nullptr)
		{
			m_pCameraController->Update(gameTime_);
		}
	}


	/**
	 *
	 */
	 /*void CameraComponent::HandleEvent(const Event* pEvent_)
	 {

	 }*/

	 /**
	  *
	  */
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

	/**
	 *
	 */
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

	/**
	 *
	 */
	ICameraController* CameraComponent::CameraController() const
	{
		return m_pCameraController;
	}

	/**
	 *
	 */
	void CameraComponent::CameraController(ICameraController* val)
	{
		m_pCameraController = val;
		m_needToComputeProjectionMatrix = true;
		m_needToComputeViewMatrix = true;
	}

	/**
	 *
	 */
	bool CameraComponent::OnWindowResized(const EventArgs& e_)
	{
		m_needToComputeProjectionMatrix = true;

		const float d_yfov_tan = 0.267949192431123f;

		const float w = static_cast<float>(m_Viewport.Width() * Game::Instance()->GetWindow()->getSize().x);
		const float h = static_cast<float>(m_Viewport.Height() * Game::Instance()->GetWindow()->getSize().y);
		const float aspect = w / h;
		const float midx = w * 0.5f;
		const float midy = h * 0.5f;
		m_ViewDistance = midx / (aspect * d_yfov_tan);

		return false;
	}

	/**
	 *
	 */
	CasaEngine::Viewport& CameraComponent::GetViewport()
	{
		return m_Viewport;
	}

	/**
	 *
	 */
	float CameraComponent::GetViewDistance() const
	{
		return m_ViewDistance;
	}

	/**
	 *
	 */
	void CameraComponent::Write(std::ostream& os)
	{
		//CA_UNUSED_1(os)
	}

	/**
	 *
	 */
	void CameraComponent::Read(std::ifstream& is)
	{
		//CA_UNUSED_1(is)
	}

	/**
	 *
	 */
	void CameraComponent::Read(const tinyxml2::XMLElement& xmlElt)
	{
		//CA_UNUSED_1(xmlElt)
	}

	/**
	 *
	 */
	void CameraComponent::Write(tinyxml2::XMLElement& xmlElt)
	{
		//CA_UNUSED_1(xmlElt)
	}


#if EDITOR

	/**
	 * Draw icon only in editor mode
	 */
	void CameraComponent::Draw()
	{

	}

#endif // EDITOR

}
