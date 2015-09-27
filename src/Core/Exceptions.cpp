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

#include <sstream>

#include "Base.h"

#include <Exceptions.h>
#include <StringUtils.h>




namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Message : Message d'erreur
///
////////////////////////////////////////////////////////////
CException::CException(const std::string& Message) :
	m_Message(Message)
{

}


/////////////////////////////////////////////////////////////
/// Destructeur
///
////////////////////////////////////////////////////////////
CException::~CException() throw()
{

}


/////////////////////////////////////////////////////////////
/// Renvoie le message associé à l'exception
///
/// \return Pointeur sur le message
///
////////////////////////////////////////////////////////////
const char* CException::what() const throw()
{
    return m_Message.c_str();
}


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param File :    Fichier source contenant l'erreur
/// \param Line :    Ligne à laquelle se trouve l'erreur dans le fichier source
/// \param Message : Message d'erreur
///
////////////////////////////////////////////////////////////
CAssertException::CAssertException(const std::string& File, int Line, const std::string& Message) :
	CException(CStringBuilder(Message)(". ")(File)(" (")(Line)(")"))
{

}


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Ptr :      Adresse du bloc
/// \param File :     Fichier source
/// \param Line :     Ligne dans le fichier source
/// \param NewArray : Indique si le [] se trouve sur le new ou le delete
///
////////////////////////////////////////////////////////////
CBadDelete::CBadDelete(const void* Ptr, const std::string& File, int Line, bool NewArray) :
	CException(CStringBuilder("Bad des/allocation ")((NewArray ? "new[] / delete" :  "new / delete[]"))(" found")(". ")("Memory address : 0x")(Ptr)("\nSource file : ")(File)(" (")(Line)(")"))
{

}


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param File :    Fichier
/// \param Message : Message d'erreur
///
////////////////////////////////////////////////////////////
CLoadingFailed::CLoadingFailed(const std::string& File, const std::string& Message) :
	CException(CStringBuilder("Loading error '")(File)("'. ")(Message))
{

}


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Message : Message d'erreur
///
////////////////////////////////////////////////////////////
COutOfMemory::COutOfMemory(const std::string& Message) :
	CException(Message)
{

}


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Feature : Caractéristique non supportée
///
////////////////////////////////////////////////////////////
CUnsupported::CUnsupported(const std::string& Feature) :
	CException(CStringBuilder("Unsupported functionality ")(Feature))
{

}


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Error : Message décrivant l'erreur
///
////////////////////////////////////////////////////////////
CBadConversion::CBadConversion(const std::string& Error) :
	CException(Error)
{

}

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Error : Message décrivant l'erreur
///
////////////////////////////////////////////////////////////
CArgumentNullException::CArgumentNullException(const std::string& Error) :
	CException(Error)
{

}

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Error : Message décrivant l'erreur
///
////////////////////////////////////////////////////////////
CArgumentException::CArgumentException(const std::string& Error) :
	CException(Error)
{

}

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Error : Message décrivant l'erreur
///
////////////////////////////////////////////////////////////
CArgumentOutOfRangeException::CArgumentOutOfRangeException(const std::string& Error) :
	CException(Error)
{

}


/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Error : Message décrivant l'erreur
///
////////////////////////////////////////////////////////////
CNotImplementedException::CNotImplementedException(const std::string& Error) :
	CException(Error)
{

}


/**
 * 
 */
CUnknownObjectException::CUnknownObjectException( const std::string& Error ) :
	CException(Error)
{

}

} // namespace CasaEngine
