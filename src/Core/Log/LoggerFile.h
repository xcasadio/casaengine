#ifndef LOGGERFILE_H
#define LOGGERFILE_H

#include <Log/Logger.h>
#include <fstream>
#include "LogVerbose.h"
#include "CA_Export.h"

namespace CasaEngine
{
    /**
     * 
     */
    class CA_EXPORT LoggerFile : public ILogger
    {
    public :
		/**
		 * 
		 */
        LoggerFile(const char *pFilename_ = "Output.log");

        /**
         * 
         */
        ~LoggerFile();

    private :
        /**
         * 
         */
        void Write(TLogVerbosity verbose_, const std::string& Message);

		/**
		 * 
		 */
		void Write(const std::string& Message);

        /**
         * 
         */
        std::ofstream m_File;

		char m_TempBuffer[32];
    };

} // namespace CasaEngine

#endif // LOGGERFILE_H
