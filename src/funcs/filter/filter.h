#ifndef FILTER_H
#define FILTER_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Filter {
    void Init();
    void SetHooks();
    void Terminate();

    DECL_HOOK(int, HUD_AddEntity, int type, cl_entity_t *ent,
        const char *modelname)
    DECL_HOOK(int, TeamInfo, const char *pszName, int iSize, void *pbuf)

    bool isValidPlayer(int index);

    bool isTeammate(int index);
} // namespace Filter

#endif // FILTER_H
