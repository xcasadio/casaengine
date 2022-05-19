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

	void World::AddEntity(BaseEntity* entity_)
	{
#ifdef EDITOR
		for (const auto e : _entities)
		{
			if (std::strcmp(entity_->GetName(), e->GetName()) == 0)
			{
				std::ostringstream oss;
				oss << "World::AddEntity() : entity " << e->GetName() << " (" << e->Id() << ")" << " is already added";
				throw ArgumentException(oss.str());
			}
		}
#endif
		_entities.push_back(entity_);
		
	}

	void World::RemoveEntity(const BaseEntity* entity)
	{
		for (auto it = _entities.begin(); it != _entities.end(); ++it)
		{
			if (std::strcmp(entity->GetName(), (*it)->GetName()) == 0)
			{
				_entities.erase(it); // TODO : not optimal !!! prefer nullptr ??
				break;
			}
		}
	}

	IPhysicsWorld& World::GetPhysicsWorld() const
	{
		return *_physicsWorld;
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
