#pragma once

#include <sstream>
#include <string>

#include "CA_Export.h"

#include "LogVerbose.h"

namespace CasaEngine
{
	class CA_EXPORT ILogger
	{
	public:
		virtual ~ILogger() = default;
		virtual void Write(TLogVerbosity verbose, const std::string& message) = 0;
	};
}
