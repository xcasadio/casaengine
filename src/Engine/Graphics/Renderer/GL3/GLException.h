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

#ifndef GLEXCEPTION_H
#define GLEXCEPTION_H

//==========================================================
// En-têtes
//==========================================================
#include "Exceptions.h"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    /// Exceptions lancées par le renderer OpenGL
    /////////////////////////////////////////////////////////////
    class GLException : public CException
    {
    public :

        //----------------------------------------------------------
        // Constructeur
        //----------------------------------------------------------
        GLException(const std::string& GLFonction, const std::string& CasaEngineFunction) :
        CException((std::string("Renderer OpenGL\n\nEchec de ") + GLFonction + " dans la fonction " + CasaEngineFunction).c_str())
        {
        }
    };

} // namespace CasaEngine


#endif // GLEXCEPTION_H
