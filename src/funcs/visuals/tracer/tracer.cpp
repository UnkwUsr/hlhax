#include "funcs/visuals/tracer/tracer.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/shit/shit.h"
#include "funcs/filter/filter.h"
#include <GL/gl.h>



namespace Cvars
{
    cvar_t* tracer;
    cvar_t* tracer_width;
    cvar_t* tracer_r;
    cvar_t* tracer_g;
    cvar_t* tracer_b;
}

namespace Tracer {
    DEF_HOOK(HUD_AddEntity)
    DEF_HOOK(Begin)

    void Init()
    {
        ADD_HOOK(HUD_AddEntity, gp_Client)
        /* ADD_HOOK(Begin, gp_Engine->pTriAPI) */

        Cvars::tracer = CREATE_CVAR("tracer", "1");
        Cvars::tracer_width = CREATE_CVAR("tracer_width", "0.3");
        Cvars::tracer_r = CREATE_CVAR("tracer_r", "0");
        Cvars::tracer_g = CREATE_CVAR("tracer_g", "100");
        Cvars::tracer_b = CREATE_CVAR("tracer_b", "100");
    }
    void Terminate() {
        // orig_Begin created by DEF_HOOK, ADD_HOOK, etc.
        // TODO: bit shitty. must be fixed in future
        /* gp_Engine->pTriAPI->Begin = orig_Begin; */
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

        DrawLine(vecBegin, ent->origin,
                Cvars::tracer_r->value, Cvars::tracer_g->value, Cvars::tracer_b->value,
                0.001, Cvars::tracer_width->value);


        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }

    // catch drawing beams and make him visible through walls
    void Begin(int primitiveCode) {
        if(primitiveCode == TRI_QUADS) {
            glDisable(GL_DEPTH_TEST);
        } else {
            glEnable(GL_DEPTH_TEST);
        }

        CALL_ORIG(Begin, primitiveCode);
    }

} // namespace Tracer
