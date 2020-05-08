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

#ifndef LOADER_H
#define LOADER_H

//==========================================================
// En-têtes
//==========================================================

//#include <Config/Fwd.h>
#include "Exceptions.h"
#include <string>
#include "IO\IFile.h"


namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    // Classe de base pour les importateurs / exportateurs de medias
    ////////////////////////////////////////////////////////////
    template <class T>
    class ILoader :
		public AllocatedObject<ILoader<T> >
    {
    public :

        //----------------------------------------------------------
        // Destructeur
        //----------------------------------------------------------
        virtual ~ILoader() {}

        //----------------------------------------------------------
        // Charge un T à partir d'un fichier
        //----------------------------------------------------------
        virtual T* LoadFromFile(IFile *pFile_)
        {
            throw CLoadingFailed(pFile_->Filename(), "The registred loader can't load this file");
        }

		/**
		 * 
		 */
		/*virtual T* LoadFromBuffer(const char* pBuffer, unsigned long size_)
		{
			throw CLoadingFailed("", "The registred loader can't parse this buffer");
		}*/

        //----------------------------------------------------------
        // Enregistre un T dans un fichier
        //----------------------------------------------------------
        virtual void SaveToFile(const T* /*Object*/, const std::string& /*Filename*/)
        {
            throw CLoadingFailed("", "The registred loader can't save the datas");
        }

    protected :

        //----------------------------------------------------------
        // Constructeur - protégé : rend la classe abstraite
        //----------------------------------------------------------
        ILoader() {}
    };

}


#endif // LOADER_H
