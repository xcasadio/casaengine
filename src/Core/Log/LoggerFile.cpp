#include "Base.h"

#include <Log/LoggerFile.h>
#include <Exceptions.h>
#include "LogManager.h"
#include "LogVerbose.h"
#include "DateTime.h"
#include "Version.h"

#include "CA_Assert.h"

namespace CasaEngine
{
	LoggerFile::LoggerFile(const char* filename) :
		_file(filename),
		_tempBuffer{}
	{
		if (!_file)
		{
			throw LoadingFailed(filename, "LoggerFile()");
		}
	}

	LoggerFile::~LoggerFile()
	{
		_file.close();
	}

	void LoggerFile::Write(TLogVerbosity verbose, const std::string& message)
	{
		std::string str;

		switch (verbose)
		{
		case Trace:
			str = "[TRACE]";
			break;
		case Debug:
			str = "[DEBUG]";
			break;
		case Info:
			str = "[INFO]";
			break;
		case Warning:
			str = "[WARNING]";
			break;
		case Error:
			str = "[ERROR]";
			break;
		case Fatal:
			str = "[FATAL]";
			break;
		}

		str = DateTime::Now().GetCurrentTime() + ">" + str + ": " + message;

		Write(str);
	}

	void LoggerFile::Write(const std::string& message)
	{
		CA_ASSERT(_file.is_open(), "LoggerFile::Write() : file is not open")

			_file << message << std::flush;
	}
}