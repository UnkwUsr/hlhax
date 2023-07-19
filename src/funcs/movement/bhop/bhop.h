#ifndef BHOP_H
#define BHOP_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Bhop {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)
} // namespace Bhop


#endif // BHOP_H
