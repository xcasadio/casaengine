#include <Windows.h>

#include <Log/LoggerDebug.hpp>

namespace CasaEngine
{
	void LoggerDebug::Write(const TLogVerbosity verbose, const std::string& message)
	{
		std::string str;

		switch (verbose)
		{
		case Trace:
			str = "[TRACE] - ";
			break;
		case Debug:
			str = "[DEBUG] - ";
			break;
		case Info:
			str = "[INFO] - ";
			break;
		case Warning:
			str = "[WARNING] - ";
			break;
		case Fatal:
		case Error:
			str = "[ERROR] - ";
			break;
		case None: break;
		default:
			str = "[UNKNOWN] - ";
		}

		str += message;

		OutputDebugString((str + '\n').c_str());
	}
}