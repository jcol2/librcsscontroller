#ifndef LIBRCSSCONTROLLER_PLAYER_H_
#define LIBRCSSCONTROLLER_PLAYER_H_

namespace librcsscontroller
{
    /**
     *  The Player struct is used by SimulatorConnection to represent a virtual
     *  NAO that is present on the simulator, being controlled by an agent.
     */
    struct Player
    {
        /**
         *  Constructor
         */ 
        Player()
        { }

        /**
         *  Constructor
         *
         *  @param num The player number of the player.
         *  @param t The team of the player. 0 indicates left team, 1 indicates
         *  right team.
         */
        Player(int num, bool t)
            : number{num}, team{t}
        { }

        /**< Player number */
        int number;         
        
        /**< Player team. 0 indicates left team, 1 indicates right team. */
        std::string team;   
    };
}


#endif // LIBRCSSCONTROLLER_PLAYER_H_