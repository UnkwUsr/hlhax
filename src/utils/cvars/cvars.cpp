#include "utils/cvars/cvars.h"
#include "globals.h"
#include <dlfcn.h>
#include <string.h>

// TODO: write better function for removing cvars
void Cvars_RemoveByFlag(int flag)
{
    cvar_t** p_cvar_vars = (cvar_t**)dlsym(handles::hw, "cvar_vars");

    typedef void (*Z_Free_t) (void* ptr);
    Z_Free_t Z_Free_hooked = (Z_Free_t)dlsym(handles::hw, "Z_Free");



    cvar_s *v2; // esi

    cvar_t *v0 = 0; // edi
    cvar_t *ptr = *p_cvar_vars; // ebx
    if ( !(*p_cvar_vars) )
        return;
    while ( 1 )
    {
        v2 = ptr->next;
        if ( ptr->flags & flag )
            break;
        ptr->next = v0;
        v0 = ptr;
        if ( !v2 )
            goto LABEL_7;
LABEL_4:
        ptr = v2;
    }
    Z_Free_hooked(ptr->string);
    // Z_Free_hooked(ptr);
    if ( v2 )
        goto LABEL_4;
LABEL_7:
    *p_cvar_vars = 0;
    if ( v0 )
    {
        cvar_t *v3 = v0; // eax
        cvar_s *v4 = 0; // ecx
        while ( 1 )
        {
            cvar_s *v5 = v3->next;
            v3->next = v4;
            if ( !v5 )
                break;
            v4 = v3;
            v3 = v5;
        }
        *p_cvar_vars = v3;
    }
}

void Cvars_Clear() {
    Cvars_RemoveByFlag(HAX_CVAR_FLAG);
}
