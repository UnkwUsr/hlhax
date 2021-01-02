#ifndef NORECOIL_H
#define NORECOIL_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace NoRecoil {
    void Init();

    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)
    DECL_HOOK(void, V_CalcRefdef, struct ref_params_s *pparams)
} // namespace NoRecoil

#endif // NORECOIL_H
