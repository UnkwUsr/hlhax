#ifndef FPS_SET_H
#define FPS_SET_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace FpsBoost {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)

    void fps_boost_on();
    void fps_boost_off();

    int calc_fps();
} // namespace FpsBoost

#endif // FPS_SET_H
