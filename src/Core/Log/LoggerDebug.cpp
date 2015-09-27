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

#include <windows.h>

#include "Base.h"
#include <Log/LoggerDebug.h>




namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Log un message
///
/// \param Message : Message à inscrire
///
////////////////////////////////////////////////////////////
void CLoggerDebug::Write(TLogVerbosity verbose_, const std::string& Message)
{
	std::string str = "";

	switch(verbose_)
	{
	case Trace:
		str = "[TRACE] - ";
		break;
	case Debug:
		str = "[DEBUG] - ";
		break;
	case Info:
		str = "[INFO] - ";
		break;
	case Warning:
		str = "[WARNING] - ";
		break;
	case Error:
		str = "[ERROR] - ";
		break;
	}

	str += Message;

    OutputDebugString((str + '\n').c_str());
}

} // namespace CasaEngine
