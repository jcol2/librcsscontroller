
#include "simulator/PlayMode.h"

namespace librcsscontroller
{

    // These names are defined by rcssserver3d - sorry the formatting and case
    // is inconsistent :'(
    std::string PlayMode::PLAY_MODE_STRINGS[NUM_MODES] 
                {"BeforeKickOff", "KickOff_Left", "KickOff_Right", "PlayOn", 
                 "KickIn_Left", "KickIn_Right", "corner_kick_left", 
                 "corner_kick_right", "goal_kick_left", "goal_kick_right", 
                 "offside_left", "offside_right", "GameOver", "Goal_Left", 
                 "Goal_Right", "free_kick_left", "free_kick_right", 
                 "direct_free_kick_left", "direct_free_kick_right"};


    PlayMode::PlayMode(int mode)
        : mode_{mode}
    { }

    PlayMode::PlayMode(const std::string& name)
    {
        for (mode_ = 0; mode_ < NUM_MODES && name != PLAY_MODE_STRINGS[mode_]; mode_++)
        { }
    }

    PlayMode::operator int() const
    {
        return mode_;
    }

    PlayMode::operator std::string() const
    {
        return ToString();
    }

    std::string PlayMode::ToString() const
    {
        return PLAY_MODE_STRINGS[mode_];
    }

    int PlayMode::ToInt() const
    {
        return mode_;
    }

}