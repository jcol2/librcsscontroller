namespace librcsscontroller
{
    template <typename TFromAgent, typename TToAgent>
    AgentConnection<TFromAgent, TToAgent>::AgentConnection()
    {  } 

    template <typename TFromAgent, typename TToAgent>
    bool AgentConnection<TFromAgent, TToAgent>::Init(const EndpointConnection& ep)
    {
        ep_ = ep;
    }       

    template <typename TFromAgent, typename TToAgent>
    bool AgentConnection<TFromAgent, TToAgent>::Receive(TFromAgent* out)
    {
        time_t start, now;
        time(&start);
        time(&now);

        std::string recv = ep_.Receive();
        while (!recv.size() && (difftime(now, start) < RECEIVE_TIMEOUT_SEC))
        {
            recv = ep_.Receive();
            usleep(10);
            time(&now);
        }
        
        if (!recv.size())
        {
            std::cerr << "Client timed out!\n";
            return false;
        }
        return out->FromMessage(recv);
    }

    template <typename TFromAgent, typename TToAgent>
    bool AgentConnection<TFromAgent, TToAgent>::Send(const TToAgent& update)
    {
        return ep_.Send(update.ToMessage());
    }

    template <typename TFromAgent, typename TToAgent>
    bool AgentConnection<TFromAgent, TToAgent>::Close()
    {
        return ep_.Close();
    }

    template <typename TFromAgent, typename TToAgent>
    int AgentConnection<TFromAgent, TToAgent>::GetId() const
    {
        return ep_.GetId();
    }
}