#ifndef FASTZOOM_H
#define FASTZOOM_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace FastZoom {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)
} // namespace FastZoom

#endif // FASTZOOM_H
