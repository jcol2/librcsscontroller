#include "utils/DateTimeWriter.h"

namespace librcsscontroller
{

    void DateTimeWriter::Write(std::ostream* s, const std::string& log_level)
    {
        time_t timer;
        time(&timer);
        struct tm * timeinfo = localtime(&timer);

        char buffer[80];
        strftime (buffer, 80,"[%d/%m/%y %T] ",timeinfo);

        *s << buffer << std::left << std::setw(8) << log_level + ": ";
    }

}