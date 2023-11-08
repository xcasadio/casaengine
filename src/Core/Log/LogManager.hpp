#pragma once

#include  "Logger.hpp"
#include "CA_Export.hpp"
#include  "LogVerbose.hpp"

#include <vector>

#define Logging CasaEngine::LogManager::Instance()
#define CA_TRACE(format, ...) Logging.Log(CasaEngine::Trace, format, ##__VA_ARGS__)
#define CA_DEBUG(format, ...) Logging.Log(CasaEngine::Debug, format, ##__VA_ARGS__)
#define CA_INFO(format, ...) Logging.Log(CasaEngine::Info, format, ##__VA_ARGS__)
#define CA_WARN(format, ...) Logging.Log(CasaEngine::Warning, format, ##__VA_ARGS__)
#define CA_ERROR(format, ...) Logging.Log(CasaEngine::Error, format, ##__VA_ARGS__)
#define CA_FATAL(format, ...) Logging.Log(CasaEngine::Fatal, format, ##__VA_ARGS__)

namespace CasaEngine
{
	class CA_EXPORT LogManager
	{
	public:
		static LogManager& Instance();
		static void Destroy();

		void AddLogger(ILogger* logger);
		void RemoveLogger(const ILogger* logger);

		TLogVerbosity getVerbosity() const;
		void setVerbosity(TLogVerbosity val);

		void Log(TLogVerbosity verbose, const char* format, ...);

	private:
		LogManager();
		~LogManager();

	private:
		static LogManager* _instance;

		TLogVerbosity _verbosity;
		std::vector<ILogger*> _logs;
	};
}
