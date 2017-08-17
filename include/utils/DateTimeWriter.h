#ifndef LIBRCSSCONTROLLER_DATETIMEWRITER_H_
#define LIBRCSSCONTROLLER_DATETIMEWRITER_H_

#include "StreamWriter.h"

#include <iomanip>

namespace librcsscontroller
{
    /**
     *  The DateTimeWriter class is a StreamWriter which writes the current date
     *  and time to an out stream.
     */
    class DateTimeWriter
        : public StreamWriter
    {
    public:
        /**
         *  Writes the current date and time, and the name of a LogLevel to
         *  an output stream.
         *
         *  @param s The output stream to write to.
         *  @param log_level The name of the LogLevel being used.
         */
        void virtual Write(std::ostream* s, const std::string& log_level);
    };

}

#endif // LIBRCSSCONTROLLER_DATETIMEPREFIXWRITER_H_