#ifndef LIBRCSSCONTROLLER_LOGGER_H_
#define LIBRCSSCONTROLLER_LOGGER_H_

#include "LogLevel.h"
#include "StreamGroupWriter.h"

#include <ostream>

namespace librcsscontroller
{
    /**
     *  The Logger class provides a comprehensive interface for logging. 
     *
     *  Messages are logged with an associated LogLevel, which represent their
     *  level of importance. The higher the LogLevel, the less critical the 
     *  messages content is. 
     *
     *  Output streams are added as listeners, which subscribe to a range of
     *  LogLevels (or less commonly, to a specific LogLevel). Each time a
     *  message is logged, streams that are subscribed to the same LogLevel
     *  will have the message written to them.
     *
     *  LogLevels can also have a StreamWriter prefix, which prefixes data to
     *  each message that is logged at that LogLevel. For example, the 
     *  DateTimeWriter class writes the date, time, and LogLevel identifier
     *  to the stream.
     */
    class Logger
    {
    public:
        /**
         *  Returns the global logging singleton in use for this project. This 
         *  is an easy way of keeping logging consistent, without having to pass 
         *  an instance around to each class.
         *
         *  @return Logger& A reference to the global logging singleton.
         */
        static Logger& GetInstance();

        /**
         *  Function Call Operator
         *
         *  Provides a StreamGroupWriter instance which allows for logging at a
         *  particular level either using the stream insertion operator ('<<')
         *  or other member functions.
         *
         *  @param level The LogLevel intended to use for logging.
         *  @return StreamGroupWriter A StreamGroupWriter instance which
         *  provides an interface for writing logging messages to all streams
         *  subscribed to the specified LogLevel, level.
         */
        StreamGroupWriter operator()(const LogLevel level)
        {
            return GetWriter(level);
        }

        /**
         *  Adds an output stream as a subscriber for all messages logged at
         *  levels between (and including) 'lowest' and 'highest' LogLevels.
         *
         *  @param out[in] The output stream to subscribe to messages.
         *  @param highest The highest level to subscribe to.
         *  @param lowest The lowest level to subscribe to.
         *  @param prefix[in] The StreamWriter instance to use to write message prefixes.
         */
        void AddStream(std::ostream* out, const LogLevel highest, const LogLevel lowest, StreamWriter* prefix);

        /**
         *  Adds an output stream as a subscriber for all messages logged at
         *  levels between (and including) 'lowest' and 'highest' LogLevels.
         *
         *  @param out[in] The output stream to subscribe to messages.
         *  @param highest The highest level to subscribe to.
         *  @param lowest The lowest level to subscribe to.
         */
        void AddStream(std::ostream* out, const LogLevel highest, const LogLevel lowest);

        /**
         *  Adds an output stream as a subscriber for all messages logged at
         *  levels between (and including) LogLevel::NONE and 'highest'
         *  LogLevels.
         *
         *  @param out[in] The output stream to subscribe to messages.
         *  @param highest The highest level to subscribe to.
         */
        void AddStream(std::ostream* out, const LogLevel highest);

        /**
         *  Unsubscribes an output stream from all LogLevels between (and 
         *  including) 'lowest' and 'highest'.
         *
         *  @param out[in] The output stream to unsubscribe.
         *  @param highest The highest level to unsubscribe from.
         *  @param lowest The lowest level to unsubscribe from.
         */
        void RemoveStream(std::ostream* out, const LogLevel highest, const LogLevel lowest);

        /**
         *  Unsubscribes an output stream from all LogLevels between (and 
         *  including) LogLevel::NONE and 'highest'.
         *
         *  @param out[in] The output stream to unsubscribe from messages.
         *  @param highest The highest level to unsubscribe from.
         */      
        void RemoveStream(std::ostream* out, const LogLevel highest);

        /**
         *  Unsubscribes an output stream from all LogLevels.
         *
         *  @param out[in] The output stream to unsubscribe from messages.
         */           
        void RemoveStream(std::ostream* out);

        /**
         *  Returns a StreamGroupWriter for the specified LogLevel.
         *
         *  @param level The StreamGroupWriter will write to subscribers of
         *  this level.
         *  @return StreamGroupWriter A StreamGroupWriter which will write to 
         *  subscribers of the requested level.
         */
        StreamGroupWriter GetWriter(const LogLevel level);

        /**
         *  Logs data to a specified LogLevel.
         *
         *  @tparam T The type of the data to be logged.
         *  @param data The data to be logged.
         *  @param level The LogLevel of the data being logged.
         *  @return Logger& A reference to the Logger instance this was called
         *  upon.
         */
        template<typename T> Logger& Log(T data, LogLevel level);

    private:
        /**
         *  Points to the singleton instance of Logger
         */
        static Logger* singleton_;
        
        /**
         *  Constructor
         */
        Logger();

        /**
         *  Holds outstream subscriptions for each LogLevel
         */
        std::vector<std::ostream*> subscribers_[static_cast<int>(LogLevel::NUM_LEVELS)];

        /**
         *  Holds StreamWriter pointers which preprend prefixes to messages for
         *  each ostream.
         */
        std::unordered_map<std::ostream*, StreamWriter*> stream_prefixes_;
    };

}

#include "Logger.tcc"

#endif // LIBRCSSCONTROLLER_LOGGER_H_
