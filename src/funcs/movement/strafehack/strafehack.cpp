#include "funcs/movement/strafehack/strafehack.h"
#include "globals.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"

namespace Cvars {
    cvar_t* strafe_side;
}

namespace Strafehack {
    bool b_strafehack;

    DEF_HOOK(CL_CreateMove);

    void Init() {
        ADD_HOOK(CL_CreateMove, gp_Client);

        CREATE_TGL_CMD("strafehack", strafehack_on, strafehack_off);

        Cvars::strafe_side = CREATE_CVAR("strafe_side", "320");
    }

    void fastrun(usercmd_t* cmd);

    void CL_CreateMove(float frametime, usercmd_t* cmd, int active) {
        CALL_ORIG(CL_CreateMove, frametime, cmd, active);

        if(!b_strafehack)
            return;

        if(gp_pmove->flags & FL_ONGROUND) {
            fastrun(cmd);
        } else {
            // by malanris for cs 1.6, modified by me

            float flxyspeed = gp_pmove->velocity.Length2D();
            // with zero speed something goes wrong and game fall into infinity
            // loop
            if(flxyspeed == 0) {
                cmd->forwardmove = gp_pmove->maxspeed;
                return;
            }

            cmd->forwardmove = 23.3 / (flxyspeed / gp_pmove->maxspeed);

            float sidespeed = 0;
            static bool Strafing;
            if(Strafing) {
                sidespeed = -Cvars::strafe_side->value;
                Strafing = false;
            } else {
                sidespeed = Cvars::strafe_side->value;
                Strafing = true;
            }
            cmd->sidemove = sidespeed;
        }
    }

    // actually just strafes on ground
    void fastrun(usercmd_t* cmd) {
        // TODO: have to understand what's going on and drop hardcoded
        // constants

        // hl1
        float aa = 500;
        float bb = 500;

        // cs 1.6
        // float aa = 89.6;
        // float bb = 126.6;

        static bool _FastRun = false;
        if((cmd->buttons & IN_FORWARD && cmd->buttons & IN_MOVELEFT) ||
           (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVERIGHT)) {
            if(_FastRun) {
                _FastRun = false;
                cmd->sidemove -= aa;
                cmd->forwardmove -= aa;
            } else {
                _FastRun = true;
                cmd->sidemove += aa;
                cmd->forwardmove += aa;
            }
        } else if((cmd->buttons & IN_FORWARD &&
                   cmd->buttons & IN_MOVERIGHT) ||
                  (cmd->buttons & IN_BACK && cmd->buttons & IN_MOVELEFT)) {
            if(_FastRun) {
                _FastRun = false;
                cmd->sidemove -= aa;
                cmd->forwardmove += aa;
            } else {
                _FastRun = true;
                cmd->sidemove += aa;
                cmd->forwardmove -= aa;
            }
        } else if(cmd->buttons & IN_FORWARD || cmd->buttons & IN_BACK) {
            if(_FastRun) {
                _FastRun = false;
                cmd->sidemove -= bb;
            } else {
                _FastRun = true;
                cmd->sidemove += bb;
            }
        } else if(cmd->buttons & IN_MOVELEFT ||
                  cmd->buttons & IN_MOVERIGHT) {
            if(_FastRun) {
                _FastRun = false;
                cmd->forwardmove -= bb;
            } else {
                _FastRun = true;
                cmd->forwardmove += bb;
            }
        }
    }

    void strafehack_on() {
        b_strafehack = true;
    }
    void strafehack_off() {
        b_strafehack = false;
    }

} // namespace Strafehack
