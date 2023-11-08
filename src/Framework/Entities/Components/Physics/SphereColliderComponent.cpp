#include  "Entities/BaseEntity.hpp"

#include  "SphereColliderComponent.hpp"
#include  "Entities/ComponentTypeEnum.hpp"
#include  "Game/Game.hpp"


namespace CasaEngine
{
	SphereColliderComponent::SphereColliderComponent(BaseEntity* entity)
		: ColliderComponent(entity, SPHERE_COLLIDER)
	{

	}

	SphereColliderComponent::~SphereColliderComponent()
		= default;

	void SphereColliderComponent::Initialize()
	{
		//m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>();
		//CA_ASSERT("SphereColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a SphereColliderComponent", m_pTransform != nullptr);
	}

	void SphereColliderComponent::Write(std::ostream& /*os*/) const
	{

	}

	void SphereColliderComponent::Read(std::ifstream& /*is*/)
	{

	}

}
