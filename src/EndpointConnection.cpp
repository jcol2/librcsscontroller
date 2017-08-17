#include "comms/EndpointConnection.h"
#include "utils/Logger.h"

#include <algorithm>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/socket.h>


namespace librcsscontroller
{
    EndpointConnection::EndpointConnection()
        : log_(&Logger::GetInstance())
    { }

    bool EndpointConnection::Init(const std::string& host, const int port)
    {
        int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            log_->operator()(LogLevel::ERROR) << "Error opening socket: " << sockfd << "\n";
            return false;
        }

        struct hostent* server = gethostbyname(host.c_str());
        if (!server)
        {
            log_->operator()(LogLevel::ERROR) << "Error finding host \"" << host << "\"\n";
            return false;
        }

        struct sockaddr_in serv_addr;
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, 
             (char *)&serv_addr.sin_addr.s_addr,
             server->h_length);
        serv_addr.sin_port = htons(port);
        
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        {
            log_->operator()(LogLevel::ERROR) << "Error connecting to host \"" << host << ":" << port << "\"\n";
            return false;
        }
        sock_.Init(sockfd);

        return true;
    }

    bool EndpointConnection::Init(const SocketStream& s)
    {
        sock_ = s;
    }

    std::string EndpointConnection::Receive()
    {
        std::string recv;
        unsigned char len_bytes[4];
        if (!sock_.Read(4, len_bytes))
        {
            //std::cerr << "Error: reading length failed!\n";
            return recv;
        }

        uint32_t len = 0;
        NLenToLen(len_bytes, &len);
        sock_.Read(len, &recv);

        log_->operator()(LogLevel::DEBUG_2) << "RECEIVED " << sock_.GetFileDescriptor() << ": \"" << recv << "\"\n";
        
        return recv;
    }

    bool EndpointConnection::Send(const std::string& data)
    {     
        log_->operator()(LogLevel::DEBUG_2) << "SENT " << sock_.GetFileDescriptor() << ": \"" << data << "\"\n";        

        uint32_t len = data.size();        
        unsigned char len_bytes[4];
        LenToNLen(len, len_bytes);

        if (!sock_.Write(len_bytes, 4))
        {
            return false;
        }
        return sock_.Write(data);
    }

    bool EndpointConnection::Close()
    {
        return sock_.Close();
    }

    int EndpointConnection::GetId() const
    {
        return sock_.GetFileDescriptor();
    }

    void EndpointConnection::LenToNLen(uint32_t len, unsigned char out[])
    {
        for (int i=0; i < 4; ++i)
        {
            out[i] = len >> (24 - (i*8));
        }
    }

    void EndpointConnection::NLenToLen(unsigned char bytes[], uint32_t* out)
    {
        for (int i=0; i < 4; ++i)
        {
            *out |= bytes[i] << (24 - (i*8));
        }
    }

}