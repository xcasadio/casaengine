#pragma once

#include <Log/Logger.h>
#include <fstream>
#include "LogVerbose.h"
#include "CA_Export.h"

namespace CasaEngine
{
	class CA_EXPORT LoggerFile : public ILogger
	{
	public:
		LoggerFile(const char* pFilename_ = "Output.log");
		~LoggerFile() override;

	private:
		void Write(TLogVerbosity verbose, const std::string& Message) override;
		void Write(const std::string& Message);

	private:
		std::ofstream m_File;
		char m_TempBuffer[32];
	};
}
