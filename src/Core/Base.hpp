#pragma once

#include  "SystemPlatform.hpp"
#include  "CA_Assert.hpp"
#include "CA_Export.hpp"

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
