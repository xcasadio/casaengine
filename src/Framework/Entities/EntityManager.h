#pragma once

#include <map>
#include "CA_Export.h"

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT EntityManager
	{
	public:
		~EntityManager();

		void RegisterEntity(BaseEntity* NewEntity);
		BaseEntity* GetEntityFromID(int id) const;
		BaseEntity* GetEntityFromName(const char *name) const;

		std::map<int, BaseEntity*>::const_iterator begin() const;
		std::map<int, BaseEntity*>::const_iterator end() const;


		void RemoveEntity(BaseEntity* pEntity);
		void Clear();

	private:
		std::map<int, BaseEntity*> m_EntityMap;


#ifdef EDITOR
	public:
		BaseEntity* GetFirstSelectedEntity() const;
#endif
	};

}
