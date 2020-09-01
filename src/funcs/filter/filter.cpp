#include "funcs/filter/filter.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/shit/shit.h"



namespace Cvars
{
    /* cvar_t* filter_ignore_teammates; */
}

namespace Filter {
    DEF_HOOK(HUD_AddEntity)

    bool players[32];

    void Init()
    {
        for(int i = 0; i < 32; i++)
            players[i] = false;

        ADD_HOOK(HUD_AddEntity, gp_Client)

        /* Cvars::filter_ignore_teammates = CREATE_CVAR("filter_ignore_teammates", "0"); */
    }


    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(ent->index > 32 || ent->index < 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        players[ent->index] = false;

        if(!ent->player)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(ent->index == gp_Engine->GetLocalPlayer()->index)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(!isAlive(ent->curstate))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        /* if(Cvars::filter_ignore_teammates->value != 0 && checkisteammate(ent->index)) */
        /*     return CALL_ORIG(HUD_AddEntity, type, ent, modelname); */

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
} // namespace Filter
