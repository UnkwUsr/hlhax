#ifndef SGS_H
#define SGS_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Sgs {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)

    void sgs_on();
    void sgs_off();
} // namespace Sgs


#endif // SGS_H
