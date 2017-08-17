#ifndef LIBRCSSCONTROLLER_SIMULATORUPDATE_H_
#define LIBRCSSCONTROLLER_SIMULATORUPDATE_H_

#include "comms/MessageParser.h"
#include "Player.h"
#include "PlayMode.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace librcsscontroller 
{
    /**
     *  The SimulatorUpdate class stores update information received by 
     *  SimulatorConnection instances that interface with rcssserver3d. It 
     *  contains information about the state of the simulator.
     */
    struct SimulatorUpdate
    {
        /**
         *  Constructor
         */
        SimulatorUpdate();

        /** 
         *  Populates a SimulatorUpdate instance with the information contained
         *  in a parsable string sent over the network.
         */
        bool FromMessage(MessageParser msg);

        /**< Holds informaiton regarding the current players on the server */
        std::vector<Player> players;    
        
        /**< Indicates the current PlayMode */
        PlayMode play_mode;
    };
}

#endif // LIBRCSSCONTROLLER_SIMULATORUPDATE_H_