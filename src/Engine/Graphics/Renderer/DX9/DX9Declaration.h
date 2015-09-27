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

#ifndef DX9DECLARATION_H
#define DX9DECLARATION_H

//==========================================================
// En-t�tes
//==========================================================
#include "Graphics/Vertices/Declaration.h"


//==========================================================
// D�clarations anticip�es
//==========================================================
struct IDirect3DVertexDeclaration9;


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    // Sp�cialisation DirectX9 des d�clarations de vertex
    /////////////////////////////////////////////////////////////
    class DX9Declaration : public IDeclaration
    {
    public :

        //----------------------------------------------------------
        // Constructeur par d�faut
        //----------------------------------------------------------
        DX9Declaration(IDirect3DVertexDeclaration9* Declaration);

        //----------------------------------------------------------
        // Renvoie la d�claration Dx9
        //----------------------------------------------------------
        IDirect3DVertexDeclaration9* GetDeclaration() const;

    private :

        //----------------------------------------------------------
        // Donn�es membres
        //----------------------------------------------------------
        SmartPtr<IDirect3DVertexDeclaration9, CResourceCOM> m_Declaration; ///< Pointeur sur la d�claration Dx9
    };

} // namespace CasaEngine


#endif // DX9DECLARATION_H
