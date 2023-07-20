#include "funcs/movement/fps_boost/fps_boost.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"



namespace Cvars {
    cvar_t* fps_critical;
    cvar_t* fps_boost_cmd_on;
    cvar_t* fps_boost_cmd_off;
}

namespace FpsBoost {
    DEF_HOOK(CL_CreateMove)

    bool b_fps_boost;

    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)

        // Note: before using fps_boost keep sure that fps_max is much higher
        // than fps_critical (but do not set fps_max very high!!! Best value is
        // just 1000, as higher it goes, slower you actually will be. Probably.
        // Read more at: https://wiki.sourceruns.org/wiki/FPS_Effects)

        CREATE_TGL_CMD("fps_boost", fps_boost_on, fps_boost_off)

        Cvars::fps_critical = CREATE_CVAR("fps_critical", "500");
        Cvars::fps_boost_cmd_on = CREATE_CVAR("fps_boost_cmd_on", "\
                hud_draw 0;\
                r_drawentities 0;\
                r_drawviewmodel 0;\
                cv_esp 0;\
                cv_tracer 0;\
                cv_barrel 0;\
                fps_max 1000;\
                fps_override 1;");
        Cvars::fps_boost_cmd_off = CREATE_CVAR("fps_boost_cmd_off", "\
                hud_draw 1;\
                r_drawentities 1;\
                r_drawviewmodel 1;\
                cv_esp 1;\
                cv_tracer 1;\
                cv_barrel 1;\
                fps_max 100;");

    }


    void CL_CreateMove(float frametime, usercmd_t *cmd, int active)
    {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);
        if(!b_fps_boost)
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


    void fps_boost_on()
    {
        b_fps_boost = true;

        gp_Engine->pfnClientCmd(Cvars::fps_boost_cmd_on->string);
    }
    void fps_boost_off()
    {
        b_fps_boost = false;
        gp_Engine->Cvar_SetValue("r_norefresh", 0);
        gp_Engine->Cvar_SetValue("cl_showfps", 1);

        gp_Engine->pfnClientCmd(Cvars::fps_boost_cmd_off->string);
    }


    int calc_fps()
    {
        static double rolling_fps;
        rolling_fps = 0.6 * rolling_fps + *gp_host_frametime * 0.4;

        int cur_fps = floor(1.0 / rolling_fps);

        return cur_fps;
    }
} // namespace FpsBoost
