
#ifndef _CEGUILOGGER_H_
#define _CEGUILOGGER_H_

#include "CA_Export.h"
#include "CEGUI\Logger.h"


namespace CasaEngine
{
	///
	class CA_EXPORT CEGUILogger : public CEGUI::Logger
	{
	public:
		/**
		 * 
		 */
		CEGUILogger();
		
		/**
		 * 
		 */
		~CEGUILogger();

		// overridden from Logger
		void logEvent(const CEGUI::String& message, CEGUI::LoggingLevel level = CEGUI::Standard);
		void setLogFilename(const CEGUI::String& filename, bool append = false);

	protected:
		// Implementation of abstract interface.
		bool initialiseImpl();
		void cleanupImpl();
	};

}  // namespace CasaEngine

#endif //_CEGUILOGGER_H_
