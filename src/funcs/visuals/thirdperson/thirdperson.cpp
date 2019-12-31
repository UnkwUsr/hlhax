#include "funcs/visuals/thirdperson/thirdperson.h"
#include "globals.h"
#include "utils/cvars/cvars.h"



namespace Cvars
{
    cvar_t* thirdperson;
}

namespace ThirdPerson {
    DEF_HOOK(HUD_Redraw)

    void Init()
    {
        ADD_HOOK(HUD_Redraw, gp_Client)

        Cvars::thirdperson = CREATE_CVAR("thirdperson", "0");
    }


    int HUD_Redraw(float time, int intermission)
    {
        if(Cvars::thirdperson->value == 0)
            return CALL_ORIG(HUD_Redraw, time, intermission);

        gp_Engine->pfnGetCvarPointer("chase_active")->value = 1;

        return CALL_ORIG(HUD_Redraw, time, intermission);
    }

} // namespace ThirdPerson
