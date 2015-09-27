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

#include "Log\LogManager.h"

/////////////////////////////////////////////////////////////
/// Enregistre un nouveau chargeur de media de type T
///
/// \param Loader :     Pointeur sur le chargeur
/// \param Extensions : Extensions associ�es au chargeur
///
////////////////////////////////////////////////////////////
template <class T>
inline void MediaManager::RegisterLoader(ILoader<T>* Loader, const char *Extensions)
{
    std::vector<std::string> Ext;
    Split(Extensions, Ext, " /\\*.,;|-_\t\n'\"");

    ILoader<T> *Ptr = Loader;
    for (std::vector<std::string>::iterator i = Ext.begin(); i != Ext.end(); ++i)
	{
		CMediaHolder<T>::m_Loaders[ToLower(*i)] = Ptr;
	}
}


////////////////////////////////////////////////////////////
/// Supprime un chargeur
///
/// \param Extensions : Extensions associ�es au chargeur
///
////////////////////////////////////////////////////////////
template <class T>
inline void MediaManager::UnregisterLoader(const std::string& Extensions)
{
    // R�cup�ration des extensions
    std::vector<std::string> Ext;
    Split(Extensions, Ext, " /\\*.,;|-_\t\n'\"");

    // Suppression du chargeur pour chaque extension
    for (std::vector<std::string>::iterator i = Ext.begin(); i != Ext.end(); ++i)
        CMediaHolder<T>::m_Loaders.erase(ToLower(*i));
}


/////////////////////////////////////////////////////////////
/// Charge un media de type T � partir d'un fichier
///
/// \param Filename : Chemin du fichier
///
/// \return Pointeur sur le T charg�
///
////////////////////////////////////////////////////////////
template <class T>
inline T* MediaManager::LoadMediaFromFile(const std::string& Filename, unsigned int mode_) const
{
    // Recherche du fichier dans les r�pertoires enregistr�s
    IFile *MediaPath = FindMedia(Filename, mode_);

	if (MediaPath == nullptr)
	{
		throw CLoadingFailed(Filename, "MediaManager::LoadMediaFromFile() : Can't find the file (maybe add a reference to the right directory ?)");
	}

    // On d�l�gue le boulot au loader appropri�
    T* Media = FindLoader<T>(MediaPath).LoadFromFile(MediaPath);

	if (Media == nullptr)
	{
		CA_DEBUG("Error when load the resource: '%s'\n", MediaPath->Fullname().c_str());
	}
	else
	{
		CA_DEBUG("Resource loaded : '%s'\n", MediaPath->Fullname().c_str());
		DELETE_AO MediaPath; // TODO : crash if called
	}

    return Media;
}


/////////////////////////////////////////////////////////////
/// Sauvegarde un T dans un fichier
///
/// \param Object :   Pointeur sur l'objet � sauvegarder
/// \param Filename : Nom du fichier � cr�er
///
////////////////////////////////////////////////////////////
template <class T>
inline void MediaManager::SaveMediaToFile(const T* Object, const IFile *Filename) const
{
    // On d�l�gue le boulot au loader appropri�
    FindLoader<T>(Filename).SaveToFile(Object, Filename->Fullname());

    // Loggization de la sauvegarde
    CA_DEBUG("Resource saved : %s\n", Filename->Fullname().c_str());
}


/////////////////////////////////////////////////////////////
/// Cherche le loader correspondant � un fichier donn�
///
/// \param Filename : Fichier
///
/// \return R�f�rence sur le loader, exception si non-trouv�
///
////////////////////////////////////////////////////////////
template <class T>
inline ILoader<T>& MediaManager::FindLoader(const IFile *Filename) const
{
    typename CMediaHolder<T>::TLoadersMap::const_iterator It = 
		CMediaHolder<T>::m_Loaders.find(ToLower(Filename->Extension()));

    if ((It != CMediaHolder<T>::m_Loaders.end()) && It->second)
        return *It->second;

    throw CLoadingFailed(Filename->Fullname(), "No loader found for this type of file");
}
