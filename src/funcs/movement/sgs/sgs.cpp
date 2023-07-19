#include "funcs/movement/sgs/sgs.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"



namespace Cvars {
    cvar_t* sgs_standup;
    cvar_t* sgs_noslowdown;
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
        Cvars::sgs_noslowdown = CREATE_CVAR("sgs_noslowdown", "1");
        Cvars::sgs_bhop = CREATE_CVAR("sgs_bhop", "0");
    }


    void CL_CreateMove(float frametime, usercmd_t *cmd, int active)
    {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);

        // noslowdown related
        static bool should_restore_speed = false;
        static float orig_speed = -1;

        if(!b_sgs) {
            // noslowdown related
            if(should_restore_speed) {
                *gp_speed_val = orig_speed;
                should_restore_speed = false;
            }

            return;
        }


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

        float horizontal_velocity = gp_pmove->velocity.Length2D();

        if(Cvars::sgs_noslowdown->value != 0 && gp_pmove->flags & FL_ONGROUND) {
            // allows surf on enevens when speed is more than 1000
            // TODO: cvar: noslowdown_min_speed_to_surf
            // TODO: refactor. I did this when was asleep. The original idea
            // was to allow surf only when speed is enough. Otherwise apply
            // noslowdown on onevens (= do not fly on them)
            if(horizontal_velocity <= 1000 && glocal_fGroundAngle != 0) {
                if(!should_restore_speed) {
                    should_restore_speed = true;
                    orig_speed = *gp_speed_val;
                }
                *gp_speed_val = 0;
            }
        } else if(should_restore_speed) {
            *gp_speed_val = orig_speed;
            should_restore_speed = false;
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
