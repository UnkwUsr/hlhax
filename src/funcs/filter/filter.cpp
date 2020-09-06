#include "funcs/filter/filter.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/hooks/usermsg.h"
#include "utils/shit/shit.h"
#include <cstring>



namespace Cvars
{
    cvar_t* filter_ignore_teammates;
    cvar_t* filter_check_player;
    cvar_t* filter_check_alive;
}

namespace Filter {
    DEF_HOOK(HUD_AddEntity)
    DEF_HOOK(TeamInfo)

    bool players[32];
    char playersteam[32][MAX_TEAM_NAME];

    void Init()
    {
        for(int i = 0; i < 32; i++)
            players[i] = false;
        for(int i = 0; i < 32; i++)
            // TODO: need add func called on reconnect for reset team for all players
            playersteam[i][0] = '\0';

        Cvars::filter_ignore_teammates = CREATE_CVAR("filter_ignore_teammates", "1");
        Cvars::filter_check_player = CREATE_CVAR("filter_check_player", "1");
        Cvars::filter_check_alive = CREATE_CVAR("filter_check_alive", "1");
    }
    void SetHooks() {
        ADD_HOOK(HUD_AddEntity, gp_Client)
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
        strcpy(playersteam[iIndex], szTeam);

        return CALL_ORIG(TeamInfo, pszName, iSize, pbuf);
    }

    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(ent->index > 32 || ent->index < 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        players[ent->index] = false;

        if(Cvars::filter_check_player->value != 0 && !ent->player)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(ent->index == gp_Engine->GetLocalPlayer()->index)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(Cvars::filter_check_alive->value != 0 && !isAlive(ent->curstate))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(Cvars::filter_ignore_teammates->value != 0 && isTeammate(ent->index))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        players[ent->index] = true;

        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }


    bool isValidPlayer(int index) {
        if(index > 32 || index < 0)
            return false;
        // check is updated
        if (gp_Engine->GetEntityByIndex(index)->curstate.messagenum
                <
                gp_Engine->GetLocalPlayer()->curstate.messagenum)
            return false;

        return players[index];
    }

    bool isTeammate(int index) {
        if(playersteam[index][0] == '\0')
            return false;
        if(strcmp(playersteam[index], playersteam[gp_Engine->GetLocalPlayer()->index]) == 0)
            return true;

        return false;
    }
} // namespace Filter
