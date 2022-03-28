#include "funcs/utils.h"
#include "globals.h"


bool isAlive(entity_state_t curstate)
{
    // return !(ent->curstate.effects & EF_NODRAW) && ent->curstate.movetype != 6 && ent->curstate.movetype != 0;
    return curstate.movetype != 6 && curstate.movetype != 0;
}

char* getPlayerNameByIndex(int index)
{
    hud_player_info_t plr_info;
    gp_Engine->pfnGetPlayerInfo(index, &plr_info);

    return plr_info.name;
}

bool WorldToScreen( float *pflOrigin , float *pflVecScreen )
{
    int iResult = gp_Engine->pTriAPI->WorldToScreen( pflOrigin , pflVecScreen );

    SCREENINFO g_Screen;
    g_Screen.iSize = sizeof( SCREENINFO );
    gp_Engine->pfnGetScreenInfo( &g_Screen );

    if ( pflVecScreen[0] < 1 && pflVecScreen[1] < 1 && pflVecScreen[0] > -1 && pflVecScreen[1] > -1 && !iResult )
    {
        pflVecScreen[0] = pflVecScreen[0] * ( g_Screen.iWidth / 2 ) + ( g_Screen.iWidth / 2 );
        pflVecScreen[1] = -pflVecScreen[1] * ( g_Screen.iHeight / 2 ) + ( g_Screen.iHeight / 2 );
        return true;
    }

    return false;
}

void DrawLine(float *from, float *to, float r, float g, float b, float a, float life, float width) {
    static int beamindex = gp_Engine->pEventAPI->
        EV_FindModelIndex("sprites/laserbeam.spr");

    r /= 255;
    g /= 255;
    b /= 255;

    gp_Engine->pEfxAPI->R_BeamPoints(from, to, beamindex, life,
            width, 0, a, 0, 0, 0, r, g, b);
}
