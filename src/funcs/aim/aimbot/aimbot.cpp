#include "funcs/aim/aimbot/aimbot.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"
#include "funcs/utils.h"
#include "funcs/filter/filter.h"



void tkzfuncVectorAngles( const float *forward, float *angles )
{
    float tmp, yaw, pitch;

    if (forward[1] == 0 && forward[0] == 0)
    {
        yaw = 0;
        if (forward[2] > 0)
            pitch = 270;
        else
            pitch = 90;
    }
    else
    {
        yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
        if (yaw < 0)
            yaw += 360;

        tmp = sqrt (forward[0]*forward[0] + forward[1]*forward[1]);
        pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
        if (pitch < 0)
            pitch += 360;
    }

    angles[0] = pitch;
    angles[1] = yaw;
    angles[2] = 0;

    while(angles[0]<-89){angles[0]+=180;angles[1]+=180;}
    while(angles[0]>89){angles[0]-=180;angles[1]+=180;}
    while(angles[1]<-180){angles[1]+=360;}
    while(angles[1]>180){angles[1]-=360;}
}

namespace Cvars {
    cvar_t* aimbot_attack_auto;
    cvar_t* aimbot_attack_type;
    cvar_t* aimbot_attack_usecmd;
    cvar_t* aimbot_attack_cmd;
}


namespace AimBot {
    DEF_HOOK(CL_CreateMove)

    bool b_aimbot = false;

    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)

        CREATE_TGL_CMD("aimbot", aimbot_on, aimbot_off)

        Cvars::aimbot_attack_auto = CREATE_CVAR("aimbot_attack_auto", "0");
        Cvars::aimbot_attack_type = CREATE_CVAR("aimbot_attack_type", "1");
        Cvars::aimbot_attack_usecmd = CREATE_CVAR("aimbot_attack_usecmd", "0");
        Cvars::aimbot_attack_cmd = CREATE_CVAR("aimbot_attack_cmd", "+attack;wait;-attack");
    }


    void aimbot_on() {
        b_aimbot = true;
    }
    void aimbot_off() {
        b_aimbot = false;
    }


    bool testAimAngles(Vector vAimAngles) {
        // there part from triggerbot

    }


    void CL_CreateMove(float frametime, usercmd_t *cmd, int active) {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);

        if(!b_aimbot) {
            return;
        }


        Vector vAimAngles;
        int targetid = FindTargetId(&vAimAngles);
        if(targetid == -1)
            return;

        // aply aim angles
        gp_Engine->SetViewAngles(vAimAngles);

        if(Cvars::aimbot_attack_auto->value != 0) {
            if(Cvars::aimbot_attack_usecmd->value != 0)
                gp_Engine->pfnClientCmd(Cvars::aimbot_attack_cmd->string);
            else if(Cvars::aimbot_attack_type->value == 1)
                cmd->buttons |= IN_ATTACK;
            else if(Cvars::aimbot_attack_type->value == 2)
                cmd->buttons |= IN_ATTACK2;
        }
    }


    int FindTargetId(Vector *out_vAimAngles) {
        float min_rating = 9999999;
        int targetid = -1;

        for(int i = 1; i <= gp_Engine->GetMaxClients(); i++)
        {
            if(!Filter::isValidPlayer(i))
                continue;

            cl_entity_t* ent = gp_Engine->GetEntityByIndex(i);

            Vector vecBegin;
            VectorCopy(gp_pmove->origin, vecBegin);
            Vector vEye;
            gp_Engine->pEventAPI->EV_LocalPlayerViewheight(vEye);
            vecBegin = vecBegin + vEye;

            Vector vDiff = gp_Engine->GetEntityByIndex(i)->origin - gp_pmove->origin;

            Vector vAimAngles;
            tkzfuncVectorAngles(vDiff, vAimAngles);
            Vector forward;
            gp_Engine->pfnAngleVectors(vAimAngles, forward, NULL, NULL);
            Vector vecEnd = vecBegin + forward * 8192;

            pmtrace_t *tr = gp_Engine->PM_TraceLine(vecBegin, vecEnd, PM_TRACELINE_PHYSENTSONLY, 2, -1);
            // hit map
            if(tr->ent <= 0)
                continue;
            int entindex = gp_pmove->physents[tr->ent].info;
            if(!Filter::isValidPlayer(entindex))
                continue;

            float rating = Filter::targetRating(i);
            if(rating > min_rating)
                continue;

            min_rating = rating;
            *out_vAimAngles = vAimAngles;
            targetid = i;
        }

        return targetid;
    }

} // namespace AimBot

