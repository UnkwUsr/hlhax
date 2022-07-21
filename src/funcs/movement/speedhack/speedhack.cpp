#include "funcs/movement/speedhack/speedhack.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"


namespace Cvars{
    cvar_t* speed;
}

namespace Speedhack {


    void Init()
    {
        CREATE_TGL_CMD("speed", speed_on, speed_off)
        Cvars::speed = CREATE_CVAR("speed", "100");
    }

    void speed_on()
    {
        *gp_speed_val = Cvars::speed->value * 1000;;
    }
    void speed_off()
    {
        *gp_speed_val = 1000;
    }
} // namespace Speedhack
