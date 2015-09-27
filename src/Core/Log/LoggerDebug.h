
#ifndef LOGGERDEBUG_H
#define LOGGERDEBUG_H

#include <Log/Logger.h>
#include "Logger.h"
#include "LogVerbose.h"


namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Logger inscrivant les messages dans un fichier
    ////////////////////////////////////////////////////////////
    class CA_EXPORT CLoggerDebug : public ILogger
    {
    private :

        //----------------------------------------------------------
        // Log un message
        //----------------------------------------------------------
        virtual void Write(TLogVerbosity verbose_, const std::string& Message);
    };

} // namespace CasaEngine


#endif // LOGGERDEBUG_H
