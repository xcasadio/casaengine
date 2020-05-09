#include "Base.h"

#include "Resources/ResourceManager.h"
#include "Log/Logger.h"
#include "Log/LogManager.h"
#include "Exceptions.h"
#include <typeinfo>
#include "Macro.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	ResourceManager::~ResourceManager()
	{
		if (!m_Resources.empty())
		{
			CA_WARN("Some resources are not unloaded:\n");

			for (TResourcesMap::const_iterator i = m_Resources.begin(); i != m_Resources.end(); ++i)
			{
				CA_WARN("\t - %s\n", i->second->GetName().c_str());
			}
		}

		Clear();
	}

	void ResourceManager::Add(const char* pName, IResource* Resource)
	{
		CA_ASSERT(Resource != nullptr, "ResourceManager::Add() : resource is nullptr");

		if (m_Resources.find(pName) != m_Resources.end())
		{
			CA_WARN("ResourceManager::Add(): resource '%s' already loaded", pName);
		}

		m_Resources[pName] = Resource;
		Resource->m_Name = pName;
	}

	void ResourceManager::Remove(const std::string& Name)
	{
		TResourcesMap::iterator It = m_Resources.find(Name);

		if (It == m_Resources.end())
		{
			CA_WARN("ResourceManager::Remove(): can't find the resource '%s'", Name.c_str());
		}
		else
		{
			m_Resources.erase(It);
		}
	}

	void ResourceManager::Clear()
	{
		if (!m_Resources.empty())
		{
			m_Resources.begin()->second->Release();
			Clear();
		}
	}

	void ResourceManager::Rename(const std::string& newName_, IResource* Resource)
	{
		CA_ASSERT(Resource != nullptr, "ResourceManager::Rename() : resource is nullptr");

		TResourcesMap::iterator it = m_Resources.find(Resource->GetName());

		if (it == m_Resources.end())
		{
			CA_WARN("ResourceManager::Rename(): can't find resource '%s'", Resource->GetName().c_str());
		}

		m_Resources.erase(it);
		m_Resources[newName_] = Resource;
		Resource->m_Name = newName_;
	}

}
