
#include <stdio.h>
#include <stdarg.h>

#include "Base.h"

#include "CA_Assert.h"
#include "LogManager.h"
#include "Exceptions.h"
#include "Logger.h"


namespace CasaEngine
{

LogManager* LogManager::m_sInstance = nullptr;

/**
 * 
 */
LogManager& LogManager::Instance()
{
	if (m_sInstance == nullptr)
	{
		m_sInstance = NEW_AO LogManager();
	}

	return *m_sInstance;
}

/**
 * 
 */
void LogManager::Destroy()
{
	if (m_sInstance != nullptr)
	{
		DELETE_AO m_sInstance;
		m_sInstance = nullptr;
	}
}

/**
 * 
 */
LogManager::LogManager()
{
	m_Verbosity = Trace;
}

/**
 * 
 */
LogManager::~LogManager()
{
	std::vector<ILogger *>::iterator it;

	for (it = m_Logs.begin();
		it != m_Logs.end();
		++it)
	{
		DELETE_AO (*it);
	}
}

void LogManager::AddLogger(ILogger *logger_)
{
	CA_ASSERT(logger_ != nullptr, "LogManager::AddLogger() : logger_ is nullptr");
	m_Logs.push_back(logger_);
}

/**
 * 
 */
void LogManager::RemoveLogger(ILogger *logger_)
{
	CA_ASSERT(logger_ != nullptr, "LogManager::RemoveLogger() : logger_ is nullptr");

	std::vector<ILogger *>::iterator it;

	for (it = m_Logs.begin();
		it != m_Logs.end();
		++it)
	{
		if ((*it) == logger_)
		{
			m_Logs.erase(it);
			break;
		}
	}
}

/////////////////////////////////////////////////////////////
/// Log un message
///
/// \param Format : Format du message à logger
/// \param ... :    Paramètres optionnels
///
////////////////////////////////////////////////////////////
void LogManager::Log(TLogVerbosity verbose_, const char* Format, ...)
{
	static char sBuffer[8192];
	va_list Params;
	va_start(Params, Format);
	vsprintf(sBuffer, Format, Params);
	va_end(Params);

	std::vector<ILogger *>::iterator it;

	for (it = m_Logs.begin();
		it != m_Logs.end();
		++it)
	{
		(*it)->Write(verbose_, sBuffer);
	}
}

TLogVerbosity LogManager::getVerbosity() const
{
	return m_Verbosity;
}

void LogManager::setVerbosity(TLogVerbosity val)
{
	m_Verbosity = val;
}

} // namespace CasaEngine
