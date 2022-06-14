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

		void RegisterEntity(BaseEntity* entity);
		BaseEntity* GetEntityFromId(unsigned int id) const;
		BaseEntity* GetEntityFromName(const char *name) const;

		std::map<unsigned int, BaseEntity*>::const_iterator begin() const;
		std::map<unsigned int, BaseEntity*>::const_iterator end() const;


		void RemoveEntity(BaseEntity* entity);
		void Clear();

	private:
		std::map<unsigned int, BaseEntity*> _entityMap;


#ifdef EDITOR
	public:
		BaseEntity* GetFirstSelectedEntity() const;
#endif
	};

}
