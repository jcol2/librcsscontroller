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