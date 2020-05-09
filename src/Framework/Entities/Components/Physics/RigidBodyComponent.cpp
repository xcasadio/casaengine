
#include "Base.h"
#include "Entities/BaseEntity.h"

#include "RigidBodyComponent.h"
#include "Maths/Matrix4.h"
#include "Entities/ComponentTypeEnum.h"
#include <string>
#include "Game/Game.h"

#include "CA_Assert.h"
#include "Game/GameInfo.h"

namespace CasaEngine
{

/**
 * 
 */
RigidBodyComponent::RigidBodyComponent(BaseEntity* pEntity_)
	: Component(pEntity_, RIGID_BODY)
{
	m_ListShapes.reserve(1);
	m_Mass = 0.0f;
	m_UseGravity = true;
	m_IsKinematic = false;
}

/**
 * 
 */
RigidBodyComponent::~RigidBodyComponent()
{

}

/**
 * 
 */
void RigidBodyComponent::Initialize()
{
	m_RigidBody.mass = 1.0f;
	IRigidBodyContainer *pContainer = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddRigidBody(&m_RigidBody);
	GetEntity()->GetPhysicalEntity().SetRigidBody(pContainer);
}

/**
 * 
 */
bool RigidBodyComponent::HandleMessage(const Telegram& msg)
{
	return false;
}

/**
 * 
 */
void RigidBodyComponent::Update(const GameTime& gameTime_)
{

}

/**
 * 
 */
RigidBody& RigidBodyComponent::GetRigidBody()
{
	return m_RigidBody;
}

/**
 * 
 */
void RigidBodyComponent::SetRigidBody(RigidBody& val)
{
	m_RigidBody = val;
}

/**
 * 
 */
void RigidBodyComponent::AddShape(ColliderComponent *pShape_)
{
	m_ListShapes.push_back(pShape_);
}

/**
 * 
 */
void RigidBodyComponent::RemoveShape(ColliderComponent *pShape_)
{
	std::vector<ColliderComponent *>::iterator it;

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

/**
 * 
 */
void RigidBodyComponent::Read(const tinyxml2::XMLElement& xmlElt)
{
	
}

/**
 * 
 */
void RigidBodyComponent::Read(std::ifstream& is)
{
	
}

/**
 * 
 */
void RigidBodyComponent::Write(tinyxml2::XMLElement& xmlElt)
{
	
}

/**
 * 
 */
void RigidBodyComponent::Write(std::ostream& os)
{
	
}

}
