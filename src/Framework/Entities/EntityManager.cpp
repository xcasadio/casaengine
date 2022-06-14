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
	
	BaseEntity* EntityManager::GetEntityFromId(unsigned int id)const
	{
		//find the entity
		auto ent = _entityMap.find(id);

		//assert that the entity is a member of the map
		CA_ASSERT(ent != _entityMap.end(), "<EntityManager::GetEntityFromID>: invalid Id")

		return ent->second;
	}

	BaseEntity* EntityManager::GetEntityFromName(const char* name) const
	{
		for (auto& pair : _entityMap)
		{
			if (std::string(pair.second->GetName()) == std::string(name))
			{
				return pair.second;
			}
		}

		return nullptr;
	}

	std::map<unsigned int, BaseEntity*>::const_iterator EntityManager::begin() const
	{
		return _entityMap.begin();
	}

	std::map<unsigned int, BaseEntity*>::const_iterator EntityManager::end() const
	{
		return _entityMap.end();
	}

	void EntityManager::RemoveEntity(BaseEntity* entity)
	{
		_entityMap.erase(_entityMap.find(entity->Id()));
	}

	void EntityManager::RegisterEntity(BaseEntity* entity)
	{
		_entityMap.insert(std::make_pair(entity->Id(), entity));
	}

	void EntityManager::Clear()
	{
		std::vector<BaseEntity*> worlds;

		//we need to delete world after
		//because world contains the physics world
		//and some entity can use this physics world when they are deleted
		for (auto it = _entityMap.begin();
		     it != _entityMap.end();
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

		_entityMap.clear();

		for (const auto* world : worlds)
		{
			delete world;
		}
	}

#ifdef EDITOR
	BaseEntity* EntityManager::GetFirstSelectedEntity() const
	{
		for (const auto pair : _entityMap)
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
