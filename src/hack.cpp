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
    CREATE_CMD("set_filter_color", set_filter_color_f)


    gp_Engine->Con_Printf("Hack loaded FINE\n");
}
void Hack_Terminate()
{
    Cmds_Terminate();
    Cvars_Terminate();

    Funcs_Terminate();

    gp_Engine->Con_Printf("Hack UNLOADED FINE!!11\n");
}


void set_filter_color_f() // fulbright
{
    if(gp_Engine->Cmd_Argc() < 4)
    {
        gp_Engine->Con_Printf("Using: " CMD_PREFIX"set_filter_color \
            <r> <g> <b>\n");
        gp_Engine->pfnSetFilterMode(false);
        return;
    }
    float r = atof(gp_Engine->Cmd_Argv(1));
    float g = atof(gp_Engine->Cmd_Argv(2));
    float b = atof(gp_Engine->Cmd_Argv(3));
    gp_Engine->pfnSetFilterColor(r, g, b);

    gp_Engine->pfnSetFilterMode(true);
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
