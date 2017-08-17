
namespace librcsscontroller
{
    template<typename T>
    StreamGroupWriter StreamGroupWriter::Write(T data)
    {
        for (auto& s : group_)
        {
            if (stream_prefixes_[s])
            {
                stream_prefixes_[s]->Write(s, identifier_);
                stream_prefixes_[s] = nullptr;
            }
            *s << data;
        }        
        return *this;
    }

    template<typename T>
    StreamGroupWriter operator<<(StreamGroupWriter& os, const T& obj)
    {
        return os.Write(obj);
    }

    template<typename T>
    StreamGroupWriter operator<<(StreamGroupWriter&& os, const T& obj)
    {
        StreamGroupWriter copy{os};
        return os << obj;
    }

}