#include "funcs/aim/fastzoom/fastzoom.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"
#include "funcs/utils.h"



namespace Cvars {
    cvar_t* fastzoom;
}


namespace FastZoom {
    DEF_HOOK(CL_CreateMove)


    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)

        Cvars::fastzoom = CREATE_CVAR("fastzoom", "0");
    }


    void CL_CreateMove(float frametime, usercmd_t *cmd, int active) {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);
        if(Cvars::fastzoom->value == 0)
            return;

        if(cmd->buttons & IN_ATTACK) {
            cmd->buttons |= IN_ATTACK2;
        }
    }

} // namespace FastZoom

