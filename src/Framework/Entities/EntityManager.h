#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H


#pragma warning (disable:4786)
//------------------------------------------------------------------------
//
//  Name:   EntityManager.h
//
//  Desc:   Singleton class to handle the  management of Entities.          
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <map>

#include <string>
#include "CA_Export.h"
#include "Singleton.h"
#include "EventHandler\EventArgs.h"


namespace CasaEngine
{
	class BaseEntity;

	//provide easy access
	#define EntityMgr EntityManager::Instance()

	/*
	 *	
	 */
	class CA_EXPORT EntityManager : 
		public CSingleton<EntityManager>
	{
		MAKE_SINGLETON(EntityManager)

		public:
			typedef std::map<int, BaseEntity*> EntityMap;
			typedef EntityMap::const_iterator EntityIterator; // typename only with msvc 2012+

		private:
			//to facilitate quick lookup the entities are stored in a std::map, in which
			//pointers to entities are cross referenced by their identifying number
			EntityMap m_EntityMap;

		public:
			/**
			 * returns the first selected entity
			 */
			BaseEntity* GetFirstSelectedEntity() const;

			/**
			 * Entity at the index position indicated by the entity's ID
			 */
			void RegisterEntity(BaseEntity* NewEntity);

			/**
			 * returns a pointer to the entity with the ID given as a parameter
			 */
			BaseEntity* GetEntityFromID(int id)const;

			/**
			 * returns 
			 */
			EntityMap::const_iterator cbegin() const;

			/**
			 * returns 
			 */
			EntityMap::const_iterator cend() const;

			/**
			 * this method removes the entity from the list
			 */
			void RemoveEntity(BaseEntity* pEntity);

			/**
			 * Remove all registered entities and do a delete
			 */
			void Clear();
	};

} // namespace CasaEngine

#endif // ENTITYMANAGER_H