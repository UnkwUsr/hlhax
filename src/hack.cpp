#include "hack.h"
#include "globals.h"
#include "funcs/funcs.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"



void Hack_Init()
{
    Cmds_Init();
    Cvars_Init();

    Funcs_Init();

    CREATE_CMD("dump_aliases", dump_aliases_f)


    gp_Engine->Con_Printf("Hack loaded FINE\n");
}
void Hack_Terminate()
{
    Cmds_Terminate();
    Cvars_Terminate();

    Funcs_Terminate();

    gp_Engine->Con_Printf("Hack UNLOADED FINE!!11\n");
}

void dump_aliases_f()
{
    cmdalias_t *cmd_aliases = gp_Engine->pfnGetAliasList();
    for(cmdalias_t *i = cmd_aliases; i; i = i->next)
    {
        gp_Engine->Con_Printf("alias \"%s\" \"%s\"", i->name,
            i->value);
        // "\n" not needed because i->value has this already
    }
}
