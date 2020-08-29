#include "funcs/visuals/esp/esp.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/shit/shit.h"
#include <vector>



namespace Cvars
{
    cvar_t* esp;
    cvar_t* esp_box_r;
    cvar_t* esp_box_g;
    cvar_t* esp_box_b;
    cvar_t* esp_name_r;
    cvar_t* esp_name_g;
    cvar_t* esp_name_b;
}

namespace Esp {
    DEF_HOOK(HUD_Redraw)
    DEF_HOOK(HUD_AddEntity)

    std::vector<cl_entity_t*> cords;

    void Init()
    {
        ADD_HOOK(HUD_Redraw, gp_Client)
        ADD_HOOK(HUD_AddEntity, gp_Client)

        Cvars::esp = CREATE_CVAR("esp", "1");
        Cvars::esp_box_r = CREATE_CVAR("esp_box_r", "0");
        Cvars::esp_box_g = CREATE_CVAR("esp_box_g", "0");
        Cvars::esp_box_b = CREATE_CVAR("esp_box_b", "255");
        Cvars::esp_name_r = CREATE_CVAR("esp_name_r", "255");
        Cvars::esp_name_g = CREATE_CVAR("esp_name_g", "255");
        Cvars::esp_name_b = CREATE_CVAR("esp_name_b", "255");
    }


    int HUD_Redraw(float time, int intermission)
    {
        if(Cvars::esp->value == 0)
            return CALL_ORIG(HUD_Redraw, time, intermission);

        // TODO: BUG: crash on changing map.
        // that is because in HUD_Redraw we trying to use ent's that not exist anymore
        // (because we store ent pointers in vector and then use it)
        // will be fixed with creating special func that will filter all ents,
        // and other funcs will work through that filter func

        for(auto &ent : cords)
        {
            float Screen[2];
            if(WorldToScreen(ent->origin , Screen)) {
                DrawBox(Screen[0], Screen[1],
                        30, 30, 5,
                        Cvars::esp_box_r->value,
                        Cvars::esp_box_g->value,
                        Cvars::esp_box_b->value,
                        255);
                gp_Engine->pfnDrawSetTextColor(
                        Cvars::esp_name_r->value / 255,
                        Cvars::esp_name_g->value / 255,
                        Cvars::esp_name_b->value / 255);
                gp_Engine->pfnDrawConsoleString(
                        Screen[0], Screen[1] + 40,
                        getPlayerNameByIndex(ent->index));
            }
        }

        cords.clear();

        return CALL_ORIG(HUD_Redraw, time, intermission);
    }

    int HUD_AddEntity(int type, cl_entity_t *ent,
        const char *modelname)
    {
        if(Cvars::esp->value == 0)
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
        if(!ent->player || !isAlive(ent->curstate))
            return CALL_ORIG(HUD_AddEntity, type, ent, modelname);

        cords.push_back(ent);

        return CALL_ORIG(HUD_AddEntity, type, ent, modelname);
    }

    void DrawBox( int x , int y , int w , int h , int linewidth , int r , int g , int b , int a )
    {
        gp_Engine->pfnFillRGBABlend( x , y , w , linewidth , r , g , b , a );
        gp_Engine->pfnFillRGBABlend( x + w - linewidth , y + linewidth , linewidth , h - linewidth , r , g , b , a );
        gp_Engine->pfnFillRGBABlend( x , y + linewidth , linewidth , h - linewidth , r , g , b , a );
        gp_Engine->pfnFillRGBABlend( x + linewidth , y + h - linewidth , w - linewidth * 2 , linewidth , r , g , b , a );
    }

} // namespace Esp
