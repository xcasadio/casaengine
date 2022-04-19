#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include "CA_Export.h"

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT EntityManager
	{
	public:
		typedef std::map<int, BaseEntity*> EntityMap;
		typedef EntityMap::const_iterator EntityIterator;

	private:
		EntityMap m_EntityMap;

	public:
		~EntityManager();

		void RegisterEntity(BaseEntity* NewEntity);
		BaseEntity* GetEntityFromID(int id) const;
		BaseEntity* GetEntityFromName(const char *name) const;

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