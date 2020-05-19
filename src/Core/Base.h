#ifndef BASE_H_
#define BASE_H_

#include "SystemPlatform.h"
#include "Types.h"
#include "CA_Assert.h"

#if CA_PLATFORM_ANDROID

#	include <cstdarg>
#	include <stddef.h>
#	include <stdint.h>
#	include <stdio.h>

#elif CA_PLATFORM_IOS

#elif CA_PLATFORM_OSX

#elif CA_PLATFORM_WINDOWS

#	include <Windows.h>

#elif CA_PLATFORM_LINUX
#endif

#endif
