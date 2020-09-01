#ifndef VISUALS_ESP_H
#define VISUALS_ESP_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Esp {
    void Init();

    DECL_HOOK(int, HUD_Redraw, float time, int intermission)

    void DrawBox( int x , int y , int w , int h , int linewidth , int r , int g , int b , int a );
} // namespace ESP

#endif // VISUALS_ESP_H
