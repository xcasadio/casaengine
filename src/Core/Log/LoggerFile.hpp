#pragma once

#include <Log/Logger.hpp>
#include <fstream>
#include  "LogVerbose.hpp"
#include "CA_Export.hpp"

namespace CasaEngine
{
	class CA_EXPORT LoggerFile : public ILogger
	{
	public:
		LoggerFile(const char* filename = "Output.log");
		~LoggerFile() override;

	private:
		void Write(TLogVerbosity verbose, const std::string& message) override;
		void Write(const std::string& message);

		std::ofstream _file;
		char _tempBuffer[32];
	};
}
