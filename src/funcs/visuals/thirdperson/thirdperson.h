#ifndef VISUALS_THIRDPERSON_H
#define VISUALS_THIRDPERSON_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace ThirdPerson {
    void Init();

    DECL_HOOK(int, HUD_Redraw, float time, int intermission)
}

#endif // VISUALS_THIRDPERSON_H
