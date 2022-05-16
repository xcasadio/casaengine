#pragma once
#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID
#	include <android/log.h>
#endif

namespace CasaEngine
{
	enum TLogVerbosity
	{
#if CA_PLATFORM_ANDROID

		Trace = ANDROID_LOG_VERBOSE,
		Debug = ANDROID_LOG_DEBUG,
		Info = ANDROID_LOG_INFO,
		Warning = ANDROID_LOG_WARN,
		Error = ANDROID_LOG_ERROR,
		Fatal = ANDROID_LOG_FATAL,
		None = ANDROID_LOG_SILENT
#else
		Trace,
		Debug,
		Info,
		Warning,
		Error,
		Fatal,
		None
#endif
	};
}
