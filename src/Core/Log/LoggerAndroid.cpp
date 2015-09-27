
#include "Base.h"
#include "LogVerbose.h"
#include "LoggerAndroid.h"

#include <android/log.h>
#include <string>

namespace CasaEngine
{

/**
 *
 */
void LoggerAndroid::Write(TLogVerbosity verbose_, const std::string& msg_)
{
	__android_log_write((android_LogPriority)verbose_, "CasaEngine", msg_.c_str());
}

} // namespace CasaEngine
