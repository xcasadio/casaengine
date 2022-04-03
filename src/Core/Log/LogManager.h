#ifndef LOGMANAGER_H_
#define LOGMANAGER_H_

#include "Logger.h"
#include "CA_Export.h"
#include "LogVerbose.h"

#include <vector>

#include "Memory\MemoryAllocation.h"

#define Logging CasaEngine::LogManager::Instance()
#define CA_TRACE(format, ...) Logging.Log(CasaEngine::Trace, format, ##__VA_ARGS__)
#define CA_DEBUG(format, ...) Logging.Log(CasaEngine::Debug, format, ##__VA_ARGS__)
#define CA_INFO(format, ...) Logging.Log(CasaEngine::Info, format, ##__VA_ARGS__)
#define CA_WARN(format, ...) Logging.Log(CasaEngine::Warning, format, ##__VA_ARGS__)
#define CA_ERROR(format, ...) Logging.Log(CasaEngine::Error, format, ##__VA_ARGS__)
#define CA_FATAL(format, ...) Logging.Log(CasaEngine::Fatal, format, ##__VA_ARGS__)

namespace CasaEngine
{
	class CA_EXPORT LogManager :
		public AllocatedObject<LogManager>
	{
	public:
		static LogManager& Instance();
		static void Destroy();

		void AddLogger(ILogger* logger_);
		void RemoveLogger(ILogger* logger_);

		TLogVerbosity getVerbosity() const;
		void setVerbosity(TLogVerbosity val);

		void Log(TLogVerbosity verbose_, const char* Format, ...);

	private:
		LogManager();
		~LogManager();

	private:
		static LogManager* m_sInstance;

		TLogVerbosity m_Verbosity;
		std::vector<ILogger*> m_Logs;
	};
}

#endif
