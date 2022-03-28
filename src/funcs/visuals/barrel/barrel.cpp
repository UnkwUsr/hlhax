#include "funcs/visuals/barrel/barrel.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "funcs/utils.h"
#include "funcs/filter/filter.h"



namespace Cvars
{
    cvar_t* barrel;
    cvar_t* barrel_width;
    cvar_t* barrel_r;
    cvar_t* barrel_g;
    cvar_t* barrel_b;
}

namespace Barrel {
    DEF_HOOK(HUD_AddEntity)

    void Init()
    {
        ADD_HOOK(HUD_AddEntity, gp_Client)

        Cvars::barrel = CREATE_CVAR("barrel", "1");
        Cvars::barrel_width = CREATE_CVAR("barrel_width", "0.8");
        Cvars::barrel_r = CREATE_CVAR("barrel_r", "0");
        Cvars::barrel_g = CREATE_CVAR("barrel_g", "255");
        Cvars::barrel_b = CREATE_CVAR("barrel_b", "0");
    }


    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(Cvars::barrel->value == 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(!Filter::isValidPlayer(ent->index))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);


        Vector vecBegin;
        VectorCopy(ent->origin, vecBegin);
        if(ent->curstate.usehull)
            vecBegin[2]+=12;
        else
            vecBegin[2]+=17;
        vecBegin[2] += 9;

        Vector forward;
        gp_Engine->pfnAngleVectors(ent->angles, forward, NULL, NULL);
        forward[2] = -forward[2];

        vecBegin[0] += forward[0] * 10;
        vecBegin[1] += forward[1] * 10;
        vecBegin[2] += forward[2] * 10;
        Vector vecEnd = vecBegin + forward * 8192;

        pmtrace_t *pmtrace = gp_Engine->PM_TraceLine(vecBegin, vecEnd, PM_TRACELINE_PHYSENTSONLY, 2, -1 );

        DrawLine(vecBegin, pmtrace->endpos,
                Cvars::barrel_r->value, Cvars::barrel_g->value, Cvars::barrel_b->value, 1,
                0.001, Cvars::barrel_width->value);


        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }
} // namespace Barrel
