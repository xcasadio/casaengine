
#include "Base.h"
#include "Entities/BaseEntity.h"

#include "Camera2DComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"
#include "Resources/ResourceManager.h"
#include "StringUtils.h"

#include "Transform2DComponent.h"


namespace CasaEngine
{

/**
 * 
 */
Camera2DComponent::Camera2DComponent(BaseEntity* pEntity_)
	: CameraComponent(pEntity_, CAMERA_2D),
		m_Zoom(1.0f)
{}

/**
 * 
 */
Camera2DComponent::~Camera2DComponent()
{
}

/**
 * 
 */
void Camera2DComponent::Initialize()
{
}

/**
 * 
 */
void Camera2DComponent::ComputeProjectionMatrix()
{
    m_ProjectionMatrix.OrthoOffCenter(
        static_cast<float>(m_Viewport.X()),
        static_cast<float>(m_Viewport.Y()),
        static_cast<float>(m_Viewport.Width() * Game::Instance()->GetWindow()->getSize().x),
        static_cast<float>(m_Viewport.Height() * Game::Instance()->GetWindow()->getSize().y),
        m_Viewport.NearClipPlane(), 
        m_Viewport.FarClipPlane());
    m_ProjectionMatrix = m_ProjectionMatrix.Transpose();
}

void Camera2DComponent::ComputeViewMatrix()
{
    m_ViewMatrix.CreateTranslation(0.0f, 0.0f, 0.0f);
}

/**
 * 
 */
/*void Camera2DComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void Camera2DComponent::Write(std::ostream& /*os*/)
{
	//CA_UNUSED_1(os)
}

/**
 * 
 */
void Camera2DComponent::Read (std::ifstream& /*is*/)
{
	//CA_UNUSED_1(is)
}

/**
 * 
 */
void Camera2DComponent::Read (const tinyxml2::XMLElement& /*xmlElt*/)
{
	//CA_UNUSED_1(xmlElt)
}

/**
 * 
 */
void Camera2DComponent::Write(tinyxml2::XMLElement& /*xmlElt*/)
{
	//CA_UNUSED_1(xmlElt)
}

}
