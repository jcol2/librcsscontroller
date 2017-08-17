#ifndef LIBRCSSCONTROLLER_SOCKETSTREAM_H_
#define LIBRCSSCONTROLLER_SOCKETSTREAM_H_

#include <sys/socket.h>
#include <string>

namespace librcsscontroller
{
    /**
     *  The SocketStream class provides a read / write interface for network
     *  sockets.
     */
    class SocketStream
    {
    public:
        /** 
         *  Constructor.
         */
        SocketStream();

        /**
         *  Initialises the SocketStream.
         *
         *  @param socketfd The socket file descriptor of an open socket to use
         *  for reading / writing.
         *  @return bool True for success. False otherwise.
         */
        void Init(const int socketfd);

        /**
         *  Attempts to read from the underlying socket.
         *
         *  @param bytes The number of bytes to read.
         *  @param out[out] The string to write received data to.
         *  @return bool True for success. False otherwise.
         */
        bool Read(size_t bytes, std::string* out);

        /**
         *  Attempts to read from the underlying socket.
         *
         *  @param bytes The number of bytes to read.
         *  @param out[out] The buffer to write received data to.
         *  @return bool True for success. False otherwise.
         */        
        bool Read(size_t bytes, unsigned char buffer[]);

        /**
         *  Attempts to write to the underlying socket.
         *
         *  @param data The data to write.
         *  @return bool True for success. False otherwise.
         */    
        bool Write(const std::string data);

        /**
         *  Attempts to write to the underlying socket.
         *
         *  @param buffer The buffer to write.
         *  @param len The length of the buffer.
         *  @return bool True for success. False otherwise.
         */        
        bool Write(unsigned char buffer[], size_t len);

        /**
         *  Attempts to close the underlying socket.
         *
         *  @return bool True for success. False otherwise.
         */
        bool Close();

        /**
         *  Returns the underlying socket file descriptor.
         * 
         *  @return int The underlying socket file descriptor.
         */
        int GetFileDescriptor() const;

    private:
        int socketfd_;  /**< The underlying socket file descriptor */
    };
}

#endif // LIBRCSSCONTROLLER_SOCKETSTREAM_H_