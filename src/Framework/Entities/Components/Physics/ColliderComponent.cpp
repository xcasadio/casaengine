#include "Base.h"
#include "Entities/BaseEntity.h"

#include "ColliderComponent.h"
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
			DELETE_AO m_pCollisionObjectContainer;
		}
	}

	void ColliderComponent::Initialize()
	{
		CA_ASSERT(m_pCollisionObjectContainer == nullptr, "ColliderComponent::Initialize()");
		m_pCollisionObjectContainer =
			Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddCollisionShape(GetShape(), Vector3F::Zero());
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
}