#include "funcs/visuals/tracer/tracer.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "funcs/utils.h"
#include "funcs/filter/filter.h"
#include <GL/gl.h>



namespace Cvars
{
    cvar_t* tracer;
    cvar_t* tracer_width;
    cvar_t* tracer_r;
    cvar_t* tracer_g;
    cvar_t* tracer_b;
    cvar_t* tracer_fix_walls;
}

namespace Tracer {
    DEF_HOOK(HUD_AddEntity)
    DEF_HOOK(Color4f)

    // to uniquely identify when our tracer beam is rendering
    const float UNIQ_VALUE_ALPHA = 5.93;

    void Init()
    {
        ADD_HOOK(HUD_AddEntity, gp_Client)
        ADD_HOOK(Color4f, gp_Engine->pTriAPI)

        Cvars::tracer = CREATE_CVAR("tracer", "1");
        Cvars::tracer_width = CREATE_CVAR("tracer_width", "0.3");
        Cvars::tracer_r = CREATE_CVAR("tracer_r", "0");
        Cvars::tracer_g = CREATE_CVAR("tracer_g", "100");
        Cvars::tracer_b = CREATE_CVAR("tracer_b", "100");
        Cvars::tracer_fix_walls = CREATE_CVAR("tracer_fix_walls", "1");
    }

    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(Cvars::tracer->value == 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(!Filter::isValidPlayer(ent->index))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        Vector vecBegin;
        VectorCopy(gp_pmove->origin, vecBegin);

        Vector vEye;
        gp_Engine->pEventAPI->EV_LocalPlayerViewheight(vEye);
        vecBegin = vecBegin + vEye;

        Vector forward;
        gp_Engine->pfnAngleVectors(gp_pmove->angles, forward, NULL, NULL);
        vecBegin = vecBegin + forward * 100;

        Vector vecEnd = ent->origin;

        DrawLine(vecBegin, vecEnd, Cvars::tracer_r->value,
                 Cvars::tracer_g->value, Cvars::tracer_b->value,
                 UNIQ_VALUE_ALPHA, 0.001, Cvars::tracer_width->value);

        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }

    // catch drawing beams and make him visible through walls
    void Color4f(float r, float g, float b, float a) {
        CALL_ORIG(Color4f, r, g, b, a);

        if(Cvars::tracer_fix_walls->value == 0)
            return;

        if(a == UNIQ_VALUE_ALPHA)
            glDisable(GL_DEPTH_TEST);
        else
            glEnable(GL_DEPTH_TEST);
    }

} // namespace Tracer
