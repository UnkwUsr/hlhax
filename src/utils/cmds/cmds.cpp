#include "globals.h"
#include "utils/cmds/cmds.h"
#include <dlfcn.h>

f_malloc_cmd_t f_Cmds_AddMalloc;

void Cmds_Init()
{
    f_Cmds_AddMalloc = (f_malloc_cmd_t)dlsym(handles::hw,
                                        "Cmd_AddMallocCommand");
}

void Cmds_Terminate()
{
    typedef void (*f_rmCmdsByFlag_t) (int flags);
    f_rmCmdsByFlag_t f_rmCmdsByFlag = (f_rmCmdsByFlag_t)dlsym(
                            handles::hw, "Cmd_RemoveMallocedCmds");

    f_rmCmdsByFlag(HAX_CMD_FLAG);
}
