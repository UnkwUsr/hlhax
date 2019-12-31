#ifndef CVARS_H
#define CVARS_H


void Cvars_Init();
void Cvars_Terminate();

void Cvars_RemoveByFlag(int flag);


#define HAX_CVAR_FLAG 8192


#define CREATE_CVAR(name, def_value) \
gp_Engine->pfnRegisterVariable(CVAR_PREFIX name , def_value, \
    HAX_CVAR_FLAG)


void dump_cvars_f();
void remove_cvar_f();


#endif
