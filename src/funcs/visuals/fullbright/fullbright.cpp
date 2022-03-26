#include "funcs/visuals/fullbright/fullbright.h"
#include "globals.h"
#include "utils/cmds/cmds.h"

namespace Fullbright {
    void set_brightness_f();

    void Init() {
        CREATE_CMD("set_brightness", set_brightness_f);
    }

    void Terminate() {
        gp_Engine->pfnSetFilterMode(false);
    }

    void set_brightness_f() {
        if(gp_Engine->Cmd_Argc() < 2) {
            gp_Engine->Con_Printf("Usage: " CMD_PREFIX
                                  "set_brightness <0.0 - 1.0>\nPass without "
                                  "arguments to disable\n");
            gp_Engine->pfnSetFilterMode(false);
            return;
        }
        float level = atof(gp_Engine->Cmd_Argv(1));
        gp_Engine->pfnSetFilterMode(true);
        gp_Engine->pfnSetFilterBrightness(level);
    }
} // namespace Fullbright
