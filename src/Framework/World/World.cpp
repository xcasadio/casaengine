#include "Base.h"
#include "World.h"
#include "Entities/BaseEntity.h"
#include "Script/ScriptEngine.h"
#include "Entities/ComponentTypeEnum.h"

namespace CasaEngine
{

/**
 *	
 */
World::World() :
	m_pPhysicsWorld(nullptr)
{
	GetComponentMgr()->AddComponent(NEW_AO WorldComponent(this));
	//TODO : create parameters
	m_CellSpacePartition.Build(50, 50, 7, 7);
}

/**
 *	
 */
World::~World()
{
	if (m_pPhysicsWorld != nullptr)
	{
		DELETE_AO m_pPhysicsWorld;
	}
}

/**
 * 
 */
const std::vector<BaseEntity *>& World::GetEntities()
{
	return m_Entities;
}

/**
 * 
 */
void World::AddEntity(BaseEntity* pEntity_)
{
	m_Entities.push_back(pEntity_);
}

/**
 * 
 */
void World::SetPhysicsWorld(IPhysicsWorld *pWorld_ )
{
	m_pPhysicsWorld = pWorld_;
}

/**
 * 
 */
IPhysicsWorld * World::GetPhysicsWorld() const
{
	return m_pPhysicsWorld;
}

/**
 * 
 */
void World::Read (std::ifstream& is)
{

}

/**
 * 
 */
void World::Read (const tinyxml2::XMLElement& xmlElt)
{

}

/**
 * 
 */
void World::Write(std::ostream& os)
{

}

/**
 * 
 */
void World::Write(tinyxml2::XMLElement& xmlElt)
{

}

/**
 * 
 */
CellSpacePartition<BaseEntity *> & World::GetSpacePartition()
{
	return m_CellSpacePartition;
}



//////////////////////////////////////////////////////////////////////////

/**
 * 
 */
World::WorldComponent::WorldComponent(BaseEntity* pEntity_) :
	Component(pEntity_, ComponentType::WORLD)
{
	m_pWorld = dynamic_cast<World *>(pEntity_);
	CA_ASSERT(m_pWorld != nullptr, "WorldComponent()");
}

/**
 * 
 */
void World::WorldComponent::Initialize()
{
	
}

/**
 * 
 */
void World::WorldComponent::Update( const GameTime& gameTime_ )
{
	if (m_pWorld->GetPhysicsWorld() != nullptr)
	{
		m_pWorld->GetPhysicsWorld()->Update(gameTime_);
	}

	for (std::vector<BaseEntity *>::const_iterator it = m_pWorld->GetEntities().begin();
		it != m_pWorld->GetEntities().end();
		it++)
	{
		(*it)->Update(gameTime_);
	}
}

/**
 * 
 */
void World::WorldComponent::Draw()
{
	for (std::vector<BaseEntity *>::const_iterator it = m_pWorld->GetEntities().begin();
		it != m_pWorld->GetEntities().end();
		it++)
	{
		(*it)->Draw();
	}
}

} // namespace CasaEngine
