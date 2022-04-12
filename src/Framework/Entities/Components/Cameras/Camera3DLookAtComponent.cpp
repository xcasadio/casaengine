#include "Entities/BaseEntity.h"

#include "Camera3DLookAtComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include "StringUtils.h"


namespace CasaEngine
{
	Camera3DLookAtComponent::Camera3DLookAtComponent(BaseEntity* pEntity_)
		: Camera3DComponent(pEntity_, CAMERA_3D_LOOK_AT),
		m_Target(Vector3::Zero()),
		m_Position(Vector3(0.0f, 10.0f, 10.0f))
	{
	}

	void Camera3DLookAtComponent::Initialize()
	{
	}

	Vector3 Camera3DLookAtComponent::Position() const
	{
		return m_Position;
	}

	void Camera3DLookAtComponent::Position(Vector3 val)
	{
		m_Position = val;
		m_needToComputeViewMatrix = true;
	}

	Vector3 Camera3DLookAtComponent::Target() const
	{
		return m_Target;
	}

	void Camera3DLookAtComponent::Target(Vector3 val)
	{
		m_Target = val;
		m_needToComputeViewMatrix = true;
	}

	void Camera3DLookAtComponent::ComputeViewMatrix()
	{
		m_needToComputeViewMatrix = false;
		m_ViewMatrix = Matrix4::CreateLookAt(m_Position, m_Target, Vector3::Up());
	}
	
	void Camera3DLookAtComponent::Write(std::ostream& /*os*/) const
	{

	}

	void Camera3DLookAtComponent::Read(std::ifstream& /*is*/)
	{
	}
}
