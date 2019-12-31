#include "globals.h"
#include "utils/cmds/cmds.h"
#include <dlfcn.h>



f_malloc_cmd_t Cmds_AddMalloc_hooked;


void Cmds_Init()
{
    Cmds_AddMalloc_hooked = (f_malloc_cmd_t)dlsym(handles::hw,
                                        "Cmd_AddMallocCommand");


    CREATE_CMD("dump_cmds", dump_cmds_f)
}

void Cmds_Terminate()
{
    typedef void (*f_rmCmdsByFlag_t) (int flags);
    f_rmCmdsByFlag_t f_rmCmdsByFlag = (f_rmCmdsByFlag_t)dlsym(
                            handles::hw, "Cmd_RemoveMallocedCmds");

    f_rmCmdsByFlag(HAX_CMD_FLAG);
}


void dump_cmds_f()
{
    cmd_function_t* first_cmd = (cmd_function_s*)gp_Engine->
                                        GetFirstCmdFunctionHandle();
    for(cmd_function_t *i = first_cmd; i; i = i->next)
    {
        gp_Engine->Con_Printf("%s\n", i->name);
    }
}
