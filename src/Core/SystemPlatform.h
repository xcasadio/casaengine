#ifndef SYSTEMPLATFORM_H_
#define SYSTEMPLATFORM_H_

#define CA_COMPILER_CLANG           0
#define CA_COMPILER_CLANG_ANALYZER  0
#define CA_COMPILER_GCC             0
#define CA_COMPILER_MSVC            0
#define CA_COMPILER_MSVC_COMPATIBLE 0

#define CA_PLATFORM_ANDROID    0
#define CA_PLATFORM_FREEBSD    0
#define CA_PLATFORM_IOS        0
#define CA_PLATFORM_LINUX      0
#define CA_PLATFORM_OSX        0
#define CA_PLATFORM_WINDOWS    0
#define CA_PLATFORM_WINRT      0
#define CA_PLATFORM_XBOX360    0

#define CA_CPU_ARM  0
#define CA_CPU_JIT  0
#define CA_CPU_MIPS 0
#define CA_CPU_PPC  0
#define CA_CPU_X86  0

#define CA_ARCH_32BIT 0
#define CA_ARCH_64BIT 0

#define CA_CPU_ENDIAN_BIG    0
#define CA_CPU_ENDIAN_LITTLE 0

#define CA_PLATFORM_MOBILE 0
#define CA_PLATFORM_DESKTOP 0

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
#if defined(__clang__)
// clang defines __GNUC__ or _MSC_VER
#	undef  CA_COMPILER_CLANG
#	define CA_COMPILER_CLANG (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#	if defined(__clang_analyzer__)
#		undef  CA_COMPILER_CLANG_ANALYZER
#		define CA_COMPILER_CLANG_ANALYZER 1
#	endif // defined(__clang_analyzer__)
#	if defined(_MSC_VER)
#		undef  CA_COMPILER_MSVC_COMPATIBLE
#		define CA_COMPILER_MSVC_COMPATIBLE _MSC_VER
#	endif // defined(_MSC_VER)
#elif defined(_MSC_VER)
#	undef  CA_COMPILER_MSVC
#	define CA_COMPILER_MSVC _MSC_VER
#	undef  CA_COMPILER_MSVC_COMPATIBLE
#	define CA_COMPILER_MSVC_COMPATIBLE _MSC_VER
#elif defined(__GNUC__)
#	undef  CA_COMPILER_GCC
#	define CA_COMPILER_GCC (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	error "CA_COMPILER_* is not defined!"
#endif //

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Architectures
#if defined(__arm__)     || \
	defined(__aarch64__) || \
	defined(_M_ARM)
#	undef  CA_CPU_ARM
#	define CA_CPU_ARM 1
#	define CA_CACHE_LINE_SIZE 64
#elif defined(__MIPSEL__)     || \
	defined(__mips_isa_rev) || \
	defined(__mips64)
#	undef  CA_CPU_MIPS
#	define CA_CPU_MIPS 1
#	define CA_CACHE_LINE_SIZE 64
#elif defined(_M_PPC)        || \
	defined(__powerpc__)   || \
	defined(__powerpc64__)
#	undef  CA_CPU_PPC
#	define CA_CPU_PPC 1
#	define CA_CACHE_LINE_SIZE 128
#elif defined(_M_IX86)    || \
	defined(_M_X64)     || \
	defined(__i386__)   || \
	defined(__x86_64__)
#	undef  CA_CPU_X86
#	define CA_CPU_X86 1
#	define CA_CACHE_LINE_SIZE 64
#else // PNaCl doesn't have CPU defined.
#	undef  CA_CPU_JIT
#	define CA_CPU_JIT 1
#	define CA_CACHE_LINE_SIZE 64
#endif //

#if defined(__x86_64__)    || \
	defined(_M_X64)        || \
	defined(__aarch64__)   || \
	defined(__64BIT__)     || \
	defined(__mips64)      || \
	defined(__powerpc64__) || \
	defined(__ppc64__)
#	undef  CA_ARCH_64BIT
#	define CA_ARCH_64BIT 64
#else
#	undef  CA_ARCH_32BIT
#	define CA_ARCH_32BIT 32
#endif //

#if CA_CPU_PPC
#	undef  CA_CPU_ENDIAN_BIG
#	define CA_CPU_ENDIAN_BIG 1
#else
#	undef  CA_CPU_ENDIAN_LITTLE
#	define CA_CPU_ENDIAN_LITTLE 1
#endif // CA_PLATFORM_

// http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
#if defined(_XBOX_VER)
#	undef  CA_PLATFORM_XBOX360
#	define CA_PLATFORM_XBOX360 1
#elif defined(_WIN32) || defined(_WIN64)
// http://msdn.microsoft.com/en-us/library/6sehtctf.aspx
#	ifndef NOMINMAX
#		define NOMINMAX
#	endif // NOMINMAX
#	include <windows.h>
#	if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
#		undef  CA_PLATFORM_WINDOWS
#		if !defined(WINVER) && !defined(_WIN32_WINNT)
#			if CA_ARCH_64BIT
//				When building 64-bit target Win7 and above.
#				define WINVER 0x0601
#				define _WIN32_WINNT 0x0601
#			else
//				Windows Server 2003 with SP1, Windows XP with SP2 and above
#				define WINVER 0x0502
#				define _WIN32_WINNT 0x0502
#			endif // CA_ARCH_64BIT
#		endif // !defined(WINVER) && !defined(_WIN32_WINNT)
#		define CA_PLATFORM_WINDOWS _WIN32_WINNT
#	else
#		undef  CA_PLATFORM_WINRT
#		define CA_PLATFORM_WINRT 1
#	endif
#elif defined(__VCCOREVER__)
// RaspberryPi compiler defines __linux__
#	undef  CA_PLATFORM_RPI
#	define CA_PLATFORM_RPI 1
#elif defined(__native_client__)
// NaCl compiler defines __linux__
#	include <ppapi/c/pp_macros.h>
#	undef  CA_PLATFORM_NACL
#	define CA_PLATFORM_NACL PPAPI_RELEASE
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
#elif defined(__FreeBSD__)
#	undef  CA_PLATFORM_FREEBSD
#	define CA_PLATFORM_FREEBSD 1
#else
#	error "CA_PLATFORM_* is not defined!"
#endif //

#define CA_PLATFORM_POSIX (0 \
	|| CA_PLATFORM_ANDROID \
	|| CA_PLATFORM_FREEBSD \
	|| CA_PLATFORM_IOS \
	|| CA_PLATFORM_LINUX \
	|| CA_PLATFORM_NACL \
	|| CA_PLATFORM_OSX \
	|| CA_PLATFORM_RPI \
	)

#ifndef  CA_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS
#	define CA_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS 0
#endif // CA_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS

#if CA_COMPILER_GCC
#	define CA_COMPILER_NAME "GCC " \
	CA_STRINGIZE(__GNUC__) "." \
	CA_STRINGIZE(__GNUC_MINOR__) "." \
	CA_STRINGIZE(__GNUC_PATCHLEVEL__)
#elif CA_COMPILER_CLANG
#	define CA_COMPILER_NAME "Clang " \
	CA_STRINGIZE(__clang_major__) "." \
	CA_STRINGIZE(__clang_minor__) "." \
	CA_STRINGIZE(__clang_patchlevel__)
#elif CA_COMPILER_MSVC
#	if CA_COMPILER_MSVC >= 1800
#		define CA_COMPILER_NAME "MSVC 12.0"
#	elif CA_COMPILER_MSVC >= 1700
#		define CA_COMPILER_NAME "MSVC 11.0"
#	elif CA_COMPILER_MSVC >= 1600
#		define CA_COMPILER_NAME "MSVC 10.0"
#	elif CA_COMPILER_MSVC >= 1500
#		define CA_COMPILER_NAME "MSVC 9.0"
#	else
#		define CA_COMPILER_NAME "MSVC"
#	endif //
#endif // CA_COMPILER_

#if CA_PLATFORM_ANDROID
#	define CA_PLATFORM_NAME "Android " \
	CA_STRINGIZE(CA_PLATFORM_ANDROID)
#elif CA_PLATFORM_FREEBSD
#	define CA_PLATFORM_NAME "FreeBSD"
#elif CA_PLATFORM_IOS
#	define CA_PLATFORM_NAME "iOS"
#elif CA_PLATFORM_LINUX
#	define CA_PLATFORM_NAME "Linux"
#elif CA_PLATFORM_NACL
#	define CA_PLATFORM_NAME "NaCl " \
	CA_STRINGIZE(CA_PLATFORM_NACL)
#elif CA_PLATFORM_OSX
#	define CA_PLATFORM_NAME "OSX"
#elif CA_PLATFORM_RPI
#	define CA_PLATFORM_NAME "RaspberryPi"
#elif CA_PLATFORM_WINDOWS
#	define CA_PLATFORM_NAME "Windows"
#elif CA_PLATFORM_WINRT
#	define CA_PLATFORM_NAME "WinRT"
#endif // CA_PLATFORM_

#if CA_CPU_ARM
#	define CA_CPU_NAME "ARM"
#elif CA_CPU_MIPS
#	define CA_CPU_NAME "MIPS"
#elif CA_CPU_PPC
#	define CA_CPU_NAME "PowerPC"
#elif CA_CPU_JIT
#	define CA_CPU_NAME "JIT-VM"
#elif CA_CPU_X86
#	define CA_CPU_NAME "x86"
#endif // CA_CPU_

#if CA_ARCH_32BIT
#	define CA_ARCH_NAME "32-bit"
#elif CA_ARCH_64BIT
#	define CA_ARCH_NAME "64-bit"
#endif // CA_ARCH_

#if CA_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && CA_COMPILER_MSVC
#	pragma warning(error:4062) // ENABLE warning C4062: enumerator'...' in switch of enum '...' is not handled
#	pragma warning(error:4121) // ENABLE warning C4121: 'symbol' : alignment of a member was sensitive to packing
//#	pragma warning(error:4127) // ENABLE warning C4127: conditional expression is constant
#	pragma warning(error:4130) // ENABLE warning C4130: 'operator' : logical operation on address of string constant
#	pragma warning(error:4239) // ENABLE warning C4239: nonstandard extension used : 'argument' : conversion from '*' to '* &' A non-const reference may only be bound to an lvalue
//#	pragma warning(error:4244) // ENABLE warning C4244: 'argument' : conversion from 'type1' to 'type2', possible loss of data
#	pragma warning(error:4245) // ENABLE warning C4245: 'conversion' : conversion from 'type1' to 'type2', signed/unsigned mismatch
#	pragma warning(error:4263) // ENABLE warning C4263: 'function' : member function does not override any base class virtual member function
#	pragma warning(error:4265) // ENABLE warning C4265: class has virtual functions, but destructor is not virtual
#	pragma warning(error:4431) // ENABLE warning C4431: missing type specifier - int assumed. Note: C no longer supports default-int
#	pragma warning(error:4545) // ENABLE warning C4545: expression before comma evaluates to a function which is missing an argument list
#	pragma warning(error:4549) // ENABLE warning C4549: 'operator' : operator before comma has no effect; did you intend 'operator'?
#	pragma warning(error:4701) // ENABLE warning C4701: potentially uninitialized local variable 'name' used
#	pragma warning(error:4706) // ENABLE warning C4706: assignment within conditional expression
#	pragma warning(error:4100) // ENABLE warning C4100: '' : unreferenced formal parameter
#	pragma warning(error:4189) // ENABLE warning C4189: '' : local variable is initialized but not referenced
#	pragma warning(error:4505) // ENABLE warning C4505: '' : unreferenced local function has been removed
#endif // CA_CONFIG_ENABLE_MSVC_LEVEL4_WARNINGS && CA_COMPILER_MSVC

// shorcut in order to detect if we are on desktop or not
#if CA_PLATFORM_ANDROID || CA_PLATFORM_IOS
#	undef CA_PLATFORM_MOBILE
#	define CA_PLATFORM_MOBILE 1
#else
#	undef CA_PLATFORM_DESKTOP
#	define CA_PLATFORM_DESKTOP 1
#endif

#endif // SYSTEMPLATFORM_H_
