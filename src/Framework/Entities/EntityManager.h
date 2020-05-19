#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>

#include <string>
#include "CA_Export.h"

#include "EventHandler\EventArgs.h"

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT EntityManager
	{
		public:
			typedef std::map<int, BaseEntity*> EntityMap;
			typedef EntityMap::const_iterator EntityIterator; // typename only with msvc 2012+

		private:
			//to facilitate quick lookup the entities are stored in a std::map, in which
			//pointers to entities are cross referenced by their identifying number
			EntityMap m_EntityMap;

		public:
			~EntityManager();
		
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

//#ifdef EDITOR
	public:
		/**
			 * returns the first selected entity
			 */
		BaseEntity* GetFirstSelectedEntity() const;

		
//#endif
	};

}

#endif