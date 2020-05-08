#include "Base.h"
#include "Log/LogManager.h"
#include "EntityManager.h"
#include "BaseEntity.h"
#include "Singleton.h"
#include "Macro.h"
#include "CA_Assert.h"
#include "World/World.h"

namespace CasaEngine
{
	SINGLETON_IMPL(EntityManager)


	//------------------------- GetEntityFromID -----------------------------------
	//-----------------------------------------------------------------------------
	BaseEntity* EntityManager::GetEntityFromID(int id)const
	{
		//find the entity
		EntityMap::const_iterator ent = m_EntityMap.find(id);

		//assert that the entity is a member of the map
		CA_ASSERT(ent != m_EntityMap.end(), "<EntityManager::GetEntityFromID>: invalid ID");

		return ent->second;
	}

	//------------------------- GetEntityIterator -----------------------------------
	//-----------------------------------------------------------------------------
	EntityManager::EntityIterator EntityManager::cbegin() const
	{
		return m_EntityMap.cbegin();
	}

	/**
	 * returns
	 */
	EntityManager::EntityIterator EntityManager::cend() const
	{
		return m_EntityMap.cend();
	}

	//--------------------------- RemoveEntity ------------------------------------
	//-----------------------------------------------------------------------------
	void EntityManager::RemoveEntity(BaseEntity* pEntity)
	{
		m_EntityMap.erase(m_EntityMap.find(pEntity->ID()));
	}

	//---------------------------- RegisterEntity ---------------------------------
	//-----------------------------------------------------------------------------
	void EntityManager::RegisterEntity(BaseEntity* NewEntity)
	{
		m_EntityMap.insert(std::make_pair(NewEntity->ID(), NewEntity));
	}

	/**
	 *
	 *
	void EntityManager::NotifyEvent(const Event* pEvent_)
	{
		EntityMap::iterator it;

		for (it = m_EntityMap.begin();
			it != m_EntityMap.end();
			it++)
		{
			(*it).second->GetComponentMgr()->HandleEvent(pEvent_);
		}
	}*/

	/**
	 *
	 */
	void EntityManager::Clear()
	{
		std::vector<BaseEntity*> worlds;

		EntityMap::iterator it;

		//we need to delete world after
		//because world contains the physics world
		//and some entity can use this physics world when they are deleted
		for (it = m_EntityMap.begin();
			it != m_EntityMap.end();
			it++)
		{
			if (dynamic_cast<World*>((*it).second) != nullptr)
			{
				worlds.push_back((*it).second);
			}
			else
			{
				DELETE_AO(*it).second;
			}

			(*it).second = nullptr;
		}

		m_EntityMap.clear();

		std::vector<BaseEntity*>::iterator itWorld;

		for (itWorld = worlds.begin();
			itWorld != worlds.end();
			itWorld++)
		{
			DELETE_AO* itWorld;
		}
	}

#ifdef EDITOR
	/**
	 * returns the first selected entity
	 */
	BaseEntity* EntityManager::GetFirstSelectedEntity() const
	{
		EntityIterator it;

		for (it = m_EntityMap.cbegin();
			it != m_EntityMap.cend();
			it++)
		{
			if (it->second->IsSelected() == true)
			{
				return it->second;
			}
		}

		return nullptr;
	}

#endif

}
