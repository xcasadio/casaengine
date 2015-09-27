//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================


//==========================================================
// En-têtes
//==========================================================
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

////////////////////////////////////////////////////////////
// Implémentation des méthodes du singleton
////////////////////////////////////////////////////////////
SINGLETON_IMPL(ResourceManager)


/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
ResourceManager::ResourceManager()
{

}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
ResourceManager::~ResourceManager()
{
    // if resource are not destroy, we log them
    if (!m_Resources.empty())
    {
        CA_WARN("Some resources are not unloaded:\n");

        for (TResourcesMap::const_iterator i = m_Resources.begin(); i != m_Resources.end(); ++i)
        {
            CA_WARN("\t - %s\n", i->second->GetName().c_str());
        }
    }
}


/////////////////////////////////////////////////////////////
/// Ajoute une ressource
///
/// \param Name :     Nom associé à la ressource
/// \param Resource : Pointeur sur la ressource à ajouter
///
////////////////////////////////////////////////////////////
void ResourceManager::Add(const char *pName, IResource* Resource)
{
    CA_ASSERT(Resource != nullptr, "ResourceManager::Add() : resource is nullptr");

    // Si la ressource avait déjà été chargée, on le signale
    if (m_Resources.find(pName) != m_Resources.end())
        CA_WARN("ResourceManager::Add(): resource '%s' already loaded", pName);

    // Ajout de la ressource à la liste
    m_Resources[pName] = Resource;
    Resource->m_Name = pName;
}


/////////////////////////////////////////////////////////////
/// Retire une ressource
///
/// \param Name : Nom de la ressource à retirer
///
////////////////////////////////////////////////////////////
void ResourceManager::Remove(const std::string& Name)
{
    TResourcesMap::iterator It = m_Resources.find(Name);

    // Si la ressource n'avait pas été chargée, on le signale
    if (It == m_Resources.end())
	{
        CA_WARN("ResourceManager::Remove(): can't find the resource '%s'", Name.c_str());
	}
	else
	{
		m_Resources.erase(It);
	}
}

/**
 * 
 */
void ResourceManager::Clear()
{
	if (m_Resources.size() > 0)
	{
		m_Resources.begin()->second->Release();
		Clear(); // recursive
	}
}

/**
 * 
 */
void ResourceManager::Rename(const std::string& newName_, IResource* Resource)
{
	CA_ASSERT(Resource != nullptr, "ResourceManager::Rename() : resource is nullptr");

	TResourcesMap::iterator it = m_Resources.find(Resource->GetName());

	// Si la ressource avait déjà été chargée, on le signale
	if (it == m_Resources.end())
		CA_WARN("ResourceManager::Rename(): can't find resource '%s'", Resource->GetName().c_str());

	// Ajout de la ressource à la liste
	m_Resources.erase(it);
	m_Resources[newName_] = Resource;
	Resource->m_Name = newName_;
}


} // namespace CasaEngine
