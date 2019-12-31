#ifndef VISUALS_WIREMODELS_H
#define VISUALS_WIREMODELS_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace WireModels {
    void Init();

    DECL_HOOK(int, StudioDrawPlayer, int flags,
        entity_state_t *pplayer)
}

#endif // VISUALS_WIREMODELS_H
