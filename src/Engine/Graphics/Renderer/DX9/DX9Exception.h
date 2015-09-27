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

#ifndef DX9EXCEPTION_H
#define DX9EXCEPTION_H

//==========================================================
// En-têtes
//==========================================================
#include "Exceptions.h"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    /// Exceptions lancées par le renderer DirectX9
    /////////////////////////////////////////////////////////////
    class DX9Exception : public CException
    {
    public :

        //----------------------------------------------------------
        // Constructeur
        //----------------------------------------------------------
        DX9Exception(const std::string& DX9Fonction, const std::string& CasaEngineFunction) :
        CException((std::string("Renderer DirectX9\n\nEchec de ") + DX9Fonction + " dans la fonction " + CasaEngineFunction).c_str())
        {
        }
    };

} // namespace CasaEngine


#endif // DX9EXCEPTION_H
