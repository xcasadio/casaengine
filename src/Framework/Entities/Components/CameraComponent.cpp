
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
#include "EngineInfo.h"
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
	m_pCameraController(nullptr)
{
	//registerEventFunc(this, &CameraComponent::OnWindowResized);
	m_WindowResizedConnection = GlobalEventSet::Instance().subscribeEvent(
		WindowResizeEvent::GetEventName(), 
		Event::Subscriber(&CameraComponent::OnWindowResized, this));

	m_Viewport.X(0);
	m_Viewport.Y(0);
	m_Viewport.Width(1.0f);
	m_Viewport.Height(1.0f);
	/*m_Viewport.Width(Game::Instance()->GetWindow()->getSize().x);
	m_Viewport.Height(Game::Instance()->GetWindow()->getSize().y);*/
	m_Viewport.NearClipPlane(1.0f);
	m_Viewport.FarClipPlane(1000.0f);
}

/**
 * 
 */
CameraComponent::~CameraComponent()
{
	m_WindowResizedConnection->disconnect();

	if (m_pCameraController != nullptr)
	{
		DELETE_AO m_pCameraController;
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

#if EDITOR

/**
 * Draw icon only in editor mode
 */
void CameraComponent::Draw()
{
	
}

#endif // EDITOR

/**
 * 
 */
/*void CameraComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
Matrix4 CameraComponent::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

/**
 * 
 */
Matrix4 CameraComponent::GetViewMatrix() const
{
	if (m_pCameraController != nullptr)
	{
		return m_pCameraController->ViewMatrix(m_ViewMatrix);
	}

	return m_ViewMatrix;
}

/**
 * 
 */
ICameraController * CameraComponent::CameraController() const 
{ 
	return m_pCameraController; 
}

/**
 * 
 */
void CameraComponent::CameraController(ICameraController * val) 
{ 
	m_pCameraController = val;
	m_pCameraController->Initialize();
}

/**
 * 
 */
bool CameraComponent::OnWindowResized(const EventArgs& e_)
{
	CA_UNUSED_1(e_)

	ComputeProjectionMatrix();

	const float d_yfov_tan = 0.267949192431123f;

	const float w = m_Viewport.Width() * static_cast<float>(m_Viewport.Width() * Game::Instance()->GetWindow()->getSize().x);
	const float h = m_Viewport.Height() * static_cast<float>(m_Viewport.Height() * Game::Instance()->GetWindow()->getSize().y);
	const float aspect = w / h;
	const float midx = w * 0.5f;
	const float midy = h * 0.5f;
	m_ViewDistance = midx / (aspect * d_yfov_tan);

	return false;
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
void CameraComponent::Read (std::ifstream& is)
{
	//CA_UNUSED_1(is)
}

/**
 * 
 */
void CameraComponent::Read (const tinyxml2::XMLElement& xmlElt)
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

/**
 * 
 */
CasaEngine::Viewport &CameraComponent::GetViewport()
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

} // namespace CasaEngine
