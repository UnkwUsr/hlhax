#ifndef SPINHACK_H
#define SPINHACK_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Spinhack {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)
} // namespace Spinhack

#endif // SPINHACK_H
