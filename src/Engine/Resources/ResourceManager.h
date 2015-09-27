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

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

//==========================================================
// En-têtes
//==========================================================

#include "Resources/Resource.h"
#include "Singleton.h"
#include <map>
#include <string>


namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Gestionnaire des ressources associées à un fichier
    ////////////////////////////////////////////////////////////
    class CA_EXPORT ResourceManager : 
		public CSingleton<ResourceManager>
    {
    MAKE_SINGLETON(ResourceManager)

    public :

        //----------------------------------------------------------
        // Récupère une ressource
        //----------------------------------------------------------
        template <class T> T* Get(const char *pName_) const;

        //----------------------------------------------------------
        // Ajoute une ressource
        //----------------------------------------------------------
        void Add(const char *pName, IResource* Resource);

        //----------------------------------------------------------
        // Retire une ressource
        //----------------------------------------------------------
        void Remove(const std::string& Name);

		/**
		 * destroy (delete) all resources
		 */
		void Clear();

		//#ifdef EDITOR

		void Rename(const std::string& newName_, IResource* Resource);

		//#endif // EDITOR

    private :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        ResourceManager();

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        ~ResourceManager();
	
        //----------------------------------------------------------
        // Types
        //----------------------------------------------------------
        typedef std::map<std::string, IResource*> TResourcesMap;

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        TResourcesMap m_Resources; ///< Table contenant les ressources associées à leur nom de fichier
    };

    #include "ResourceManager.inl"

} // namespace CasaEngine


#endif // RESOURCEMANAGER_H
