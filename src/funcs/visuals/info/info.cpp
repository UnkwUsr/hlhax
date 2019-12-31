#include "funcs/visuals/info/info.h"
#include "globals.h"
#include "utils/cvars/cvars.h"



namespace Cvars
{
    cvar_t* info_speed_h;
    cvar_t* info_speed_v;
}

namespace Info {
    DEF_HOOK(HUD_Redraw)

    void Init()
    {
        ADD_HOOK(HUD_Redraw, gp_Client)

        Cvars::info_speed_h = CREATE_CVAR("info_speed_h", "1");
        Cvars::info_speed_v = CREATE_CVAR("info_speed_v", "0");
    }


    int HUD_Redraw(float time, int intermission)
    {
        if(gp_Engine->pfnGetCvarFloat("r_norefresh") == 1)
            return CALL_ORIG(HUD_Redraw, time, intermission);

        static int y;
        y = 60;

        if(Cvars::info_speed_h->value != 0)
        {
            char text[30];
            sprintf(text, "HSpeed: TODO");
            // TODO: find define func LengthXY in tkz sources
            //sprintf(text, "HSpeed: %.3f", gp_pmove->velocity.
            //    LengthXY());
            gp_Engine->pfnDrawConsoleString(640 / 2, 480 / 2 + y,
                text);
            y += 15;
        }
        if(Cvars::info_speed_v->value != 0)
        {
            char text[30];
            sprintf(text, "VSpeed: %.3f\n", gp_pmove->flFallVelocity);
            gp_Engine->pfnDrawConsoleString(640 / 2, 480 / 2 + y,
                text);
            y += 15;
        }

        return CALL_ORIG(HUD_Redraw, time, intermission);
    }
} // namespace Info
