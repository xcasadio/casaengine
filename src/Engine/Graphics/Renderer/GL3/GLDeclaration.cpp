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
#include "GLDeclaration.h"


namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
////////////////////////////////////////////////////////////
GLDeclaration::GLDeclaration() :
m_Elements(8)
{

}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
GLDeclaration::~GLDeclaration()
{

}


/////////////////////////////////////////////////////////////
/// Ajoute la description d'un élément
///
/// \param Stream :  Numéro du stream
/// \param Element : Element à ajouter
///
////////////////////////////////////////////////////////////
void GLDeclaration::AddElement(unsigned int Stream, const GLDeclaration::TElement& Element)
{
    m_Elements[Stream].push_back(Element);
}


/////////////////////////////////////////////////////////////
/// Renvoie la description d'un stream de la déclaration
///
/// \param Stream : Numéro du stream
///
/// \return Référence constante sur la tableau des éléments du stream
///
////////////////////////////////////////////////////////////
const GLDeclaration::TElementArray& GLDeclaration::GetStreamElements(unsigned int Stream) const
{
    return m_Elements[Stream];
}

} // namespace CasaEngine
