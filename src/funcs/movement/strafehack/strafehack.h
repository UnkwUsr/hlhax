#ifndef STRAFEHACK_H
#define STRAFEHACK_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Strafehack {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)

    void strafehack_on();
    void strafehack_off();
} // namespace Strafehack


#endif // STRAFEHACK_H
