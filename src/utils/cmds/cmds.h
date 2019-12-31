#ifndef CMDS_H
#define CMDS_H

#include "sdk.h"


void Cmds_Init();
void Cmds_Terminate();

typedef void (*f_malloc_cmd_t) (char *cmd_name, xcommand_t function,
    int flags);
extern f_malloc_cmd_t Cmds_AddMalloc_hooked;


#define HAX_CMD_FLAG 4096


#define CREATE_CMD(name, func) \
Cmds_AddMalloc_hooked(CMD_PREFIX name , func, HAX_CMD_FLAG);

#define CREATE_TGL_CMD(name, func_on, func_off) \
Cmds_AddMalloc_hooked("+" CMD_PREFIX name , func_on, HAX_CMD_FLAG); \
Cmds_AddMalloc_hooked("-" CMD_PREFIX name , func_off, HAX_CMD_FLAG);


void dump_cmds_f();
void remove_cmd_f();


#endif // CMDS_H
