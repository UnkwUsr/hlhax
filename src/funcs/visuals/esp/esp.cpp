#include "funcs/visuals/esp/esp.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "funcs/utils.h"
#include "funcs/filter/filter.h"



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

    void Init()
    {
        ADD_HOOK(HUD_Redraw, gp_Client)

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

        for(int i = 1; i <= gp_Engine->GetMaxClients(); i++) {
            if(!Filter::isValidPlayer(i))
                continue;

            cl_entity_t* ent = gp_Engine->GetEntityByIndex(i);

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


        return CALL_ORIG(HUD_Redraw, time, intermission);
    }

    void DrawBox( int x , int y , int w , int h , int linewidth , int r , int g , int b , int a )
    {
        gp_Engine->pfnFillRGBABlend( x , y , w , linewidth , r , g , b , a );
        gp_Engine->pfnFillRGBABlend( x + w - linewidth , y + linewidth , linewidth , h - linewidth , r , g , b , a );
        gp_Engine->pfnFillRGBABlend( x , y + linewidth , linewidth , h - linewidth , r , g , b , a );
        gp_Engine->pfnFillRGBABlend( x + linewidth , y + h - linewidth , w - linewidth * 2 , linewidth , r , g , b , a );
    }

} // namespace Esp
