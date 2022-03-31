#include "Entities/BaseEntity.h"

#include "Circle2DColliderComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

namespace CasaEngine
{
	Circle2DColliderComponent::Circle2DColliderComponent(BaseEntity* pEntity_)
		: ColliderComponent(pEntity_, CIRCLE2D_COLLIDER)
	{
	}

	Circle2DColliderComponent::~Circle2DColliderComponent()
	{
	}

	void Circle2DColliderComponent::SetPosition(const Vector3F& position)
	{
		m_Circle.Center(position);
	}

	void Circle2DColliderComponent::SetRadius(float radius)
	{
		m_Circle.Radius(radius);
	}

	void Circle2DColliderComponent::Initialize()
	{
		auto* transform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		//CA_ASSERT("Circle2DColliderComponent::Initialize() can't find the Transform2DComponent. Please add it before add a Circle2DColliderComponent", m_pTransform != nullptr);
		auto* rigidBody = new RigidBody();
		rigidBody->mass = 1.0f;
		rigidBody->pCollisionShape = &m_Circle;
		IRigidBodyContainer* pContainer = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddRigidBody(rigidBody, transform->GetPosition());
		GetEntity()->GetPhysicalEntity().SetRigidBody(pContainer);
	}
}