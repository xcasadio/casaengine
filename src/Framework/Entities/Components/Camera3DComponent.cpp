
#include "Base.h"
#include "Entities/BaseEntity.h"

#include "Camera3DComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"
#include "Resources/ResourceManager.h"
#include "StringUtils.h"

#include "Transform3DComponent.h"
#include "EngineInfo.h"

namespace CasaEngine
{

/**
 * 
 */
Camera3DComponent::Camera3DComponent(BaseEntity* pEntity_)
	: CameraComponent(pEntity_, CAMERA_3D),
		m_Position(Vector3F::One()),
		m_Target(Vector3F::Zero()),
		m_fFOV(MATH_PI_DIV_4)
{
	ComputeProjectionMatrix();
}

/**
 * 
 */
Camera3DComponent::~Camera3DComponent()
{

}

/**
 * 
 */
void Camera3DComponent::Initialize()
{
}

/**
 * 
 */
/*void Camera3DComponent::Update(const GameTime& gameTime_)
{
	
}*/

#if EDITOR

/**
 * 
 */
void Camera3DComponent::Draw()
{
	//Draw icon only in editor mode
}

#endif // EDITOR

/**
 * 
 */
/*void Camera3DComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
Vector3F Camera3DComponent::Position() const 
{ 
	return m_Position; 
}

/**
 * 
 */
void Camera3DComponent::Position(Vector3F val) 
{ 
	m_Position = val; 
	ComputeViewMatrix();
}

/**
 * 
 */
Vector3F Camera3DComponent::Target() const 
{ 
	return m_Target; 
}

/**
 * 
 */
void Camera3DComponent::Target(Vector3F val) 
{
	m_Target = val; 
	ComputeViewMatrix();
}


/**
 * 
 */
float Camera3DComponent::FOV() const 
{ 
	return m_fFOV; 
}

/**
 * 
 */
void Camera3DComponent::FOV(float val) 
{ 
	m_fFOV = val; 
	ComputeProjectionMatrix();
}

/**
 * 
 */
float Camera3DComponent::FarClipPlane() const 
{ 
	return m_Viewport.FarClipPlane(); 
}

/**
 * 
 */
void Camera3DComponent::FarClipPlane(float val) 
{ 
	m_Viewport.FarClipPlane(val); 
	ComputeProjectionMatrix();
}

/**
 * 
 */
float Camera3DComponent::NearClipPlane() const 
{ 
	return m_Viewport.NearClipPlane();
}

/**
 * 
 */
void Camera3DComponent::NearClipPlane(float val)
{ 
	m_Viewport.NearClipPlane(val);
	ComputeProjectionMatrix();
}

/**
 * 
 */
void Camera3DComponent::ComputeProjectionMatrix()
{
	float ratio = static_cast<float>(m_Viewport.Width() * Game::Instance()->GetWindow()->getSize().x) / 
		static_cast<float>(m_Viewport.Height() * Game::Instance()->GetWindow()->getSize().y);

	m_ProjectionMatrix.PerspectiveFOV(
		m_fFOV,
		ratio/*m_Viewport.AspectRatio()*/, 
		m_Viewport.NearClipPlane(),
		m_Viewport.FarClipPlane());
}


/**
 * 
 */
void Camera3DComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void Camera3DComponent::Read (std::ifstream& /*is*/)
{

}

/**
 * 
 */
void Camera3DComponent::ComputeViewMatrix()
{
	m_ViewMatrix.LookAt(m_Position, m_Target);
}

} // namespace CasaEngine
