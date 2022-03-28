#include "funcs/movement/sgs/sgs.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"



namespace Cvars {
    cvar_t* sgs_standup;
    // cvar_t* sgs_slowdown;
    cvar_t* sgs_bhop;
}

namespace Sgs {
    bool b_sgs;

    DEF_HOOK(CL_CreateMove)

    void Init()
    {
        ADD_HOOK(CL_CreateMove, gp_Client)

        CREATE_TGL_CMD("sgs", sgs_on, sgs_off)

        Cvars::sgs_standup = CREATE_CVAR("sgs_standup", "0");
        // Cvars::sgs_slowdown = CREATE_CVAR("sgs_slowdown", "0");
        Cvars::sgs_bhop = CREATE_CVAR("sgs_bhop", "0");
    }


    void CL_CreateMove(float frametime, usercmd_t *cmd, int active)
    {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);

        if(!b_sgs)
            return;


        Vector vtmp = gp_pmove->origin; vtmp[2] = -4096.0f;
        pmtrace_t *trace = gp_Engine->PM_TraceLine(gp_pmove->origin, vtmp, 1, (gp_pmove->flags & FL_DUCKING) ? 1 : 0, -1);

        float glocal_fHeightGround = gp_pmove->origin.z - trace->endpos.z;
        float glocal_fGroundAngle = acos(trace->plane.normal[2]) / M_PI * 180.0f;

        float glocal_fHeightPlane;
        //Get Distance to Plane
        {
            Vector vtmp_hull = gp_pmove->origin; vtmp_hull[2] = -4096.0f;

            pmtrace_t *trace_hull = gp_Engine->PM_TraceLine(gp_pmove->origin, vtmp_hull, 1, 2, -1);

            glocal_fHeightPlane = gp_pmove->origin.z - trace_hull->endpos.z - (gp_pmove->usehull == 1 ? 18.0f : 36.0f);
        }

        float glocal_fHeight;
        //Get Current Distance to Ground and Plane
        {
            glocal_fHeight = glocal_fHeightGround;

            if(glocal_fGroundAngle >= 0.1f)
            {
                if((glocal_fHeightPlane - glocal_fHeightGround) <= 20.0f)
                    glocal_fHeight = glocal_fHeightPlane;
            }
        }


        // from 101xd

        static int gs_state = 0;
        if(Cvars::sgs_standup->value&&glocal_fHeight<Cvars::sgs_standup->value)
        {
            cmd->buttons |=IN_DUCK;
        }
        if(gs_state == 0 && gp_pmove->flags&FL_ONGROUND)
        {
            cmd->buttons |=IN_DUCK;
            gs_state = 1;
        }
        else if(gs_state == 1)
        {
            if(Cvars::sgs_bhop->value &&
                gp_pmove->usehull==0)
            {
                cmd->buttons|=IN_JUMP;
            }
            cmd->buttons &= ~IN_DUCK;
            gs_state = 0;
        }

        // my shitty sgs

        // if (gp_pmove->flags & FL_ONGROUND)
        //  cmd->buttons |= IN_DUCK;
        // if (((gp_pmove->flags & FL_ONGROUND) && (gp_pmove->bInDuck)) || !(gp_pmove->flags & FL_ONGROUND))
        //  cmd->buttons &= ~IN_DUCK;
    }

    void sgs_on()
    {
        b_sgs = true;
    }
    void sgs_off()
    {
        b_sgs = false;
    }

} // namespace Sgs
