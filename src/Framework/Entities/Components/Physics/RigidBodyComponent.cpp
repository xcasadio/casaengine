#include "Base.h"
#include "Entities/BaseEntity.h"

#include "RigidBodyComponent.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"

#include "CA_Assert.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/GameInfo.h"

namespace CasaEngine
{
	class Transform3DComponent;

	RigidBodyComponent::RigidBodyComponent(BaseEntity* pEntity_)
		: Component(pEntity_, RIGID_BODY), m_Mass(0.0f), m_UseGravity(true), m_IsKinematic(false)
	{
		m_ListShapes.reserve(1);
	}

	void RigidBodyComponent::Initialize()
	{
		m_RigidBody.mass = 1.0f;
		auto* transform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		IRigidBodyContainer* pContainer = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddRigidBody(GetEntity(), &m_RigidBody, transform->GetPosition());
		GetEntity()->GetPhysicalEntity().SetRigidBody(pContainer);
	}

	bool RigidBodyComponent::HandleMessage(const Telegram& msg)
	{
		return false;
	}

	void RigidBodyComponent::Update(const GameTime& gameTime_)
	{

	}

	RigidBodyParameters& RigidBodyComponent::GetRigidBody()
	{
		return m_RigidBody;
	}

	void RigidBodyComponent::SetRigidBody(RigidBodyParameters& val)
	{
		m_RigidBody = val;
	}

	void RigidBodyComponent::AddShape(ColliderComponent* pShape_)
	{
		m_ListShapes.push_back(pShape_);
	}

	void RigidBodyComponent::RemoveShape(ColliderComponent* pShape_)
	{
		std::vector<ColliderComponent*>::iterator it;

		for (it = m_ListShapes.begin(); it != m_ListShapes.end(); it++)
		{
			if ((*it) == pShape_)
			{
				m_ListShapes.erase(it);
				break;
			}
		}

		CA_ASSERT(0, "RigidBodyComponent::RemoveShape() ColliderComponent not found")
	}
}
