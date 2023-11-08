#include <cstdio>
#include <cstdarg>

#include  "Base.hpp"

#include  "CA_Assert.hpp"
#include  "LogManager.hpp"

#include  "Exceptions.hpp"
#include  "Logger.hpp"
#include  "Version.hpp"

namespace CasaEngine
{
	LogManager* LogManager::_instance = nullptr;

	LogManager& LogManager::Instance()
	{
		if (_instance == nullptr)
		{
			_instance = new LogManager();
		}

		return *_instance;
	}

	void LogManager::Destroy()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	LogManager::LogManager()
	{
		_verbosity = Trace;
	}

	LogManager::~LogManager()
	{
		for (auto* log : _logs)
		{
			log->Write(Info, "CasaEngine closed");
			delete log;
		}
	}

	void LogManager::AddLogger(ILogger* logger)
	{
		CA_ASSERT(logger != nullptr, "LogManager::AddLogger() : logger is nullptr");
		_logs.push_back(logger);

		std::ostringstream oss;
		oss << "CasaEngine version=" << CA_PRODUCT_VERSION << "." << CA_MAJOR_VERSION << "." << CA_MINOR_VERSION << std::endl;

		logger->Write(Info, oss.str());
	}

	void LogManager::RemoveLogger(const ILogger* logger)
	{
		CA_ASSERT(logger != nullptr, "LogManager::RemoveLogger() : logger is nullptr");

		for (auto it = _logs.begin();
			it != _logs.end();
			++it)
		{
			if (*it == logger)
			{
				_logs.erase(it);
				break;
			}
		}
	}

	void LogManager::Log(TLogVerbosity verbose, const char* format, ...)
	{
		static char sBuffer[8192];
		va_list Params;
		va_start(Params, format);
		vsprintf(sBuffer, format, Params);
		va_end(Params);

		for (auto* log : _logs)
		{
			log->Write(verbose, sBuffer);
		}
	}

	TLogVerbosity LogManager::getVerbosity() const
	{
		return _verbosity;
	}

	void LogManager::setVerbosity(const TLogVerbosity val)
	{
		_verbosity = val;
	}
}
