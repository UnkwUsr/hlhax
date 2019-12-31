#include "funcs/visuals/noflash/noflash.h"
#include "globals.h"
#include "utils/cvars/cvars.h"



namespace Cvars
{
    cvar_t* noflash;
}

namespace NoFlash {
    DEF_HOOK(HUD_Redraw)

    void Init()
    {
        ADD_HOOK(HUD_Redraw, gp_Client)

        Cvars::noflash = CREATE_CVAR("noflash", "1");
    }


    int HUD_Redraw(float time, int intermission)
    {
        if(Cvars::noflash->value == 0)
            return CALL_ORIG(HUD_Redraw, time, intermission);

        screenfade_t cur_fade;

        gp_Engine->pfnGetScreenFade(&cur_fade);

        if(cur_fade.fadealpha > 32)
        {
            cur_fade.fadealpha = 32;

            gp_Engine->pfnSetScreenFade(&cur_fade);
        }
        // gp_Engine->Con_Printf("\nfader = %d, fadeg = %d \
            // fadeb = %d\n", cur_fade.fader, cur_fade.fadeg,
            // cur_fade.fadeb);

        return CALL_ORIG(HUD_Redraw, time, intermission);
    }
} // namespace NoFlash
