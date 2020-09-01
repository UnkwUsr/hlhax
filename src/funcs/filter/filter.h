#ifndef FILTER_H
#define FILTER_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Filter {
    void Init();

    DECL_HOOK(int, HUD_AddEntity, int type, cl_entity_t *ent,
        const char *modelname)

    bool isValidPlayer(int index);
} // namespace Filter

#endif // FILTER_H
