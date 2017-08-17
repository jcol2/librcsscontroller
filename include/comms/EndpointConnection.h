#ifndef LIBRCSSCONTROLLER_ENDPOINTCONNECTION_H_
#define LIBRCSSCONTROLLER_ENDPOINTCONNECTION_H_

#include "SocketStream.h"
#include "utils/Logger.h"

#include <iostream>

namespace librcsscontroller 
{
    /**
     *  The EndpointConnection class provides a text interface between two
     *  endpoints. This allows the sending / receiving of strings to a
     *  TCP endpoint.
     */
    class EndpointConnection 
    {
    public:
        /**
         *  Constructor.
         */
        EndpointConnection();
        
        /**
         *  Initialises the EndpointConneciton. 
         *
         *  @param host The host to connect to.
         *  @param port The port to connect to.
         *  @return bool True if initialisation was successful. False otherwise.
         */
        bool Init(const std::string& host, const int port);

        /**
         *  Initialises the EndpointConneciton. 
         * 
         *  @param s The underlying SocketStream to use for communicaiton.
         *  @return bool True if initialisation was successful. False otherwise.
         */
        bool Init(const SocketStream& s);      

        /**
         *  Receives a string from the connected host.
         *
         *  @return std::string Returns the data that was received. If the 
         *  receive failed, an empty string ("") is returned.
         */ 
        std::string Receive();

        /**
         *  Sends a string to the connected host.
         *
         *  @param data The string to send to the host. 
         *  @return bool True indicates success. False indicates failure.
         */
        bool Send(const std::string& data);

        /** 
         *  Closes the connection with the host.
         *
         *  @return bool True indicates success. False indicates failure.
         */
        bool Close();

        /**
         *  Returns the unique identifier of the connection.
         *
         *  @return int The unique identifier of the connection.
         */
        int GetId() const;

    private:
        /**
         *  Converts a 4-byte integer to network order to send over the
         *  wire.
         * 
         *  @param len The integer to convert.
         *  @param[out] out The integer converted to network order.
         */
        static void LenToNLen(uint32_t len, unsigned char out[]);

        /**
         *  Converts a 4-byte network order integer to host order.
         * 
         *  @param len The integer to convert.
         *  @param[out] out The integer converted to host order.
         */       
        static void NLenToLen(unsigned char bytes[], uint32_t* out);

        SocketStream sock_; /**< The underlying SocketStream connection */
        Logger* log_;       /**< The logging instance in use */

    };
}

#endif // LIBRCSSCONTROLLER_ENDPOINTCONNECTION_H_