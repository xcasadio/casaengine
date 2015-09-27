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

#ifndef GLDECLARATION_H
#define GLDECLARATION_H

#include <vector>

#include "Graphics/Vertices/Declaration.h"
#include "Graphics/Vertices/DeclarationElement.h"


namespace CasaEngine
{
    /////////////////////////////////////////////////////////////
    // Spécialisation OpenGL des déclarations de vertex
    /////////////////////////////////////////////////////////////
    class GLDeclaration : public IDeclaration
    {
    public :

        //----------------------------------------------------------
        // Types
        //----------------------------------------------------------
        struct TElement
        {
            DeclarationElement::TElementUsage Usage;
            DeclarationElement::TElementType  Type;
            unsigned int  Offset;
        };
        typedef std::vector<TElement>      TElementArray;
        typedef std::vector<TElementArray> TElementMatrix;

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        GLDeclaration();

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        ~GLDeclaration();

        //----------------------------------------------------------
        // Ajoute la description d'un élément
        //----------------------------------------------------------
        void AddElement(unsigned int Stream, const TElement& Element);

        //----------------------------------------------------------
        // Renvoie la description d'un stream de la déclaration
        //----------------------------------------------------------
        const TElementArray& GetStreamElements(unsigned int Stream) const;

    private :

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        TElementMatrix m_Elements; ///< Description de la déclaration
    };

} // namespace CasaEngine


#endif // GLDECLARATION_H
