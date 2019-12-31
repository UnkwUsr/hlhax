#ifndef VISUALS_INFO_H
#define VISUALS_INFO_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Info {
    void Init();

    DECL_HOOK(int, HUD_Redraw, float time, int intermission)
}

#endif // VISUALS_INFO_H
