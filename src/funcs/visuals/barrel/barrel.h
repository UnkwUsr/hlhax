#ifndef VISUALS_BARREL_H
#define VISUALS_BARREL_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Barrel {
    void Init();

    DECL_HOOK(int, HUD_AddEntity, int type, cl_entity_t *ent,
        const char *modelname)
} // namespace Barrel

#endif // VISUALS_BARREL_H
