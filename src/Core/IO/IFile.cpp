
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


#include "Base.h"

#include "IFile.h"
#include "Exceptions.h"

//


namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur à partir d'un std::string
///
/// \param Name : Chemin complet du fichier
///
////////////////////////////////////////////////////////////
IFile::IFile() : 
	m_BufferSize(0),
	m_pBuffer(nullptr)
{
	
}

/**
 * 
 */
IFile::IFile(const IFile& rsh) : 
	m_BufferSize(0),
	m_pBuffer(nullptr)
{
	*this = rsh;
}

/**
 * 
 */
const IFile& IFile::operator = (const IFile& rsh)
{
	m_Name = rsh.m_Name;

	if (rsh.m_BufferSize > 0 && rsh.m_pBuffer != nullptr)
	{
		FillBuffer();
	}

	return *this;
}

/**
 * 
 */
IFile::~IFile()
{
	DestroyBuffer();
}


/**
 * 
 */
char *IFile::GetBuffer()
{
	if (m_pBuffer == nullptr)
	{
		FillBuffer();
	}
	
	return m_pBuffer;
}

/**
 * 
 */
unsigned int IFile::GetBufferLength()
{
	if (m_pBuffer == nullptr)
	{
		FillBuffer();
	}

	return m_BufferSize;
}

/**
 * 
 */
void IFile::DestroyBuffer()
{
	if (m_pBuffer != nullptr)
	{
		delete[] m_pBuffer;
		m_pBuffer = nullptr;
	}
}


/**
 * 
 */
unsigned int IFile::Seek(unsigned int pos_)
{
	return Seek(pos_, SeekDir::SEEKDIR_SET);
}

/**
 *
 */
unsigned int IFile::Position() const
{
	throw CNotImplementedException("IFile::Position() not implemented");
}

/////////////////////////////////////////////////////////////
/// Renvoie le nom du fichier avec son chemin complet
///
/// \return Chemin complet du fichier
///
////////////////////////////////////////////////////////////
const std::string& IFile::Fullname() const
{
    return m_Name;
}


/////////////////////////////////////////////////////////////
/// Renvoie le nom du fichier sans son chemin
///
/// \return Nom du fichier
///
////////////////////////////////////////////////////////////
std::string IFile::Filename() const
{
    std::string::size_type Pos = m_Name.find_last_of("\\/");

    if (Pos != std::string::npos)
        return m_Name.substr(Pos + 1, std::string::npos);
    else
        return m_Name;
}


/////////////////////////////////////////////////////////////
/// Renvoie le nom du fichier sans extension ni chemin
///
/// \return Nom du fichier
///
////////////////////////////////////////////////////////////
std::string IFile::ShortFilename() const
{
    return Filename().substr(0, Filename().find_last_of("."));
}


/////////////////////////////////////////////////////////////
/// Renvoie l'extension du fichier
///
/// \return Extension du fichier
///
////////////////////////////////////////////////////////////
std::string IFile::Extension() const
{
    std::string::size_type Pos = m_Name.find_last_of(".");
    if (Pos != std::string::npos)
        return m_Name.substr(Pos + 1, std::string::npos);
    else
        return "";
}

} // namespace CasaEngine
