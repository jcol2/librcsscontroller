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

#include "utils/StreamGroupWriter.h"

namespace librcsscontroller
{
    StreamGroupWriter::StreamGroupWriter(std::vector<std::ostream*> group, 
            const std::string& identifier, 
            const std::unordered_map<std::ostream*, StreamWriter*>& prefixes)
        : group_{group}, identifier_{identifier}, stream_prefixes_{prefixes}
    { }

    StreamGroupWriter::StreamGroupWriter(std::vector<std::ostream*> group)
        : StreamGroupWriter(group, "", {})
    { }

}