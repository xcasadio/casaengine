#ifndef CASAENGINE_DEBUG_H_
#define CASAENGINE_DEBUG_H_

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID
#	include <android/log.h>
#elif CA_PLATFORM_WINRT || CA_PLATFORM_WINDOWS || CA_PLATFORM_XBOX360
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char* _str);
#elif CA_PLATFORM_IOS || CA_PLATFORM_OSX
#	if defined(__OBJC__)
#		import <Foundation/NSObjCRuntime.h>
#	else
#		include <CoreFoundation/CFString.h>
extern "C" void NSLog(CFStringRef _format, ...);
#	endif // defined(__OBJC__)
#else
#	include <stdio.h>
#endif // CA_PLATFORM_WINDOWS

namespace CasaEngine
{

#if CA_COMPILER_CLANG_ANALYZER
	inline __attribute__((analyzer_noreturn)) void debugBreak();
#endif // CA_COMPILER_CLANG_ANALYZER

	inline void debugBreak()
	{
#if CA_COMPILER_MSVC
		__debugbreak();
#elif CA_CPU_ARM
		asm("bkpt 0");
#elif CA_CPU_X86 && (CA_COMPILER_GCC || CA_COMPILER_CLANG)
		// NaCl doesn't like int 3:
		// NativeClient: NaCl module load failed: Validation failure. File violates Native Client safety rules.
		__asm__("int $3");
#else // cross platform implementation
		int* int3 = (int*)3L;
		*int3 = 3;
#endif // BX
	}

	inline void debugOutput(const char* _out)
	{
#if CA_PLATFORM_ANDROID
		__android_log_write(ANDROID_LOG_DEBUG, "", _out);
#elif CA_PLATFORM_WINRT || CA_PLATFORM_WINDOWS || CA_PLATFORM_XBOX360
		OutputDebugStringA(_out);
#elif CA_PLATFORM_IOS || CA_PLATFORM_OSX
#	if defined(__OBJC__)
		NSLog(@"%s", _out);
#	else
		NSLog(__CFStringMakeConstantString("%s"), _out);
#	endif // defined(__OBJC__)
#else
		fputs(_out, stdout);
		fflush(stdout);
#endif // CA_PLATFORM_WINDOWS
	}

}

#endif
