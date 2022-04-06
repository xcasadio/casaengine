#include "Base.h"
#include "Entities/BaseEntity.h"

#include "ColliderComponent.h"

#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

#include "Game/GameInfo.h"

namespace CasaEngine
{
	ColliderComponent::ColliderComponent(BaseEntity* pEntity_, int type_)
		: Component(pEntity_, type_),
		m_IsTrigger(false),
		m_pShape(nullptr),
		m_pCollisionObjectContainer(nullptr)
	{
	}

	ColliderComponent::~ColliderComponent()
	{
		if (m_pCollisionObjectContainer != nullptr)
		{
			delete m_pCollisionObjectContainer;
		}
	}

	void ColliderComponent::Initialize()
	{
		CA_ASSERT(m_pCollisionObjectContainer == nullptr, "ColliderComponent::Initialize()");
		m_pCollisionObjectContainer =
			Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->CreateCollisionShape(GetShape(), Vector3F::Zero());
	}

	void ColliderComponent::Update(const GameTime& /*gameTime_*/)
	{
	}

	void ColliderComponent::Write(std::ostream& /*os*/) const
	{
	}

	void ColliderComponent::Read(std::ifstream& /*is*/)
	{
	}

	float ColliderComponent::Mass() const
	{
		return m_Mass;
	}

	void ColliderComponent::Mass(float val)
	{
		m_Mass = val;
	}

	IShape* ColliderComponent::GetShape() const
	{
		return m_pShape;
	}

	void ColliderComponent::CreateAndSetRigidBody(float mass)
	{
		auto* transform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(transform != nullptr, "Circle2DColliderComponent::Initialize() can't find the Transform3DComponent. Please add it before add a Circle2DColliderComponent");
		auto* rigidBody = new RigidBody();
		rigidBody->mass = mass;
		rigidBody->pCollisionShape = m_pShape;
		IRigidBodyContainer* pContainer = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddRigidBody(rigidBody, transform->GetPosition());
		GetEntity()->GetPhysicalEntity().SetRigidBody(pContainer);
	}
}