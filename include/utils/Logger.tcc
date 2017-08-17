
namespace librcsscontroller
{
    template<typename T>
    Logger& Logger::Log(T data, LogLevel level)
    {
        for (int l = static_cast<int>(level); l >= static_cast<int>(LogLevel::NONE); l = l-1)
        {
            for (auto& s : subscribers_[l])
            {
                s << data;
            }
        }
    }

}