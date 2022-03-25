#ifndef HOOK_GL_H
#define HOOK_GL_H

#include "utils/hooks/funcs.h"
#include "globals.h"
#include <GL/gl.h>
#include <dlfcn.h>



#define ADD_GL_HOOK(name) \
void** q ## name ##_ptr = (void**)dlsym(handles::hw, "q" #name); \
orig_ ## name = ( name ## _t)(*q ## name ## _ptr); \
*q ## name ## _ptr = (void*) name;


#define REM_GL_HOOK(name) \
void** q ## name ##_ptr = (void**)dlsym(handles::hw, "q" #name); \
*q ## name ##_ptr = (void*)orig_ ## name;


#endif // HOOK_GL_H
