#include "funcs/movement/speedhack/speedhack.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"


namespace Cvars{
    cvar_t* xspeed;
}

namespace Speedhack {


    void Init()
    {
        CREATE_TGL_CMD("xspeed", xspeed_on, xspeed_off)
        Cvars::xspeed = CREATE_CVAR("xspeed", "100");

        gp_Engine->pfnClientCmd("bind h +" CMD_PREFIX"xspeed");
    }

    void xspeed_on()
    {
        float new_val = Cvars::xspeed->value * 1000;
        *gp_speed_val = new_val;
    }
    void xspeed_off()
    {
        float new_val = 1 * 1000;
        *gp_speed_val = new_val;
    }
} // namespace Speedhack
