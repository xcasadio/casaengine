#include <windows.h>

#include "Base.h"
#include <Log/LoggerDebug.h>

namespace CasaEngine
{
	void CLoggerDebug::Write(TLogVerbosity verbose_, const std::string& Message)
	{
		std::string str = "";

		switch (verbose_)
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
		case Error:
			str = "[ERROR] - ";
			break;
		default:
			str = "[UNKNOWN] - ";;
		}

		str += Message;

		OutputDebugString((str + '\n').c_str());
	}
}