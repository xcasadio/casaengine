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

#ifndef FILE_H
#define FILE_H

//==========================================================
// En-têtes
//==========================================================

#include "CA_Export.h"
#include "IO/IFile.h"
#include <string>
#include <iosfwd>
#include <fstream>      // std::fstream

namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Classe facilitant la manipulation des noms de fichiers
    ////////////////////////////////////////////////////////////
    class CA_EXPORT File : public IFile
    {
    public :

		/**
		 *
		 */
        File();
		File(const File& rsh);
		const File& operator = (const File& rsh);

		/**
         * 
         */
        ~File();

		/**
		 * 
		 */
		bool Open(const char* fileName_, unsigned int mode_);
		
		/**
		 * 
		 */
		bool Create(const char* fileName_, bool append_);
		
		/**
		 *
		 */
		void Close();

        /**
         * 
         */
        bool Exists() const;

		/**
		 * 
		 */
        int Read(char *dst_, unsigned int size_);
		
		/**
		 * 
		 */
        int Write(char *data_, unsigned int size_);

		/**
		 * 
		 */
		unsigned int Seek(unsigned int off_, SeekDir::TSeekDir dir_);

	protected:
		/**
		 *
		 */
		void FillBuffer();

    private :

		std::fstream m_Stream;
	};

} // namespace CasaEngine


#endif // FILE_H
