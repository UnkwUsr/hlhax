#ifndef TRIGGER_BOT_H
#define TRIGGER_BOT_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace TriggerBot {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)

    void triggerbot_on();
    void triggerbot_off();
} // namespace TriggerBot

#endif // TRIGGER_BOT_H
