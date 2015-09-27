#ifndef GAMEPLAYDLLEXPORT_H_
#define GAMEPLAYDLLEXPORT_H_

#include "SystemPlatform.h"

#if CA_PLATFORM_WINDOWS

#	ifdef GAMEPLAYDLL_EXPORTS
#		define GAMEPLAYDLL_EXPORT __declspec(dllexport)
#	else
#		define GAMEPLAYDLL_EXPORT __declspec(dllimport)
#	endif // ifdef LIBRARY_CORE_EXPORTS

#elif CA_PLATFORM_ANDROID

#	define GAMEPLAYDLL_EXPORT 

#else

// Unsupported system
#	error This operating system is not supported by CasaEngine.Core library

#endif // #if CA_PLATFORM_WINDOWS


#endif // GAMEPLAYDLLEXPORT_H_