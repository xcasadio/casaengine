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

#include "Resources/Resource.h"
#include <Resources/ResourceManager.h>



namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
IResource::IResource() :
	m_Name    (""),
	m_RefCount(1)
{

}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
IResource::~IResource()
{
    if (m_Name != "")
        ResourceManager::Instance().Remove(m_Name);
}


/////////////////////////////////////////////////////////////
/// Renvoie le nom associé à la ressource
///
/// \return Nom attribué à la ressource
///
////////////////////////////////////////////////////////////
const std::string& IResource::GetName() const
{
    return m_Name;
}


/////////////////////////////////////////////////////////////
/// Ajoute une référence sur la ressource
///
////////////////////////////////////////////////////////////
void IResource::AddRef()
{
    ++m_RefCount;
}


/////////////////////////////////////////////////////////////
/// Retire une référence sur la ressource
///
/// \return Nombre de références restantes sur la ressource
///
////////////////////////////////////////////////////////////
int IResource::Release()
{
    int RefCount = --m_RefCount;

    if (RefCount == 0)
        DELETE_AO this;

    return RefCount;
}

}
