#pragma once

#include "Log/Logger.h"
#include "Win32/Win32Exception.h"
#include "Log/LogManager.h"

namespace CasaEngine
{
#if defined(DEBUG) || defined(_DEBUG)
#define Win32Check(Func) (OnWin32Error((BOOL)(Func), #Func, __FILE__, __LINE__))
#else
#define Win32Check(Func) (Func)
#endif

	inline void OnWin32Error(BOOL res, const char* functionName_, const char* file, DWORD Line)
	{
		if (res == false && GetLastError() != 0)
		{
			Win32Exception win32Error;
			CA_ERROR("Win32 function (%s) error (%d) %s : (%d) %s\n",
				functionName_, win32Error.ErrorCode(), win32Error.Description(), Line, file);

			throw win32Error;
		}
	}
}
