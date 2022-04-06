#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <string>

#include "CA_Export.h"

#include "LogVerbose.h"

namespace CasaEngine
{
	class CA_EXPORT ILogger
	{
	public:
		virtual ~ILogger();
		virtual void Write(TLogVerbosity verbose_, const std::string& Message) = 0;
	};
}

#endif
