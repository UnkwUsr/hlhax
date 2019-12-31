#include "funcs/movement/spinhack/spinhack.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include <cstring>



namespace Cvars {
    cvar_t* spinhack;
    cvar_t* spinhack_val;
}

namespace Spinhack {
    DEF_HOOK(CL_CreateMove)

    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)

        Cvars::spinhack = CREATE_CVAR("spinhack", "0");
        Cvars::spinhack_val = CREATE_CVAR("spinhack_val", "5");
    }


    void CL_CreateMove(float frametime, usercmd_t *cmd, int active)
    {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);

        if(Cvars::spinhack->value == 0)
            return;

        cl_entity_t *pLocal;

        Vector viewforward, viewright, viewup, aimforward, aimright, aimup, vTemp;

        float newforward, newright, newup, fTime;
        float forward = cmd->forwardmove;
        float right = cmd->sidemove;
        float up = cmd->upmove;
        pLocal = gp_Engine->GetLocalPlayer();

        if(!pLocal)
            return;

        if(pLocal->curstate.movetype == MOVETYPE_WALK)
        {
            gp_Engine->pfnAngleVectors(Vector(0.0f, cmd->viewangles.y, 0.0f), viewforward, viewright, viewup);
        }
        else
        {
            gp_Engine->pfnAngleVectors(cmd->viewangles, viewforward, viewright, viewup);
        }

        if(pLocal->curstate.movetype == MOVETYPE_WALK &&
            !(cmd->buttons & IN_ATTACK) &&
            !(cmd->buttons & IN_ATTACK2) &&
            !((cmd->buttons & IN_JUMP) && (cmd->buttons & IN_DUCK)) &&
            !(cmd->buttons & IN_USE))
        {
            fTime = gp_Engine->GetClientTime();
            cmd -> viewangles . y = fmod ( fTime * Cvars::spinhack_val->value * 360.0f , 360.0f );
        }
        if( pLocal -> curstate . movetype == MOVETYPE_WALK )
        {
            gp_Engine->pfnAngleVectors ( Vector ( 0.0f , cmd -> viewangles . y , 0.0f ), aimforward , aimright , aimup );
        }
        else
        {
            gp_Engine->pfnAngleVectors ( cmd -> viewangles , aimforward , aimright , aimup );
        }

        newforward = DotProduct ( forward * viewforward . Normalize (), aimforward ) + DotProduct ( right * viewright . Normalize (), aimforward ) + DotProduct ( up * viewup . Normalize (), aimforward );
        newright = DotProduct ( forward * viewforward . Normalize (), aimright ) + DotProduct ( right * viewright . Normalize (), aimright ) + DotProduct ( up * viewup . Normalize (), aimright );
        newup = DotProduct ( forward * viewforward . Normalize (), aimup ) + DotProduct ( right * viewright . Normalize (), aimup ) + DotProduct ( up * viewup . Normalize (), aimup );

        cmd -> forwardmove = newforward ;
        cmd -> sidemove = newright ;
        cmd -> upmove = newup ;
    }
} // namespace Spinhack
