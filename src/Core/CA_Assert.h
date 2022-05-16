#pragma once

#include "CompilationConfig.h"

//#define CA_STATIC_ASSERT(_condition, ...) static_assert(_condition, "" __VA_ARGS__)
//#define CA_ASSERT(_condition, ...) typedef char CA_CONCATENATE(CA_STATIC_ASSERT_, __LINE__)[1][(_condition)] CA_ATTRIBUTE(unused)

#ifdef CA_DEBUGGING

#include "debug.h"

#define CA_STRINGIZE(_x) CA_STRINGIZE_(_x)
#define CA_STRINGIZE_(_x) #_x
#define CA_FILE_LINE_LITERAL "" __FILE__ "(" CA_STRINGIZE(__LINE__) "): "

#define CA_ASSERT(x, format, ...) \
for(;;) { \
if (!(x)) { CA_ERROR("assert: " CA_STRINGIZE(format) " in " CA_FILE_LINE_LITERAL, ##__VA_ARGS__); \
CasaEngine::debugBreak(); } \
break; \
}

#else
#   define CA_ASSERT( x, format, ...)
#endif
