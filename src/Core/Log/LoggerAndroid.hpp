#ifndef LOGGERANDROID_H
#define LOGGERANDROID_H


#include "Logger.h"
#include "LogVerbose.h"

#include <string>
#include "CA_Export.h"

namespace CasaEngine
{
    /**
     * 
     */
    class CA_EXPORT LoggerAndroid : public ILogger
    {
    private :

        /**
		 *
		 */
        void Write(TLogVerbosity verbose_, const std::string& msg_);
    };

} // namespace CasaEngine


#endif // LOGGERDEBUG_H
