#include "funcs/visuals/esp/esp.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/shit/shit.h"
#include <vector>



namespace Cvars
{
    cvar_t* esp;
    cvar_t* esp_r;
    cvar_t* esp_g;
    cvar_t* esp_b;
    cvar_t* esp_a;
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
        Cvars::esp_r = CREATE_CVAR("esp_r", "0");
        Cvars::esp_g = CREATE_CVAR("esp_g", "0");
        Cvars::esp_b = CREATE_CVAR("esp_b", "255");
        Cvars::esp_a = CREATE_CVAR("esp_a", "255");
    }


    int HUD_Redraw(float time, int intermission)
    {
        if(Cvars::esp->value == 0)
            return CALL_ORIG(HUD_Redraw, time, intermission);

        for(auto &ent : cords)
        {
            float Screen[2];
            if(WorldToScreen(ent->origin , Screen)) {
                DrawBox(Screen[0], Screen[1],
                        30, 30, 5,
                        Cvars::esp_r->value,
                        Cvars::esp_g->value,
                        Cvars::esp_b->value,
                        Cvars::esp_a->value);
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
