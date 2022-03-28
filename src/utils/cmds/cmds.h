#ifndef CMDS_H
#define CMDS_H

#include "sdk.h"

extern f_malloc_cmd_t f_Cmds_AddMalloc;


#define HAX_CMD_FLAG 4096


#define CREATE_CMD(name, func) \
f_Cmds_AddMalloc(CMD_PREFIX name , func, HAX_CMD_FLAG);

#define CREATE_TGL_CMD(name, func_on, func_off) \
f_Cmds_AddMalloc("+" CMD_PREFIX name , func_on, HAX_CMD_FLAG); \
f_Cmds_AddMalloc("-" CMD_PREFIX name , func_off, HAX_CMD_FLAG);


#endif // CMDS_H
