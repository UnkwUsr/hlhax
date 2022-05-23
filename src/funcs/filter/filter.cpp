#include "funcs/filter/filter.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/hooks/usermsg.h"
#include "funcs/utils.h"
#include <cstring>



float AngleBetweenVectors(Vector v1, Vector v2);

namespace Cvars
{
    cvar_t* filter_ignore_teammates;
    cvar_t* filter_check_player;
    cvar_t* filter_check_alive;
}

namespace Filter {
    DEF_HOOK(HUD_AddEntity)
    DEF_HOOK(CL_CreateMove)
    DEF_HOOK(TeamInfo)

    player_s players[32];

    void Init()
    {
        for(int i = 0; i < 32; i++) {
            player_s player = {false, 0, 0.0, '\0'};
            players[i] = player;
        }
        // TODO: need add func called on reconnect for reset team for all players

        // TODO: on hud_redraw (or something) add clearing field 'valid' for
        // all players. It should be cleared before hud_addentitt

        Cvars::filter_ignore_teammates = CREATE_CVAR("filter_ignore_teammates", "1");
        Cvars::filter_check_player = CREATE_CVAR("filter_check_player", "1");
        Cvars::filter_check_alive = CREATE_CVAR("filter_check_alive", "1");
    }
    void SetHooks() {
        ADD_HOOK(HUD_AddEntity, gp_Client)
        ADD_HOOK(CL_CreateMove, gp_Client)
        ADD_USERMSG_HOOK(TeamInfo)
    }
    void Terminate() {
        REM_USERMSG_HOOK(TeamInfo)
    }

    int TeamInfo(const char *pszName, int iSize, void *pbuf) {
        BEGIN_READ(pbuf, iSize);

        int iIndex = READ_BYTE();
        char *szTeam = READ_STRING();

        if(iIndex > 32 || iIndex < 0) {
            /* gp_Engine->Con_Printf("anticheat send fake teaminfo? iIndex = %i\n", iIndex); */

            return CALL_ORIG(TeamInfo, pszName, iSize, pbuf);
        }

        /* gp_Engine->Con_Printf("team %s for %i\n", szTeam, iIndex); */
        strcpy(players[iIndex].team_name, szTeam);

        return CALL_ORIG(TeamInfo, pszName, iSize, pbuf);
    }

    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(ent->index > 32 || ent->index < 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        players[ent->index].valid = false;

        if(Cvars::filter_check_player->value != 0 && !ent->player)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(ent->index == gp_Engine->GetLocalPlayer()->index)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(Cvars::filter_check_alive->value != 0 && !isAlive(ent->curstate))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(Cvars::filter_ignore_teammates->value != 0 && isTeammate(ent->index))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        players[ent->index].valid = true;

        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }

    void CL_CreateMove(float frametime, usercmd_t *cmd, int active) {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);

        for(int i = 1; i < 32; i++) {
            if(!players[i].valid)
                continue;

            cl_entity_t* ent = gp_Engine->GetEntityByIndex(i);

            Vector vDiff = gp_pmove->origin - ent->origin;
            players[i].distance = vDiff.Length();

            Vector vAim;
            gp_Engine->pfnAngleVectors(ent->angles, vAim, NULL, NULL);
            float angle = AngleBetweenVectors(vAim, vDiff);
            players[i].view_angle = angle;
        }
    }


    bool isValidPlayer(int index) {
        if(index > 32 || index < 0)
            return false;
        // check is updated
        if (gp_Engine->GetEntityByIndex(index)->curstate.messagenum
                <
                gp_Engine->GetLocalPlayer()->curstate.messagenum)
            return false;

        return players[index].valid;
    }

    bool isTeammate(int index) {
        if(players[index].team_name[0] == '\0')
            return false;
        if(strcmp(players[index].team_name, players[gp_Engine->GetLocalPlayer()->index].team_name) == 0)
            return true;

        return false;
    }

    // lower rating - better target to choose
    int targetRating(int index) {
        player_s target = players[index];

        // TODO: more complex calculation (with distance)
        return target.view_angle * (target.distance / 10);
    }
} // namespace Filter


float AngleBetweenVectors( Vector v1, Vector v2 ) {
    float l1 = v1.Length();
    float l2 = v2.Length();

    if ( !l1 || !l2 )
        return 0.0f;

    float dot = DotProduct(v1, v2);
    float angle = acos(dot / (l1 * l2));
    angle = (angle  * 180.0f) / M_PI;

    return angle;
}
