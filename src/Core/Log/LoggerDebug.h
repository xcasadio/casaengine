#pragma once

#include <Log/Logger.h>
#include "LogVerbose.h"

namespace CasaEngine
{
	class CA_EXPORT LoggerDebug : public ILogger
	{
	private:
		void Write(TLogVerbosity verbose, const std::string& message) override;
	};
}
