#include "utils/shit/shit.h"
#include "globals.h"


bool isAlive(entity_state_t curstate)
{
    // return !(ent->curstate.effects & EF_NODRAW) && ent->curstate.movetype != 6 && ent->curstate.movetype != 0;
    return curstate.movetype != 6 && curstate.movetype != 0;
}

const char* getPlayerNameByIndex(int index)
{
    hud_player_info_t plr_info;
    gp_Engine->pfnGetPlayerInfo(index, &plr_info);

    return plr_info.name;
}
