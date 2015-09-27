
#include "Base.h"

#include "CEGUILogger.h"
#include "CEGUI\String.h"
#include "Log\LogManager.h"



namespace CasaEngine
{
	/**
	 * 
	 */
	CEGUILogger::CEGUILogger()
	{
		char addr_buff[32];
		sprintf(addr_buff, "(%p)", static_cast<void*>(this));
		logEvent("CEGUI::Logger singleton created. " + CEGUI::String(addr_buff));
		logEvent("CEGUILogger singleton created. " + CEGUI::String(addr_buff));
	}

	/**
	 * 
	 */
	CEGUILogger::~CEGUILogger()
	{
		CA_TRACE("[CEGUI] logger destroyed\n");
	}
	
	/**
	 *
	 */
	void CEGUILogger::logEvent(const CEGUI::String& message, CEGUI::LoggingLevel level)
	{
		TLogVerbosity verbose = Info;
		
		switch (level)
		{
			case CEGUI::Errors:
				verbose = Error;
				break;
			
			case CEGUI::Warnings:
				verbose = Warning;
				break;
			
			case CEGUI::Informative:
				verbose = Debug;
				break;
			
			case CEGUI::Insane:
				verbose = Trace;
				break;
		}
		
		Logging.Log(verbose, "[CEGUI] %s\n", message.c_str());
	}
	
	/**
	 *
	 */
	void CEGUILogger::setLogFilename(const CEGUI::String& filename, bool append)
	{
		//Do nothing
	}

} // namespace CasaEngine
