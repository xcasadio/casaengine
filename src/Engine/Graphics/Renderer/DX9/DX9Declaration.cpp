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
#include "DX9Declaration.h"
#include "DX9Renderer.h"
#include "Util.h"




namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
/// \param Declaration : Pointeur sur la déclaration Dx9
///
////////////////////////////////////////////////////////////
DX9Declaration::DX9Declaration(IDirect3DVertexDeclaration9* Declaration) :
m_Declaration(Declaration)
{

}


/////////////////////////////////////////////////////////////
/// Renvoie la déclaration Dx9
///
/// \return Pointeur sur la déclaration Dx9
///
////////////////////////////////////////////////////////////
IDirect3DVertexDeclaration9* DX9Declaration::GetDeclaration() const
{
    return m_Declaration;
}


} // namespace CasaEngine
