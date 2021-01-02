#ifndef AIMBOT_H
#define AIMBOT_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace AimBot {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)

    void aimbot_on();
    void aimbot_off();

    int FindTargetId(Vector *out_vAimAngles);
} // namespace AimBot

#endif // AIMBOT_H
