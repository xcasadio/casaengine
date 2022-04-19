#include "Base.h"
#include "Log/LogManager.h"
#include "EntityManager.h"
#include "BaseEntity.h"

#include "CA_Assert.h"
#include "World/World.h"

namespace CasaEngine
{
	EntityManager::~EntityManager()
	{
		Clear();
	}
	
	BaseEntity* EntityManager::GetEntityFromID(int id)const
	{
		//find the entity
		auto ent = m_EntityMap.find(id);

		//assert that the entity is a member of the map
		CA_ASSERT(ent != m_EntityMap.end(), "<EntityManager::GetEntityFromID>: invalid ID")

		return ent->second;
	}

	BaseEntity* EntityManager::GetEntityFromName(const char* name) const
	{
		for (auto pair : m_EntityMap)
		{
			if (std::string(pair.second->GetName()) == std::string(name))
			{
				return pair.second;
			}
		}

		return nullptr;
	}

	EntityManager::EntityIterator EntityManager::cbegin() const
	{
		return m_EntityMap.cbegin();
	}

	EntityManager::EntityIterator EntityManager::cend() const
	{
		return m_EntityMap.cend();
	}

	void EntityManager::RemoveEntity(BaseEntity* pEntity)
	{
		m_EntityMap.erase(m_EntityMap.find(pEntity->ID()));
	}

	void EntityManager::RegisterEntity(BaseEntity* NewEntity)
	{
		m_EntityMap.insert(std::make_pair(NewEntity->ID(), NewEntity));
	}

	void EntityManager::Clear()
	{
		std::vector<BaseEntity*> worlds;

		//we need to delete world after
		//because world contains the physics world
		//and some entity can use this physics world when they are deleted
		for (auto it = m_EntityMap.begin();
		     it != m_EntityMap.end();
		     ++it)
		{
			if (dynamic_cast<World*>((*it).second) != nullptr)
			{
				worlds.push_back((*it).second);
			}
			else
			{
				delete(*it).second;
			}

			(*it).second = nullptr;
		}

		m_EntityMap.clear();

		for (auto* world : worlds)
		{
			delete world;
		}
	}

#ifdef EDITOR
	BaseEntity* EntityManager::GetFirstSelectedEntity() const
	{
		for (auto pair : m_EntityMap)
		{
			if (pair.second->IsSelected() == true)
			{
				return pair.second;
			}
		}

		return nullptr;
	}

#endif
}
