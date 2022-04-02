#include "funcs/aim/triggerbot/triggerbot.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"
#include "funcs/utils.h"
#include "funcs/filter/filter.h"



namespace Cvars {
    cvar_t* triggerbot_attacktype;
    cvar_t* triggerbot_usecmd;
    cvar_t* triggerbot_attackcmd;
    cvar_t* triggerbot_drawshot;
    cvar_t* triggerbot_drawshot_time;
    cvar_t* triggerbot_minimal_distance;
}


namespace TriggerBot {
    DEF_HOOK(CL_CreateMove)

    bool b_triggerbot;

    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)

        CREATE_TGL_CMD("triggerbot", triggerbot_on, triggerbot_off)

        Cvars::triggerbot_attacktype = CREATE_CVAR("triggerbot_attacktype", "1");
        Cvars::triggerbot_usecmd = CREATE_CVAR("triggerbot_usecmd", "0");
        Cvars::triggerbot_attackcmd = CREATE_CVAR("triggerbot_attackcmd", "+attack;wait;-attack");
        Cvars::triggerbot_drawshot = CREATE_CVAR("triggerbot_drawshot", "0");
        Cvars::triggerbot_drawshot_time = CREATE_CVAR("triggerbot_drawshot_time", "0.5");
        // cs 1.6 knife:
        // ~63 - left mouse button
        // ~50 - right mouse button
        Cvars::triggerbot_minimal_distance = CREATE_CVAR("triggerbot_minimal_distance", "100000");
    }


    void triggerbot_on() {
        b_triggerbot = true;
    }
    void triggerbot_off() {
        b_triggerbot = false;
    }

    void CL_CreateMove(float frametime, usercmd_t *cmd, int active) {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);

        if(!b_triggerbot) {
            return;
        }

        Vector vecBegin;
        VectorCopy(gp_pmove->origin, vecBegin);
        Vector vEye;
        gp_Engine->pEventAPI->EV_LocalPlayerViewheight(vEye);
        vecBegin = vecBegin + vEye;

        Vector forward;
        gp_Engine->pfnAngleVectors(gp_pmove->angles, forward, NULL, NULL);

        Vector vecEnd = vecBegin + forward * 8192;

        pmtrace_t *tr = gp_Engine->PM_TraceLine( vecBegin, vecEnd, PM_TRACELINE_PHYSENTSONLY, 2, -1 );

        // hit map
        if(tr->ent <= 0)
            return;

        float distance = (tr->endpos - vecBegin).Length();
        if(distance > Cvars::triggerbot_minimal_distance->value) {
            return;
        }

        // WARNING! trace->ent is is the number in physent list, not the normal entity number
        cl_entity_t* ent = gp_Engine->GetEntityByIndex(gp_pmove->physents[tr->ent].info);

        if(!Filter::isValidPlayer(ent->index))
            return;

        // start attack
        if(Cvars::triggerbot_usecmd->value != 0)
            gp_Engine->pfnClientCmd(Cvars::triggerbot_attackcmd->string);
        else if(Cvars::triggerbot_attacktype->value == 1)
            cmd->buttons |= IN_ATTACK;
        else if(Cvars::triggerbot_attacktype->value == 2)
            cmd->buttons |= IN_ATTACK2;

        if(Cvars::triggerbot_drawshot->value != 0)
            DrawLine(vecBegin, tr->endpos, 255, 0, 0, 1,
                    Cvars::triggerbot_drawshot_time->value, 0.8);
    }

} // namespace TriggerBot

