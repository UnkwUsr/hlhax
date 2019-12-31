#include "funcs/visuals/tracer/tracer.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/shit/shit.h"



namespace Cvars
{
    cvar_t* tracer;
    cvar_t* tracer_width;
    cvar_t* tracer_r;
    cvar_t* tracer_g;
    cvar_t* tracer_b;
    cvar_t* tracer_offset;
}

namespace Tracer {
    DEF_HOOK(HUD_AddEntity)

    void Init()
    {
        ADD_HOOK(HUD_AddEntity, gp_Client)

        Cvars::tracer = CREATE_CVAR("tracer", "1");
        Cvars::tracer_width = CREATE_CVAR("tracer_width", "0.3");
        Cvars::tracer_r = CREATE_CVAR("tracer_r", "0");
        Cvars::tracer_g = CREATE_CVAR("tracer_g", "100");
        Cvars::tracer_b = CREATE_CVAR("tracer_b", "100");
        Cvars::tracer_offset = CREATE_CVAR("tracer_offset", "25");
    }


    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(Cvars::tracer->value == 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(!ent->player || !isAlive(ent->curstate))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        cl_entity_t* me = gp_Engine->GetLocalPlayer();
        DrawTraceLine(ent, me);

        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }


    void DrawTraceLine(cl_entity_t *from, cl_entity_t *to)
    {
        int beamindex = gp_Engine->pEventAPI->
            EV_FindModelIndex("sprites/laserbeam.spr");

        float life = 0.001f;
        float width = Cvars::tracer_width->value;
        float r = Cvars::tracer_r->value / 255;
        float g = Cvars::tracer_g->value / 255;
        float b = Cvars::tracer_b->value / 255;

//      gp_Engine->pEfxAPI->R_BeamEnts(from->index, to->index,
        vec3_t offseted_to = to->origin;

        offseted_to[2] += Cvars::tracer_offset->value;
        gp_Engine->pEfxAPI->R_BeamPoints(from->origin, offseted_to,
            beamindex, life, width, 0, 32, 2, 0, 0, r, g, b);
    }

} // namespace Barrel
