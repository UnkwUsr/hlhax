#ifndef HOOK_USERMSG_H
#define HOOK_USERMSG_H

#include "utils/hooks/funcs.h"
#include "globals.h"
#include <cstring>


UserMsg* FindUserMsg(const char* MsgName) {
    UserMsg *Ptr = gp_ClientUserMsgs;

    while(Ptr)
    {
        if (!strcmp(Ptr->szName, MsgName))
            return Ptr;
        Ptr = Ptr->next;
    }

    gp_Engine->Con_Printf("[hlhax] Can't find %s usermsg\n", MsgName);
    return NULL;
}

#define ADD_USERMSG_HOOK(name) \
UserMsg *usermsg_ ## name = FindUserMsg(#name); \
if(usermsg_ ## name != NULL) { \
    orig_ ## name = ( name ## _t)usermsg_ ## name ->pfn; \
    usermsg_ ## name ->pfn = (pfnUserMsgHook) name; \
}


#define REM_USERMSG_HOOK(name) \
UserMsg *usermsg_ ## name = FindUserMsg(#name); \
if(usermsg_ ## name != NULL) \
    usermsg_ ## name ->pfn = orig_ ## name;


#endif // HOOK_USERMSG_H
