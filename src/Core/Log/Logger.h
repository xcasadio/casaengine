#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
#include <string>

#include "CA_Export.h"

#include "LogVerbose.h"
#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	class CA_EXPORT ILogger :
		public AllocatedObject<ILogger>
	{
	public:
		virtual ~ILogger();
		virtual void Write(TLogVerbosity verbose_, const std::string& Message) = 0;
	};
}

#endif // LOGGER_H
