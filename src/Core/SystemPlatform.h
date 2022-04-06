#pragma once

#define CA_PLATFORM_ANDROID    0
#define CA_PLATFORM_IOS        0
#define CA_PLATFORM_LINUX      0
#define CA_PLATFORM_OSX        0
#define CA_PLATFORM_WINDOWS    0

#define CA_PLATFORM_MOBILE 0
#define CA_PLATFORM_DESKTOP 0

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_WIN32) || defined(_WIN64)
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif // NOMINMAX
#	include <Windows.h>
#	if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#		undef  CA_PLATFORM_WINDOWS
#		if !defined(WINVER) && !defined(_WIN32_WINNT)
//				When building 64-bit target Win7 and above.
#			define WINVER 0x0601
#			define _WIN32_WINNT 0x0601
#		endif // !defined(WINVER) && !defined(_WIN32_WINNT)
#		define CA_PLATFORM_WINDOWS _WIN32_WINNT
#	endif
#elif defined(__ANDROID__)
// Android compiler defines __linux__
#	include <android/api-level.h>
#	undef  CA_PLATFORM_ANDROID
#	define CA_PLATFORM_ANDROID __ANDROID_API__
#elif defined(__linux__)
#	undef  CA_PLATFORM_LINUX
#	define CA_PLATFORM_LINUX 1
#elif defined(__ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__)
#	undef  CA_PLATFORM_IOS
#	define CA_PLATFORM_IOS 1
#elif defined(__ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__)
#	undef  CA_PLATFORM_OSX
#	define CA_PLATFORM_OSX 1
#else
#	error "CA_PLATFORM_* is not defined!"
#endif //

#define CA_PLATFORM_POSIX (0 \
	|| CA_PLATFORM_ANDROID \
	|| CA_PLATFORM_IOS \
	|| CA_PLATFORM_LINUX \
	|| CA_PLATFORM_OSX \
	)

#if CA_PLATFORM_ANDROID
#	define CA_PLATFORM_NAME "Android " \
	CA_STRINGIZE(CA_PLATFORM_ANDROID)
#elif CA_PLATFORM_IOS
#	define CA_PLATFORM_NAME "iOS"
#elif CA_PLATFORM_LINUX
#	define CA_PLATFORM_NAME "Linux"
#elif CA_PLATFORM_OSX
#	define CA_PLATFORM_NAME "OSX"
#elif CA_PLATFORM_WINDOWS
#	define CA_PLATFORM_NAME "Windows"
#endif

#if CA_PLATFORM_ANDROID || CA_PLATFORM_IOS
#	undef CA_PLATFORM_MOBILE
#	define CA_PLATFORM_MOBILE 1
#else
#	undef CA_PLATFORM_DESKTOP
#	define CA_PLATFORM_DESKTOP 1
#endif
