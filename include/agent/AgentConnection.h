#ifndef LIBRCSSCONTROLLER_AGENTCONNECTION_H_
#define LIBRCSSCONTROLLER_AGENTCONNECTION_H_

#include "comms/EndpointConnection.h"
#include "comms/MessageParser.h"
#include "FromAgent.h"
#include "ToAgent.h"

#include <time.h>
#include <unistd.h>

namespace librcsscontroller 
{
    /**
     *  The AgentConnection class facilitates a TCP connection with agents.
     *  Agents are expected to send TFromAgent instances, and will receieve
     *  TToAgent instances.
     *
     *  @tparam TFromAgent The type that is expected to be received from
     *  agents. 
     *  @tparam TToAgent The type that will be sent to agents.
     */
    template <typename TFromAgent, typename TToAgent>
    class AgentConnection 
    {
    public:
        /**
         *  Constructor
         */        
        AgentConnection();

        /**
         *  Initialises the connection with the agent.
         *
         *  @param ep A reference to the underlying 
         *  EndpointConnection with the agent.
         */
        bool Init(const EndpointConnection& ep);

        /**
         *  Attempts to receive a TFromAgent from the agent.
         *
         *  @param[out] out A pointer to a TFromAgent to store the 
         *  received TFromAgent in.
         *  @return bool True indicates success. False indicates failure.
         */
        bool Receive(TFromAgent* out);

        /**
         *  Attempts to send a TToAgent to the agent.
         *
         *  @param update The TToAgent instance to send.
         *  @return bool True indicates success. False indicates failure.
         */
        bool Send(const TToAgent& update);

        /**
         *  Attempts to close the connection with the agent.
         *
         *  @return bool True if the connection was successfully closed. False
         *  if the connection could not be closed.
         */
        bool Close();

        /** 
         *  Returns the unique agent connection id.
         *
         *  @return int The unique agent connection id.
         */
        int GetId() const;

    private:
        /**
         *  The time in seconds until an agent is considered to have timed out.
         */
        constexpr static double RECEIVE_TIMEOUT_SEC = 2.0;     

        /**
         *  The underlying EndpointConnection with the agent.
         */
        EndpointConnection ep_;
    };
}

#include "AgentConnection.tcc"

#endif // LIBRCSSCONTROLLER_AGENTCONNECTION_H_