#include  "Entities/BaseEntity.hpp"

#include  "CapsuleColliderComponent.hpp"
#include  "Entities/ComponentTypeEnum.hpp"
#include  "Game/Game.hpp"

namespace CasaEngine
{

	CapsuleColliderComponent::CapsuleColliderComponent(BaseEntity* entity)
		: ColliderComponent(entity, CAPSULE_COLLIDER)
	{

	}

	CapsuleColliderComponent::~CapsuleColliderComponent()
		= default;

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
