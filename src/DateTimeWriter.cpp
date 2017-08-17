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

#include "utils/DateTimeWriter.h"

namespace librcsscontroller
{

    void DateTimeWriter::Write(std::ostream* s, const std::string& log_level)
    {
        time_t timer;
        time(&timer);
        struct tm * timeinfo = localtime(&timer);

        char buffer[80];
        strftime (buffer, 80,"[%d/%m/%y %T] ",timeinfo);

        *s << buffer << std::left << std::setw(8) << log_level + ": ";
    }

}