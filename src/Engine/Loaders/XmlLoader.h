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

#ifndef _XMLLOADER_H
#define _XMLLOADER_H

//==========================================================
// En-têtes
//==========================================================

#include "CA_Export.h"

#include "Loaders/Loader.h"


#include "Parsers/Xml/tinyxml2.h"
#include "IO/IFile.h"


namespace CasaEngine
{
    /**
     * 
     */
    class CA_EXPORT XmlLoader : 
		public ILoader<tinyxml2::XMLDocument>
    {
    public :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        XmlLoader();

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        ~XmlLoader();

        //----------------------------------------------------------
        // Charge une image à partir d'un fichier
        //----------------------------------------------------------
        tinyxml2::XMLDocument* LoadFromFile(IFile *pFile_);

        //----------------------------------------------------------
        // Enregistre une image dans un fichier
        //----------------------------------------------------------
        virtual void SaveToFile(const tinyxml2::XMLDocument* Object, const std::string& Filename);
    };

} // namespace CasaEngine


#endif // _XMLLOADER_H
