#ifndef LIBRCSSCONTROLLER_LOGLEVEL_H_
#define LIBRCSSCONTROLLER_LOGLEVEL_H_

#include <string>

namespace librcsscontroller
{
    /**
     *  The LogLevel class defines a number of logging levels that may be used
     *  to indicate the importance of a logging message.
     */
    enum class LogLevel: int 
    {  
        NONE,
        CRITICAL,
        ERROR,
        WARNING,
        INFO,
        DEBUG,
        DEBUG_2,
        DEBUG_3,
        DEBUG_4,
        DEBUG_5,
        NUM_LEVELS 
    };


    /**
     *  Maps a LogLevel to an associated std::string representation.
     *
     *  @param level The LogLevel to convert to a string.
     *  @return std::string The string representation of the supplied LogLevel.
     */
    static std::string LogLevelToString(LogLevel level)
    {
        switch(level)
        {
            case LogLevel::NONE:
                return "NONE";
            case LogLevel::CRITICAL:
                return "CRITICAL";
            case LogLevel::ERROR:
                return "ERROR";
            case LogLevel::WARNING:
                return "WARNING";
            case LogLevel::INFO:
                return "INFO";
            case LogLevel::DEBUG:
                return "DEBUG";
            case LogLevel::DEBUG_2:
                return "DEBUG_2";
            case LogLevel::DEBUG_3:
                return "DEBUG_3";
            case LogLevel::DEBUG_4:
                return "DEBUG_4";
            case LogLevel::DEBUG_5:
                return "DEBUG_5";
            default:
                break;
        }
        return "N/A";
    }
}

#endif // LIBRCSSCONTROLLER_LOGLEVEL_H_