#pragma once

#include <Log/Logger.hpp>
#include  "LogVerbose.hpp"

namespace CasaEngine
{
	class CA_EXPORT LoggerDebug : public ILogger
	{
	private:
		void Write(TLogVerbosity verbose, const std::string& message) override;
	};
}
