#ifndef CASAENGINE_DEBUG_H_
#define CASAENGINE_DEBUG_H_

#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID
#	include <android/log.h>
#elif CA_PLATFORM_WINDOWS
//extern "C" __declspec(dllimport) void __stdcall OutputDebugString(const char* _str);
#elif CA_PLATFORM_IOS || CA_PLATFORM_OSX
#	if defined(__OBJC__)
#		import <Foundation/NSObjCRuntime.h>
#	else
#		include <CoreFoundation/CFString.h>
extern "C" void NSLog(CFStringRef _format, ...);
#	endif // defined(__OBJC__)
#else
#	include <stdio.h>
#endif

namespace CasaEngine
{
	inline void debugBreak()
	{
		__debugbreak();
	}

	inline void debugOutput(const char* _out)
	{
#if CA_PLATFORM_ANDROID
		__android_log_write(ANDROID_LOG_DEBUG, "", _out);
#elif CA_PLATFORM_WINDOWS
		OutputDebugStringA(_out);
#else
		fputs(_out, stdout);
		fflush(stdout);
#endif
	}
}

#endif
