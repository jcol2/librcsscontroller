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

#include <string.h>

#include "utils/Logger.h"
#include "utils/DateTimeWriter.h"

namespace librcsscontroller
{
    Logger::Logger()
    { }

    Logger* Logger::singleton_ = nullptr;

    Logger& Logger::GetInstance()
    {
        if (!singleton_)
        {
            singleton_ = new Logger();
        }
        return *singleton_;
    }

    void Logger::AddStream(std::ostream* out, const LogLevel highest, const LogLevel lowest, StreamWriter* prefix)
    {
        stream_prefixes_[out] = prefix;
        for (int i = static_cast<int>(lowest); i <= static_cast<int>(highest); ++i)
        {
            subscribers_[i].push_back(out);
        }  
    }

    void Logger::AddStream(std::ostream* out, const LogLevel highest, const LogLevel lowest)
    {
        AddStream(out, highest, lowest, new DateTimeWriter());
    }
    void Logger::AddStream(std::ostream* out, const LogLevel highest)
    {
        AddStream(out, highest, LogLevel::NONE);
    }

    void Logger::RemoveStream(std::ostream* out, const LogLevel highest, const LogLevel lowest)
    {
        for (int i = static_cast<int>(lowest); i <= static_cast<int>(highest); ++i)
        {
            for (auto itr = subscribers_[i].begin(); itr != subscribers_[i].end(); )
            {
                if (*itr == out)
                {
                    itr = subscribers_[i].erase(itr);
                }
                else
                {
                    itr++;
                }
            }
        }
    }

    void Logger::RemoveStream(std::ostream* out, const LogLevel highest)
    {
        return RemoveStream(out, highest, LogLevel::NONE);
    }

    void Logger::RemoveStream(std::ostream* out)
    {
        return RemoveStream(out, LogLevel(static_cast<int>(LogLevel::NUM_LEVELS)-1), LogLevel::NONE);
    }

    StreamGroupWriter Logger::GetWriter(const LogLevel level)
    {
        int index = static_cast<int>(level);
        return StreamGroupWriter{subscribers_[index], LogLevelToString(level), stream_prefixes_};
    }

}
