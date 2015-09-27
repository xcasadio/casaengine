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

#include "MediaManager.h"
#include "Singleton.h"

#if CA_PLATFORM_WINDOWS
#	include <windows.h>
#endif


#include "IO/IOManager.h"
#include "IO/IFile.h"

namespace CasaEngine
{

////////////////////////////////////////////////////////////
// Implémentation des méthodes du singleton
////////////////////////////////////////////////////////////
SINGLETON_IMPL(MediaManager)


/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
MediaManager::MediaManager()
{

#if CA_PLATFORM_WINDOWS

    m_Paths.insert("");

	char szDir[MAX_PATH + 1];
	DWORD dw = GetCurrentDirectory(MAX_PATH, szDir);
	if (dw == 0)
	{
		dw = GetLastError();
		// Handle error
	}

	m_RootPath.append(szDir);
	m_RootPath.append("\\");

#endif

}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
MediaManager::~MediaManager()
{

}


/////////////////////////////////////////////////////////////
/// Ajoute un répertoire de recherche pour les médias
///
/// \param Path : Chemin à ajouter
///
////////////////////////////////////////////////////////////
void MediaManager::AddSearchPath(const char* path_)
{
	std::string Path = path_;

    if (Path.empty() || (*Path.rbegin() == '\\') || (*Path.rbegin() == '/'))
        m_Paths.insert(Path);
    else
        m_Paths.insert(Path + "\\");
}

/**
 * 
 */
IFile *MediaManager::FindMedia(const std::string& fileName_, bool isBinary_) const
{
	return FindMedia(fileName_.c_str(), isBinary_);
}

/////////////////////////////////////////////////////////////
/// Cherche un fichier dans les répertoires de recherche
///
/// \param Filename : Chemin du media
///
/// \return Chemin complet du media, exception si non trouvé
///
////////////////////////////////////////////////////////////
IFile *MediaManager::FindMedia(const char *fileName_, bool isBinary_) const
{
    for (std::set<std::string>::const_iterator i = m_Paths.begin(); 
		i != m_Paths.end(); 
		++i)
    {
		std::string path = m_RootPath + *i + fileName_;
		//TODO : set if open in BINARY MODE or not
        IFile *pRetFile = IOManager::OpenFile(path, FileMode::READ | (isBinary_ == true ? FileMode::BINARY : 0));

        if (pRetFile->Exists() == true)
		{
            return pRetFile;
		}
		else
		{
			DELETE_AO pRetFile;
		}
    }

    return nullptr;
}

} // namespace CasaEngine
