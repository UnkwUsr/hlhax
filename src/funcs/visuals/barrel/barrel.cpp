#include "funcs/visuals/barrel/barrel.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/shit/shit.h"



namespace Cvars
{
    cvar_t* barrel;
    cvar_t* barrel_len;
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
        Cvars::barrel_len = CREATE_CVAR("barrel_len", "450");
        Cvars::barrel_width = CREATE_CVAR("barrel_width", "0.8");
        Cvars::barrel_r = CREATE_CVAR("barrel_r", "0");
        Cvars::barrel_g = CREATE_CVAR("barrel_g", "255");
        Cvars::barrel_b = CREATE_CVAR("barrel_b", "0");
    }


    void DrawLine(float *from, float *to)
    {
        int beamindex = gp_Engine->pEventAPI->
            EV_FindModelIndex("sprites/laserbeam.spr");

        float life = 0.001f;
        float width = Cvars::barrel_width->value;
        float r = Cvars::barrel_r->value / 255;
        float g = Cvars::barrel_g->value / 255;
        float b = Cvars::barrel_b->value / 255;

        gp_Engine->pEfxAPI->R_BeamPoints(from, to, beamindex, life,
            width, 0, 32, 2, 0, 0, r, g, b);
    }

    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(Cvars::barrel->value == 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(!ent->player || !isAlive(ent->curstate))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);


        Vector vecBegin;
        VectorCopy(ent->origin, vecBegin);
        if(ent->curstate.usehull)
            vecBegin[2]+=12;
        else
            vecBegin[2]+=17;

        Vector forward;
        gp_Engine->pfnAngleVectors(ent->angles, forward, NULL, NULL);

        vecBegin[0] += forward[0] * 10;
        vecBegin[1] += forward[1] * 10;
        vecBegin[2] += forward[2] * 10;
        Vector vecEnd = vecBegin + forward * Cvars::barrel_len->value;

        DrawLine(vecBegin, vecEnd);

        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }


} // namespace Barrel
