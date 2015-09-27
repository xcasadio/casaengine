
#ifndef TYPES_H_
#define TYPES_H_

#if CA_PLATFORM_ANDROID
/*
////////////////////////////////////////////
//
// Chars
//
////////////////////////////////////////////
typedef char char8_t;
typedef unsigned char uchar8_t;

////////////////////////////////////////////
//
// Signed Integers
//
////////////////////////////////////////////
typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

////////////////////////////////////////////
//
// Unsigned Integers
//
////////////////////////////////////////////
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

////////////////////////////////////////////
//
// Floats
//
////////////////////////////////////////////
typedef float float32_t;
typedef double float64_t;

////////////////////////////////////////////
//
// Booleans
//
////////////////////////////////////////////
typedef unsigned char bool8_t;
typedef unsigned short bool16_t;
typedef unsigned int bool32_t;
typedef unsigned long long bool64_t;

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef NULL
#undef NULL
#endif
#define NULL 0

// Define _STDINT_H to prevent compiler clashes from that file being included elsewhere
#define _STDINT_H
*/
#elif CA_PLATFORM_WINDOWS

#include <cstdint>

////////////////////////////////////////////
//
// Chars
//
////////////////////////////////////////////
typedef char char8_t;
typedef unsigned char uchar8_t;

////////////////////////////////////////////
//
// Floats
//
////////////////////////////////////////////
typedef float float32_t;
typedef double float64_t;

////////////////////////////////////////////
//
// Booleans
//
////////////////////////////////////////////
typedef unsigned char bool8_t;
typedef unsigned short bool16_t;
typedef unsigned int bool32_t;
typedef unsigned long long bool64_t;

#ifdef TRUE
#undef TRUE
#endif
#define TRUE 1

#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

////////////////////////////////////////////
//
// Pointers
//
////////////////////////////////////////////

// Define NULL pointer value
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif

////////////////////////////////////////////////////////////
// Define portable fixed-size types
////////////////////////////////////////////////////////////
#include <climits>

namespace CasaEngine
{
	// 8 bits integer types
#if UCHAR_MAX == 0xFF
	typedef signed   char Int8;
	typedef unsigned char Uint8;
#else
#error No 8 bits integer type for this platform
#endif

	// 16 bits integer types
#if USHRT_MAX == 0xFFFF
	typedef signed   short Int16;
	typedef unsigned short Uint16;
#elif UINT_MAX == 0xFFFF
	typedef signed   int Int16;
	typedef unsigned int Uint16;
#elif ULONG_MAX == 0xFFFF
	typedef signed   long Int16;
	typedef unsigned long Uint16;
#else
#error No 16 bits integer type for this platform
#endif

	// 32 bits integer types
#if USHRT_MAX == 0xFFFFFFFF
	typedef signed   short Int32;
	typedef unsigned short Uint32;
#elif UINT_MAX == 0xFFFFFFFF
	typedef signed   int Int32;
	typedef unsigned int Uint32;
#elif ULONG_MAX == 0xFFFFFFFF
	typedef signed   long Int32;
	typedef unsigned long Uint32;
#else
#error No 32 bits integer type for this platform
#endif

} // namespace casaEngine

#endif // TYPES_H_
