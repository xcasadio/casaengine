#pragma once

#include "SystemPlatform.hpp"

#if CA_PLATFORM_WINDOWS

#ifdef CA_DLL
#	ifdef CA_EXPORTS
#		define CA_EXPORT __declspec(dllexport)
#	else
#		define CA_EXPORT __declspec(dllimport)
#	endif
#else
#	define CA_EXPORT
#endif

#elif CA_PLATFORM_ANDROID
#	define CA_EXPORT
#else
#	error This operating system is not supported by CasaEngine library
#endif

#ifdef _MSC_VER
#   pragma warning(disable : 4251)
#   pragma warning(disable : 4661)
#endif
