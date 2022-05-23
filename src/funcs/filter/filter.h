#ifndef FILTER_H
#define FILTER_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


struct player_s {
    bool valid;
    uint distance;
    float view_angle;
    char team_name[MAX_TEAM_NAME];
};

namespace Filter {
    extern player_s players[32];

    void Init();
    void SetHooks();
    void Terminate();

    DECL_HOOK(int, HUD_AddEntity, int type, cl_entity_t *ent,
        const char *modelname)
    DECL_HOOK(int, TeamInfo, const char *pszName, int iSize, void *pbuf)
    DECL_HOOK(void, CL_CreateMove, float frametime, usercmd_t *cmd, int active)

    bool isValidPlayer(int index);

    bool isTeammate(int index);

    int targetRating(int index);
} // namespace Filter

#endif // FILTER_H
