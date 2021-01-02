#ifndef HOOK_SYMFUNCS_H
#define HOOK_SYMFUNCS_H

#include "utils/hooks/funcs.h"
#include "globals.h"
#include <dlfcn.h>



#define ADD_SYM_HOOK(name) \
void** name ##_ptr = (void**)dlsym(handles::hw, #name); \
orig_ ## name = ( name ## _t)(*name ## _ptr); \
*name ## _ptr = (void*) name;


#define REM_SYM_HOOK(name) \
void** name ##_ptr = (void**)dlsym(handles::hw, #name); \
*name ##_ptr = (void*)orig_ ## name;


#endif // HOOK_SYMFUNCS_H
