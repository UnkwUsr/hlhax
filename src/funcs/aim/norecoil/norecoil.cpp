#include "funcs/aim/norecoil/norecoil.h"
#include "globals.h"
#include "utils/cvars/cvars.h"



namespace Cvars {
    cvar_t* norecoil;
}


namespace NoRecoil {
    DEF_HOOK(CL_CreateMove)
    DEF_HOOK(V_CalcRefdef)

    Vector recoil_angles;

    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)
        ADD_HOOK(V_CalcRefdef, gp_Client)

        Cvars::norecoil = CREATE_CVAR("norecoil", "1");
    }

    void V_CalcRefdef(struct ref_params_s *pparams) {
        if(Cvars::norecoil->value == 0)
            return CALL_ORIG(V_CalcRefdef, pparams);

        pparams->punchangle[0] = 0;
        pparams->punchangle[1] = 0;
        pparams->punchangle[2] = 0;

        return CALL_ORIG(V_CalcRefdef, pparams);
    }

    void CL_CreateMove(float frametime, usercmd_t *cmd, int active) {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);
        if(Cvars::norecoil->value == 0)
            return;

        cmd->viewangles = cmd->viewangles - recoil_angles;
    }

} // namespace NoRecoil

