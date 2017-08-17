#include "comms/SocketStream.h"

#include <unistd.h>

namespace librcsscontroller {

    SocketStream::SocketStream()
        : socketfd_{0}
    { }

    void SocketStream::Init(const int socketfd)
    {
        socketfd_ = socketfd;
    }

    bool SocketStream::Read(size_t bytes, std::string* out)
    {
        unsigned char buffer[bytes];
        if (!Read(bytes, buffer))
        {
            return false;
        }
        *out = std::string{(char*)buffer, bytes};
        return true;
    }

    bool SocketStream::Read(size_t bytes, unsigned char buffer[])
    {
        // Continue reading until the requested number of bytes
        // are read or an error occurs
        size_t tally = 0;
        while (tally < bytes)
        {
            size_t b = ::read(socketfd_, buffer + tally, bytes - tally);
            tally += b;

            // 0 indicates EOF, < 0 indicates error
            if (b <= 0)
            {
                break;        
            }
        }
        
        // TODO return error code instead of boolean
        return (tally == bytes);
    }

    bool SocketStream::Write(const std::string data)
    {
        return Write((unsigned char*)data.c_str(), data.size());
    }

    bool SocketStream::Write(unsigned char buffer[], size_t len)
    {
        size_t b = ::write(socketfd_, buffer, len);
        return (b == len);   
    }

    bool SocketStream::Close()
    {
        if (!socketfd_)
        {
            return true;
        }
        return ::close(socketfd_) == 0;
    }

    int SocketStream::GetFileDescriptor() const
    {
        return socketfd_;
    }

}


    