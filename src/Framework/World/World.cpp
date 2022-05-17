#include "Base.h"
#include "World.h"
#include "Entities/BaseEntity.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "Physics/Bullet/BulletPhysicsWorld.h"

namespace CasaEngine
{
	World::World()
	{
		GetComponentMgr()->AddComponent(new WorldComponent(this));
		//TODO : create parameters
		_cellSpacePartition.Build(50, 50, 7, 7);

		_physicsWorld = Game::Instance().GetPhysicsEngine().CreateWorld();
	}

	World::~World()
	{
		delete _physicsWorld;
	}

	const std::vector<BaseEntity*>& World::GetEntities()
	{
		return _entities;
	}

	BaseEntity* World::GetEntityByName(const std::string& name)
	{
		for (const auto entity : _entities)
		{
			if (entity->GetName() == name)
			{
				return entity;
			}
		}

		return nullptr;
	}

	void World::AddEntity(BaseEntity* pEntity_)
	{
#ifdef EDITOR
		for (const auto entity : _entities)
		{
			if (std::strcmp(entity->GetName(), pEntity_->GetName()) == 0)
			{
				std::ostringstream oss;
				oss << "World::AddEntity() : entity " << pEntity_->GetName() << " (" << pEntity_->Id() << ")" << " is already added";
				throw ArgumentException(oss.str());
			}
		}
#endif
		_entities.push_back(pEntity_);
		
	}

	IPhysicsWorld& World::GetPhysicsWorld() const
	{
		return *_physicsWorld;
	}

	void World::Read(std::ifstream& is)
	{
	}

	void World::Write(std::ostream& os)
	{
	}

	CellSpacePartition<BaseEntity*>& World::GetSpacePartition()
	{
		return _cellSpacePartition;
	}

	//////////////////////////////////////////////////////////////////////////

	World::WorldComponent::WorldComponent(BaseEntity* pEntity_) :
		Component(pEntity_, WORLD),
		m_pWorld(dynamic_cast<World*>(pEntity_))
	{
		CA_ASSERT(m_pWorld != nullptr, "WorldComponent()");
	}

	void World::WorldComponent::Initialize()
	{		
		for (const auto entity : m_pWorld->GetEntities())
		{
			entity->Initialize();
		}
	}

	void World::WorldComponent::Update(const GameTime& gameTime_)
	{
		m_pWorld->GetPhysicsWorld().Update(gameTime_);

		for (auto it = m_pWorld->GetEntities().begin();
		     it != m_pWorld->GetEntities().end();
		     ++it)
		{
			(*it)->Update(gameTime_);
		}
	}

	void World::WorldComponent::Draw()
	{
		m_pWorld->GetPhysicsWorld().Draw();

		for (auto it = m_pWorld->GetEntities().begin();
		     it != m_pWorld->GetEntities().end();
		     ++it)
		{
			(*it)->Draw();
		}
	}
}
