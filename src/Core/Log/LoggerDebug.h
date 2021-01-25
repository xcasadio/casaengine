#ifndef LOGGERDEBUG_H
#define LOGGERDEBUG_H

#include <Log/Logger.h>
#include "Logger.h"
#include "LogVerbose.h"

namespace CasaEngine
{
	class CA_EXPORT CLoggerDebug : public ILogger
	{
	private:
		void Write(TLogVerbosity verbose_, const std::string& Message) override;
	};
}

#endif // LOGGERDEBUG_H
