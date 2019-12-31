#ifndef VISUALS_NOFLASH_H
#define VISUALS_NOFLASH_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace NoFlash {
    void Init();

    DECL_HOOK(int, HUD_Redraw, float time, int intermission)
}

#endif // VISUALS_NOFLASH_H
