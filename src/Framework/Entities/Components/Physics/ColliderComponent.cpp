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
		m_pShape(nullptr),
		axisConstraint(AxisConstraints::NONE),
		m_Mass(0),
		m_pCollisionObjectContainer(nullptr)
	{
	}

	ColliderComponent::~ColliderComponent()
	{
		delete m_pCollisionObjectContainer;
	}

	void ColliderComponent::Initialize()
	{
		CA_ASSERT(m_pCollisionObjectContainer == nullptr, "ColliderComponent::Initialize()");
		m_pCollisionObjectContainer =
			Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->CreateCollisionShape(GetShape(), Vector3::Zero());
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

	AxisConstraints ColliderComponent::AxisConstraint() const
	{
		return axisConstraint;
	}

	void ColliderComponent::AxisConstraint(AxisConstraints val)
	{
		axisConstraint = val;
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
		rigidBody->axisConstraint = axisConstraint;
		IRigidBodyContainer* pContainer = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddRigidBody(GetEntity(), rigidBody, transform->GetPosition());
		GetEntity()->GetPhysicalEntity().SetRigidBody(pContainer);
	}
}