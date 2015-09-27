
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
#include "EngineInfo.h"

namespace CasaEngine
{

/**
 * 
 */
Camera2DComponent::Camera2DComponent(BaseEntity* pEntity_)
	: CameraComponent(pEntity_, CAMERA_2D),
		m_Zoom(1.0f)
{
	ComputeProjectionMatrix();
}

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
void Camera2DComponent::Update(const GameTime& /*gameTime_*/)
{
	/*Matrix4 mat = m_pTransform->GetWorldMatrix();
	Vector3F pos3 = mat.GetTranslation();
	Vector2F pos(pos3.x, pos3.y);*/
}

#if EDITOR

/**
 * 
 */
void Camera2DComponent::Draw()
{
	//Draw icon only in editor mode
}

#endif // EDITOR

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
		0.0f, 1000.0f);
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

} // namespace CasaEngine
