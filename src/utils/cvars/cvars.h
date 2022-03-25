#ifndef CVARS_H
#define CVARS_H

void Cvars_Init();
void Cvars_Terminate();


#define HAX_CVAR_FLAG 8192


#define CREATE_CVAR(name, def_value) \
gp_Engine->pfnRegisterVariable(CVAR_PREFIX name , def_value, \
    HAX_CVAR_FLAG)


#endif // CVARS_H
