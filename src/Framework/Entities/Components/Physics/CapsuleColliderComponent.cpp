#include "Entities/BaseEntity.h"

#include "CapsuleColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

namespace CasaEngine
{

	CapsuleColliderComponent::CapsuleColliderComponent(BaseEntity* pEntity_)
		: ColliderComponent(pEntity_, CAPSULE_COLLIDER)
	{

	}

	CapsuleColliderComponent::~CapsuleColliderComponent()
	{

	}

	void CapsuleColliderComponent::Initialize()
	{
		//m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>();
		//CA_ASSERT("CapsuleColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a CapsuleColliderComponent", m_pTransform != nullptr);
	}
	void CapsuleColliderComponent::Write(std::ostream& /*os*/) const
	{

	}

	void CapsuleColliderComponent::Read(std::ifstream& /*is*/)
	{

	}

}
