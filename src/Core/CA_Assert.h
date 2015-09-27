#ifndef CA_ASSERT_H_
#define CA_ASSERT_H_

#include "CompilationConfig.h"

//#define CA_STATIC_ASSERT(_condition, ...) static_assert(_condition, "" __VA_ARGS__)
//#define CA_ASSERT(_condition, ...) typedef char CA_CONCATENATE(CA_STATIC_ASSERT_, __LINE__)[1][(_condition)] CA_ATTRIBUTE(unused)

#ifdef CA_DEBUGGING

//#include "Log/LogManager.h"
#include "Macro.h"
#include "debug.h"

// #ifndef CA_ERROR
// 	#error Please include LogManager.h before include CA_Assert.h
// #endif

#	define CA_ASSERT(x, format, ...) \
	CA_MACRO_BLOCK_BEGIN \
	if (!(x)) { CA_ERROR("assert: " CA_STRINGIZE(format) " in " CA_FILE_LINE_LITERAL, ##__VA_ARGS__); \
	CasaEngine::debugBreak(); } \
	CA_MACRO_BLOCK_END

#else
#   define CA_ASSERT( x, format, ...)
#endif // CA_DEBUGGING


#endif // CA_ASSERT_H_