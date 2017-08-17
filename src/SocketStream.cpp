/*
 *  librcsscontroller
 *  A library for controlling rcssserver3d simulations.
 *  Copyright (C) 2017 Jeremy Collette.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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


    