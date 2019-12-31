#include "funcs/movement/fps_set/fps_set.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"



namespace Cvars {
    cvar_t* fps_critical;
}

namespace FpsSet {
    DEF_HOOK(CL_CreateMove)

    bool b_fps_set;

    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)

        CREATE_TGL_CMD("fps_set", fps_set_on, fps_set_off)

        Cvars::fps_critical = CREATE_CVAR("fps_critical", "500");

        gp_Engine->pfnClientCmd("alias tgl_fps_set fps_set_on");
        gp_Engine->pfnClientCmd("alias fps_set_on \"+" CMD_PREFIX"fps_set;alias tgl_fps_set fps_set_off\"");
        gp_Engine->pfnClientCmd("alias fps_set_off \"-" CMD_PREFIX"fps_set;alias tgl_fps_set fps_set_on\"");
        gp_Engine->pfnClientCmd("bind mouse5 \"tgl_fps_set;tgl_hud_draw\"");

        gp_Engine->pfnClientCmd("fps_max 10000");
    }


    void CL_CreateMove(float frametime, usercmd_t *cmd, int active)
    {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);
        if(!b_fps_set)
            return;

        if(cmd->buttons & IN_SCORE ||
            Cvars::fps_critical->value == 0)
        {
            gp_Engine->Cvar_SetValue("r_norefresh", 0);
            gp_Engine->Cvar_SetValue("cl_showfps", 1);

            return;
        }


        int cur_fps = calc_fps();
        if(cur_fps < Cvars::fps_critical->value)
        {
            gp_Engine->Cvar_SetValue("r_norefresh", 1);
            gp_Engine->Cvar_SetValue("cl_showfps", 0);
        }
        else
        {
            gp_Engine->Cvar_SetValue("r_norefresh", 0);
            gp_Engine->Cvar_SetValue("cl_showfps", 1);
        }

    }


    void fps_set_on()
    {
        b_fps_set = true;
    }
    void fps_set_off()
    {
        b_fps_set = false;

        gp_Engine->Cvar_SetValue("r_norefresh", 0);
        gp_Engine->Cvar_SetValue("cl_showfps", 1);
    }


    int calc_fps()
    {
        static double rolling_fps;
        rolling_fps = 0.6 * rolling_fps + *gp_host_frametime * 0.4;

        int cur_fps = floor(1.0 / rolling_fps);

        return cur_fps;
    }
} // namespace FpsSet
