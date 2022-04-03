#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>

#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT EntityManager : public AllocatedObject<EntityManager>
	{
		public:
			typedef std::map<int, BaseEntity*> EntityMap;
			typedef EntityMap::const_iterator EntityIterator; // typename only with msvc 2012+

		private:
			EntityMap m_EntityMap;

		public:
			~EntityManager();
		
			void RegisterEntity(BaseEntity* NewEntity);
			BaseEntity* GetEntityFromID(int id) const;
			
			EntityMap::const_iterator cbegin() const;
			EntityMap::const_iterator cend() const;


			void RemoveEntity(BaseEntity* pEntity);
			void Clear();

#ifdef EDITOR
	public:
		BaseEntity* GetFirstSelectedEntity() const;
#endif
	};

}

#endif