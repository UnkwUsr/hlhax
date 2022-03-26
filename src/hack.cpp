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


    gp_Engine->Con_Printf("Hack loaded FINE\n");
}
void Hack_Terminate()
{
    Cmds_Terminate();
    Cvars_Terminate();

    Funcs_Terminate();

    gp_Engine->Con_Printf("Hack UNLOADED FINE!!11\n");
}
