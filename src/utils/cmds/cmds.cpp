#include "utils/cmds/cmds.h"
#include "globals.h"
#include <dlfcn.h>

void Cmds_Clear() {
    typedef void (*f_rmCmdsByFlag_t)(int flags);
    f_rmCmdsByFlag_t f_rmCmdsByFlag =
        (f_rmCmdsByFlag_t)dlsym(handles::hw, "Cmd_RemoveMallocedCmds");
    if(!f_rmCmdsByFlag) {
        printf("[hlhax] Can't find Cmd_RemoveMallocedCmds func\n");
        return;
    }

    f_rmCmdsByFlag(HAX_CMD_FLAG);
}
