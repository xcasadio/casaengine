//==========================================================
// CasaEngine - Free C++ 3D engine
//==========================================================

#ifndef CA_EXPORT_H
#define CA_EXPORT_H


#include "SystemPlatform.h"

#if CA_PLATFORM_WINDOWS

#ifdef CA_DLL

#	ifdef CA_EXPORTS
#		define CA_EXPORT __declspec(dllexport)
#	else
#		define CA_EXPORT __declspec(dllimport)
#	endif // ifdef LIBRARY_CORE_EXPORTS

#else

#	define CA_EXPORT

#endif // CA_DLL

#elif CA_PLATFORM_ANDROID

#	define CA_EXPORT 

#else

	// Unsupported system
#	error This operating system is not supported by CasaEngine library

#endif // #if CA_PLATFORM_WINDOWS


//==========================================================
// Désactivation de warnings "gênants" de Visual C++
//
// 4251 : "T1 nécessite une interface DLL pour être utilisé(e)
//         par les clients de class T2" 
// 4661 : "Aucune définition appropriée pour la demande
//         d'instanciation explicite du modèle"
//==========================================================
#ifdef _MSC_VER
#   pragma warning(disable : 4251)
#   pragma warning(disable : 4661)
#endif


#endif // LIBRARY_CORE_EXPORT_H
