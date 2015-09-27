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

#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <algorithm>
#include <cctype>
#include <map>
#include <set>
#include <string>

#include "Singleton.h"
#include "GenHierarchies.h"
#include "IO/IFile.h"
#include "StringUtils.h"

#include "Loaders/Loader.h"
#include "Graphics/Mesh/Mesh.h"

#include "Exceptions.h"
#include "Log/Logger.h"
#include "Log/LogManager.h"
#include "Parsers/Xml/tinyxml2.h"



namespace CasaEngine
{
    //==========================================================
    // Liste des médias pris en charge
    //==========================================================
    typedef TYPELIST_2(Mesh, tinyxml2::XMLDocument) MediaList;

    ////////////////////////////////////////////////////////////
    /// Modèle de gestionnaire de média
    ////////////////////////////////////////////////////////////
    template <class T>
    struct CMediaHolder
    {
        typedef std::map<std::string, ILoader<T> *> TLoadersMap;
        TLoadersMap m_Loaders; ///< Chargeurs de T associés à leur extension
    };

    ////////////////////////////////////////////////////////////
    /// Gestionnaire de médias - "empilement" de CMediaHolder pour chaque média
    ////////////////////////////////////////////////////////////
    class CA_EXPORT MediaManager : 
		public CSingleton<MediaManager>, 
		public CScatteredHierarchy<MediaList, CMediaHolder>
    {
    MAKE_SINGLETON(MediaManager)

    public :

        //----------------------------------------------------------
        // Ajoute un répertoire de recherche pour les médias
        //----------------------------------------------------------
        void AddSearchPath(const char* path_);

        //----------------------------------------------------------
        // Enregistre un nouveau chargeur de T
        //----------------------------------------------------------
        template <class T> void RegisterLoader(ILoader<T>* Loader, const char *Extensions);

        //----------------------------------------------------------
        // Supprime un chargeur de T
        //----------------------------------------------------------
        template <class T> void UnregisterLoader(const std::string& Extensions);

        //----------------------------------------------------------
        // Charge un T à partir d'un fichier
        //----------------------------------------------------------
        template <class T> T* LoadMediaFromFile(const std::string& Filename, unsigned int mode_) const;

        //----------------------------------------------------------
        // Sauvegarde un T dans un fichier
        //----------------------------------------------------------
        template <class T> void SaveMediaToFile(const T* Object, const IFile *Filename) const;

		/**
		 * Search a file in all registered directories
		 * @return nullptr if the file doesn't exist in all registered directories
		 */
		IFile *FindMedia(const char* fileName_, bool isBinary_) const;

		/**
		 * Search a file in all registered directories
		 * @return nullptr if the file doesn't exist in all registered directories
		 */
		IFile *FindMedia(const std::string& fileName_, bool isBinary_) const;

    private :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        MediaManager();

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        ~MediaManager();

        //----------------------------------------------------------
        // Cherche le loader correspondant à une extension donnée
        //----------------------------------------------------------
        template <class T> ILoader<T>& FindLoader(const IFile * Filename) const;

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        std::set<std::string> m_Paths; ///< Liste des chemins de recherche

		std::string m_RootPath; ///< Binary path
    };

    #include "MediaManager.inl"

} // namespace CasaEngine


#endif // MEDIAMANAGER_H
