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

#include "simulator/SimulatorUpdate.h"

namespace librcsscontroller
{
    SimulatorUpdate::SimulatorUpdate()
        : play_mode{PlayMode::BEFORE_KICK_OFF}
    { }

    bool SimulatorUpdate::FromMessage(MessageParser msg)
    {
        while(msg.IsGood())
        {
            std::string key {""};                
            if (!msg.ReadDelimitedWord(&key))
            {
                break;
            }

            if (key == "play_mode")
            {
                int mode;
                msg.ReadType(&mode);
                play_mode = mode;
            }
            // "matNum%d" represents a player where "%d" is the player number
            else if (key.find("matNum") != std::string::npos && 
                     key.size() > 6 && std::isdigit(key[6]))
            {
                Player new_player;
                new_player.number = key[6] - '0';

                // Player number is followed by team which is either "matLeft" or "matRight"
                std::string team;
                msg.ReadDelimitedWord(&team);
                new_player.team = (team == "matLeft" ? "Left" : "Right");

                bool found = false;
                for (const Player& p : players)
                {
                    if (p.number == new_player.number && p.team == new_player.team)
                    {
                        found = true;
                    }
                }
                if (!found)
                {
                    players.push_back(new_player);
                }
            }                        
        }
        return true;
    }

}