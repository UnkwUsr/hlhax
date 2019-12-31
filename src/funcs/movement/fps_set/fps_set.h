#ifndef FPS_SET_H
#define FPS_SET_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace FpsSet {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)

    void fps_set_on();
    void fps_set_off();

    int calc_fps();
} // namespace FpsSet

#endif // FPS_SET_H
