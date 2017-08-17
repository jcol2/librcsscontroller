#ifndef LIBRCSSCONTROLLER_STREAMWRITER_H_
#define LIBRCSSCONTROLLER_STREAMWRITER_H_

#include <ostream>

namespace librcsscontroller
{
    /**
     *  The StreamWriter class is an abstract base class, where implementing
     *  classes will write some kind of data to a stream. 
     *
     *  The deriving class may write some static or generated data to the
     *  stream, such as an identifier, or the current time.
     */    
    class StreamWriter
    {        
    public:
        /**
         *  Writes some kind of data to the output stream.
         *
         *  @param s[in] The output stream to write to.
         *  @param log_level The identifier of the LogLevel being used.
         */
        void virtual Write(std::ostream* s, const std::string& log_level) = 0;
    
    };

}

#endif // LIBRCSSCONTROLLER_STREAMWRITER_H_