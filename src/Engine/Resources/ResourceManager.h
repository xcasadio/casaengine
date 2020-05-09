#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Resources/Resource.h"

#include <map>
#include <string>

namespace CasaEngine
{
	class CA_EXPORT ResourceManager
	{
	public:
		~ResourceManager();
		
		template <class T> T* Get(const char* pName_) const;
		void Add(const char* pName, IResource* Resource);
		void Remove(const std::string& Name);
		void Clear();

//#ifdef EDITOR
		void Rename(const std::string& newName_, IResource* Resource);
//#endif // EDITOR

	private:
		typedef std::map<std::string, IResource*> TResourcesMap;
		TResourcesMap m_Resources;
	};

#include "ResourceManager.inl"
}

#endif 
