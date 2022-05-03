#include "Base.h"
#include "Entities/BaseEntity.h"

#include "ColliderComponent.h"

#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"

#include "Game/GameInfo.h"

namespace CasaEngine
{
	ColliderComponent::ColliderComponent(BaseEntity* entity_, int type_)
		: Component(entity_, type_),
		_shape(nullptr),
		_axisConstraint(AxisConstraints::NONE),
		_mass(0),
		_collisionObjectContainer(nullptr)
	{
	}

	ColliderComponent::~ColliderComponent()
	{
		delete _collisionObjectContainer;
	}

	void ColliderComponent::Initialize()
	{
		CA_ASSERT(_collisionObjectContainer == nullptr, "ColliderComponent::Initialize()");
		_collisionObjectContainer = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->CreateCollisionShape(GetShape(), Vector3::Zero());
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
		return _mass;
	}

	void ColliderComponent::Mass(float val)
	{
		_mass = val;
	}

	AxisConstraints ColliderComponent::AxisConstraint() const
	{
		return _axisConstraint;
	}

	void ColliderComponent::AxisConstraint(AxisConstraints val)
	{
		_axisConstraint = val;
	}

	IShape* ColliderComponent::GetShape() const
	{
		return _shape;
	}

	void ColliderComponent::CreateAndSetRigidBody(float mass)
	{
		auto* transform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(transform != nullptr, "ColliderComponent::Initialize() can't find the Transform3DComponent.");
		auto* rigidBody = new RigidBodyParameters();
		rigidBody->mass = mass;
		rigidBody->collisionShape = _shape;
		rigidBody->axisConstraint = _axisConstraint;
		IRigidBodyContainer* pContainer = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddRigidBody(GetEntity(), rigidBody, transform->GetPosition());
		GetEntity()->GetPhysicalEntity().SetRigidBody(pContainer);
	}
}