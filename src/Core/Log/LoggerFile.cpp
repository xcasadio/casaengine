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

/**
 * 
 */
LoggerFile::LoggerFile(const char *pFilename_) :
	m_File(pFilename_)
{
    if (!m_File)
        throw CLoadingFailed(pFilename_, "LoggerFile()");

    m_File << "===========================================" << std::endl;
    m_File << "CasaEngine v" << CA_PRODUCT_VERSION << "." << CA_MAJOR_VERSION << "." << CA_MINOR_VERSION;
	m_File << " - Event log - " << DateTime::Now().GetCurrentDate() << " " << DateTime::Now().GetCurrentTime() << std::endl;
    m_File << "===========================================" << std::endl;
}

/**
 * 
 */
LoggerFile::~LoggerFile()
{
    m_File << "===========================================" << std::endl;
    m_File << " CasaEngine closed at " << DateTime::Now().GetCurrentTime() << std::endl;
    m_File << "===========================================" << std::endl;

	m_File.close();
}

/**
 * 
 */
void LoggerFile::Write(TLogVerbosity verbose_, const std::string& Message)
{
	std::string str;

	switch(verbose_)
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

	str = DateTime::Now().GetCurrentTime() + ">" + str + ": " + Message;

    Write(str);
}

/**
 * 
 */
void LoggerFile::Write(const std::string& Message)
{
	CA_ASSERT(m_File.is_open(), "LoggerFile::Write() : file is not open");

	m_File << Message << std::flush;
}

}
