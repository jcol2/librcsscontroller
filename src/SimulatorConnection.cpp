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

#include "comms/MessageParser.h"
#include "simulator/SimulatorConnection.h"

#include <sstream>
#include <iomanip>

namespace librcsscontroller 
{
    SimulatorConnection::SimulatorConnection()
    { }
    
    bool SimulatorConnection::Init(const EndpointConnection& ep)
    {
        ep_ = ep;
        return true;
    }

    bool SimulatorConnection::Tick()
    {
        return last_.FromMessage(MessageParser{ep_.Receive()});      
    }

    SimulatorUpdate SimulatorConnection::GetLastUpdate()
    {
        return last_;
    }

    bool SimulatorConnection::SendInit()
    {
        return ep_.Send("(init)");
    }

    bool SimulatorConnection::SendKickOffCommand(bool team)
    {
        return ep_.Send(team ? "(kickOffRight)" : "(kickOffLeft)");
    }

    bool SimulatorConnection::SendDropBallCommand()
    {
        return ep_.Send("(dropBall)");
    }

    bool SimulatorConnection::SendMoveBallCommand(float x_pos, float y_pos, float z_pos, 
                                                  float x_vel, float y_vel, float z_vel)
    {
        std::stringstream cmd;            
        cmd << std::setprecision(2) << std::fixed << "(ball (pos " 
            << x_pos << " " << " " << y_pos << " " << z_pos << ") "
            << "(vel " << x_vel << " " << y_vel << " " << z_vel << "))";
        return ep_.Send(cmd.str());
    }

    bool SimulatorConnection::SendMoveBallCommand(float x_pos, float y_pos, float z_pos)
    {
        return SendMoveBallCommand(x_pos,  y_pos, z_pos, 0.0f, 0.0f, 0.0f);
    }

    bool SimulatorConnection::SendPlayModeCommand(PlayMode play_mode)
    {
        std::stringstream cmd;
        cmd << "(playMode " << play_mode.ToString() << ")";
        return ep_.Send(cmd.str());        
    }

    bool SimulatorConnection::SendMovePlayerCommand(const Player& to_move, float x_pos,
                                                    float y_pos, float z_pos,
                                                    float orientation)
    {
        std::stringstream cmd;
        cmd << std::setprecision(2) << std::fixed << "(agent (team "
            << to_move.team << ")(unum " << to_move.number << ")(move " 
            << x_pos << " " << y_pos << " " << z_pos << " " << orientation
            << "))";            
        return ep_.Send(cmd.str());
    }

    bool SimulatorConnection::SendFreeKickCommand(bool team)
    {
        return ep_.Send(team ? "(free_kick_right)" : "(free_kick_left)");
    }

    bool SimulatorConnection::SendDirectFreeKickCommand(bool team)
    {
        return ep_.Send(team ? "(direct_free_kick_right)" : "(direct_free_kick_left)");
    }

    bool SimulatorConnection::SendKillServerCommand()
    {
        return ep_.Send("(killsim)");
    }

    bool SimulatorConnection::SendSetTimeCommand(int time)
    {
        std::stringstream ss;
        ss << "(time " << time << ")";
        return ep_.Send(ss.str());
    }

    bool SimulatorConnection::SendResetTimeCommand()
    {
        return SendSetTimeCommand(0);
    }

    bool SimulatorConnection::SendFullStateRequest()
    {
        return ep_.Send("(reqfullstate)");
    }

    bool SimulatorConnection::SendGetAckCommand()
    {
        return ep_.Send("(getAck)");
    }

    bool SimulatorConnection::SendSetScoreCommand(int left_score, int right_score)
    {
        std::stringstream ss;
        ss << "(score (left " << left_score << ") (right " << right_score << "))";
        return ep_.Send(ss.str());
    }

    bool SimulatorConnection::SendKillPlayerCommand(const Player& to_kill)
    {
        std::stringstream cmd;
        cmd << "(kill (team " << to_kill.team << ")(unum " << to_kill.number 
            << "))";            
        return ep_.Send(cmd.str());
    }

    bool SimulatorConnection::SendReposPlayerCommand(const Player& to_repos)
    {
        std::stringstream cmd;
        cmd << "(repos (team " << to_repos.team << ")(unum " << to_repos.number 
            << "))";            
        return ep_.Send(cmd.str());
    }

    bool SimulatorConnection::SendSelectPlayerCommand(const Player& to_select)
    {
        std::stringstream cmd;
        cmd << "(select (team " << to_select.team << ")(unum " 
            << to_select.number << "))";            
        return ep_.Send(cmd.str());
    }

}

