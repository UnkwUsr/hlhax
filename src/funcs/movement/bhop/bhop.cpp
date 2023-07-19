#include "funcs/movement/bhop/bhop.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"

namespace Cvars {
    cvar_t* bhop;
}

namespace Bhop {
    DEF_HOOK(CL_CreateMove)

    void Init() {
        ADD_HOOK(CL_CreateMove, gp_Client)

        Cvars::bhop = CREATE_CVAR("bhop", "1");
    }

    void CL_CreateMove(float frametime, usercmd_t* cmd, int active) {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);
        if(Cvars::bhop->value == 0)
            return;

        static bool s_jump_was_down_last_frame = false;

        bool should_release_jump = !(gp_pmove->flags & FL_ONGROUND) &&
                                   gp_pmove->movetype == MOVETYPE_WALK;

        if(s_jump_was_down_last_frame && gp_pmove->flags & FL_ONGROUND &&
           gp_pmove->movetype == MOVETYPE_WALK)
            should_release_jump = true;

        if(should_release_jump)
            cmd->buttons &= ~IN_JUMP;

        s_jump_was_down_last_frame = ((cmd->buttons & IN_JUMP) != 0);
    }
} // namespace Bhop
