#ifndef MACRO_H_
#define MACRO_H_

#include "SystemPlatform.h"
#include "debug.h"

namespace CasaEngine
{
	/*
	// http://cnicholson.net/2011/01/stupid-c-tricks-a-better-sizeof_array/
	template<typename T, size_t N> char (&COUNTOF_REQUIRES_ARRAY_ARGUMENT(const T(&)[N]) )[N];
	#define CA_COUNTOF(_x) sizeof(CasaEngine::COUNTOF_REQUIRES_ARRAY_ARGUMENT(_x) )

	// Template for avoiding MSVC: C4127: conditional expression is constant
	template<bool>
	inline bool isEnabled()
	{
		return true;
	}

	template<>
	inline bool isEnabled<false>()
	{
		return false;
	}
	#define CA_ENABLED(_x) CasaEngine::isEnabled<!!(_x)>()

	inline bool ignoreC4127(bool _x)
	{
		return _x;
	}
	#define CA_IGNORE_C4127(_x) CasaEngine::ignoreC4127(!!(_x) )
	*/
	
	/*template<typename Ty>
	inline void swap(Ty& _a, Ty& _b)
	{
		Ty tmp = _a; _a = _b; _b = tmp;
	}*/
	
	///
#if CA_COMPILER_MSVC
	// Workaround MSVS bug...
#	define CA_VA_ARGS_PASS(...) CA_VA_ARGS_PASS_1_ __VA_ARGS__ CA_VA_ARGS_PASS_2_
#	define CA_VA_ARGS_PASS_1_ (
#	define CA_VA_ARGS_PASS_2_ )
#else
#	define CA_VA_ARGS_PASS(...) (__VA_ARGS__)
#endif // CA_COMPILER_MSVC

#define CA_VA_ARGS_COUNT(...) CA_VA_ARGS_COUNT_ CA_VA_ARGS_PASS(__VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define CA_VA_ARGS_COUNT_(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11, _a12, _a13, _a14, _a15, _a16, _last, ...) _last

	///
#define CA_MACRO_DISPATCHER(_func, ...) CA_MACRO_DISPATCHER_1_(_func, CA_VA_ARGS_COUNT(__VA_ARGS__) )
#define CA_MACRO_DISPATCHER_1_(_func, _argCount) CA_MACRO_DISPATCHER_2_(_func, _argCount)
#define CA_MACRO_DISPATCHER_2_(_func, _argCount) CA_CONCATENATE(_func, _argCount)

	///
#define CA_MAKEFOURCC(_a, _b, _c, _d) ( ( (uint32_t)(_a) | ( (uint32_t)(_b) << 8) | ( (uint32_t)(_c) << 16) | ( (uint32_t)(_d) << 24) ) )

	///
#define CA_STRINGIZE(_x) CA_STRINGIZE_(_x)
#define CA_STRINGIZE_(_x) #_x

	///
#define CA_CONCATENATE(_x, _y) CA_CONCATENATE_(_x, _y)
#define CA_CONCATENATE_(_x, _y) _x ## _y

	///
#define CA_FILE_LINE_LITERAL "" __FILE__ "(" CA_STRINGIZE(__LINE__) "): "

	///
#define CA_ALIGN_MASK(_value, _mask) ( ( (_value)+(_mask) ) & ( (~0)&(~(_mask) ) ) )
#define CA_ALIGN_16(_value) CA_ALIGN_MASK(_value, 0xf)
#define CA_ALIGN_256(_value) CA_ALIGN_MASK(_value, 0xff)
#define CA_ALIGN_4096(_value) CA_ALIGN_MASK(_value, 0xfff)

#define CA_ALIGNOF(_type) __alignof(_type)
/*
#if CA_COMPILER_GCC || CA_COMPILER_CLANG
#	define CA_ALIGN_DECL(_align, _decl) _decl __attribute__( (aligned(_align) ) )
#	define CA_ALLOW_UNUSED __attribute__( (unused) )
#	define CA_FORCE_INLINE __extension__ static __inline __attribute__( (__always_inline__) )
#	define CA_FUNCTION __PRETTY_FUNCTION__
#	define CA_NO_INLINE __attribute__( (noinline) )
#	define CA_NO_RETURN __attribute__( (noreturn) )
#	define CA_NO_VTABLE
#	define CA_OVERRIDE
#	define CA_PRINTF_ARGS(_format, _args) __attribute__ ( (format(__printf__, _format, _args) ) )
#	if CA_COMPILER_CLANG && (CA_PLATFORM_OSX || CA_PLATFORM_IOS
#		define CA_THREAD // not supported right now
#	else
#		define CA_THREAD __thread
#	endif // CA_COMPILER_CLANG
#	define CA_ATTRIBUTE(_x) __attribute__( (_x) )
#	if CA_COMPILER_MSVC_COMPATIBLE
#		define __stdcall
#	endif // CA_COMPILER_MSVC_COMPATIBLE
#elif CA_COMPILER_MSVC
#	define CA_ALIGN_DECL(_align, _decl) __declspec(align(_align) ) _decl
#	define CA_ALLOW_UNUSED
#	define CA_FORCE_INLINE __forceinline
#	define CA_FUNCTION __FUNCTION__
#	define CA_NO_INLINE __declspec(noinline)
#	define CA_NO_RETURN
#	define CA_NO_VTABLE __declspec(novtable)
#	define CA_OVERRIDE override
#	define CA_PRINTF_ARGS(_format, _args)
#	define CA_THREAD __declspec(thread)
#	define CA_ATTRIBUTE(_x)
#else
#	error "Unknown CA_COMPILER_?"
#endif
*/
#if defined(__has_extension)
#	define CA_CLANG_HAS_EXTENSION(_x) __has_extension(_x)
#else
#	define CA_CLANG_HAS_EXTENSION(_x) 0
#endif // defined(__has_extension)

	///
#define CA_ALIGN_DECL_16(_decl) CA_ALIGN_DECL(16, _decl)
#define CA_ALIGN_DECL_256(_decl) CA_ALIGN_DECL(256, _decl)
#define CA_ALIGN_DECL_CACHE_LINE(_decl) CA_ALIGN_DECL(CA_CACHE_LINE_SIZE, _decl)

	///
#define CA_MACRO_BLOCK_BEGIN for(;;) {
#define CA_MACRO_BLOCK_END break; }
#define CA_NOOP(...) CA_MACRO_BLOCK_BEGIN CA_MACRO_BLOCK_END


	///
#define CA_UNUSED_1(_a1) CA_MACRO_BLOCK_BEGIN (void)(true ? (void)0 : ( (void)(_a1) ) ); CA_MACRO_BLOCK_END
#define CA_UNUSED_2(_a1, _a2) CA_UNUSED_1(_a1); CA_UNUSED_1(_a2)
#define CA_UNUSED_3(_a1, _a2, _a3) CA_UNUSED_2(_a1, _a2); CA_UNUSED_1(_a3)
#define CA_UNUSED_4(_a1, _a2, _a3, _a4) CA_UNUSED_3(_a1, _a2, _a3); CA_UNUSED_1(_a4)
#define CA_UNUSED_5(_a1, _a2, _a3, _a4, _a5) CA_UNUSED_4(_a1, _a2, _a3, _a4); CA_UNUSED_1(_a5)
#define CA_UNUSED_6(_a1, _a2, _a3, _a4, _a5, _a6) CA_UNUSED_5(_a1, _a2, _a3, _a4, _a5); CA_UNUSED_1(_a6)
#define CA_UNUSED_7(_a1, _a2, _a3, _a4, _a5, _a6, _a7) CA_UNUSED_6(_a1, _a2, _a3, _a4, _a5, _a6); CA_UNUSED_1(_a7)
#define CA_UNUSED_8(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8) CA_UNUSED_7(_a1, _a2, _a3, _a4, _a5, _a6, _a7); CA_UNUSED_1(_a8)
#define CA_UNUSED_9(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9) CA_UNUSED_8(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8); CA_UNUSED_1(_a9)
#define CA_UNUSED_10(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10) CA_UNUSED_9(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9); CA_UNUSED_1(_a10)
#define CA_UNUSED_11(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11) CA_UNUSED_10(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10); CA_UNUSED_1(_a11)
#define CA_UNUSED_12(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11, _a12) CA_UNUSED_11(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8, _a9, _a10, _a11); CA_UNUSED_1(_a12)

#if CA_COMPILER_MSVC
	// Workaround MSVS bug...
#	define CA_UNUSED(...) CA_MACRO_DISPATCHER(CA_UNUSED_, __VA_ARGS__) CA_VA_ARGS_PASS(__VA_ARGS__)
#else
#	define CA_UNUSED(...) CA_MACRO_DISPATCHER(CA_UNUSED_, __VA_ARGS__)(__VA_ARGS__)
#endif // CA_COMPILER_MSVC

	///
#if CA_COMPILER_CLANG
#	define CA_PRAGMA_DIAGNOSTIC_PUSH_CLANG()      _Pragma("clang diagnostic push")
#	define CA_PRAGMA_DIAGNOSTIC_POP_CLANG()       _Pragma("clang diagnostic pop")
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_CLANG(_x) _Pragma(CA_STRINGIZE(clang diagnostic ignored _x) )
#else
#	define CA_PRAGMA_DIAGNOSTIC_PUSH_CLANG()
#	define CA_PRAGMA_DIAGNOSTIC_POP_CLANG()
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_CLANG(_x)
#endif // CA_COMPILER_CLANG

#if CA_COMPILER_GCC
#	define CA_PRAGMA_DIAGNOSTIC_PUSH_GCC()        _Pragma("GCC diagnostic push")
#	define CA_PRAGMA_DIAGNOSTIC_POP_GCC()         _Pragma("GCC diagnostic pop")
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_GCC(_x)   _Pragma(CA_STRINGIZE(GCC diagnostic ignored _x) )
#else
#	define CA_PRAGMA_DIAGNOSTIC_PUSH_GCC()
#	define CA_PRAGMA_DIAGNOSTIC_POP_GCC()
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_GCC(_x)
#endif // CA_COMPILER_GCC

#if CA_COMPILER_MSVC
#	define CA_PRAGMA_DIAGNOSTIC_PUSH_MSVC()      __pragma(warning(push) )
#	define CA_PRAGMA_DIAGNOSTIC_POP_MSVC()       __pragma(warning(pop) )
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(_x) __pragma(warning(disable:_x) )
#else
#	define CA_PRAGMA_DIAGNOSTIC_PUSH_MSVC()
#	define CA_PRAGMA_DIAGNOSTIC_POP_MSVC()
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(_x)
#endif // CA_COMPILER_CLANG

#if CA_COMPILER_CLANG
#	define CA_PRAGMA_DIAGNOSTIC_PUSH              CA_PRAGMA_DIAGNOSTIC_PUSH_CLANG
#	define CA_PRAGMA_DIAGNOSTIC_POP               CA_PRAGMA_DIAGNOSTIC_POP_CLANG
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC CA_PRAGMA_DIAGNOSTIC_IGNORED_CLANG
#elif CA_COMPILER_GCC
#	define CA_PRAGMA_DIAGNOSTIC_PUSH              CA_PRAGMA_DIAGNOSTIC_PUSH_GCC
#	define CA_PRAGMA_DIAGNOSTIC_POP               CA_PRAGMA_DIAGNOSTIC_POP_GCC
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC CA_PRAGMA_DIAGNOSTIC_IGNORED_GCC
#elif CA_COMPILER_MSVC
#	define CA_PRAGMA_DIAGNOSTIC_PUSH              CA_PRAGMA_DIAGNOSTIC_PUSH_MSVC
#	define CA_PRAGMA_DIAGNOSTIC_POP	              CA_PRAGMA_DIAGNOSTIC_POP_MSVC
#	define CA_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC(_x)
#endif // CA_COMPILER_

	///
#define CA_TYPE_IS_POD(_type) (!__is_class(_type) || __is_pod(_type) )

	///
#define CA_CLASS_NO_DEFAULT_CTOR(_class) \
private: _class()

#define CA_CLASS_NO_COPY(_class) \
private: _class(const _class& _rhs)

#define CA_CLASS_NO_ASSIGNMENT(_class) \
private: _class& operator=(const _class& _rhs)

#define CA_CLASS_ALLOCATOR(_class) \
public: void* operator new(size_t _size); \
public: void  operator delete(void* _ptr); \
public: void* operator new[](size_t _size); \
public: void  operator delete[](void* _ptr)

#define CA_CLASS_1(_class, _a1) CA_CONCATENATE(CA_CLASS_, _a1)(_class)
#define CA_CLASS_2(_class, _a1, _a2) CA_CLASS_1(_class, _a1); CA_CLASS_1(_class, _a2)
#define CA_CLASS_3(_class, _a1, _a2, _a3) CA_CLASS_2(_class, _a1, _a2); CA_CLASS_1(_class, _a3)
#define CA_CLASS_4(_class, _a1, _a2, _a3, _a4) CA_CLASS_3(_class, _a1, _a2, _a3); CA_CLASS_1(_class, _a4)

#if CA_COMPILER_MSVC
#	define CA_CLASS(_class, ...) CA_MACRO_DISPATCHER(CA_CLASS_, __VA_ARGS__) CA_VA_ARGS_PASS(_class, __VA_ARGS__)
#else
#	define CA_CLASS(_class, ...) CA_MACRO_DISPATCHER(CA_CLASS_, __VA_ARGS__)(_class, __VA_ARGS__)
#endif // CA_COMPILER_MSVC

}

namespace std { namespace tr1{}; using namespace tr1; }

#endif // MACRO_H_