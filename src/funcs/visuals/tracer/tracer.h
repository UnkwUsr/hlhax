#ifndef VISUALS_TRACER_H
#define VISUALS_TRACER_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Tracer {
    void Init();

    DECL_HOOK(int, HUD_AddEntity, int type, cl_entity_t *ent,
        const char *modelname)

    void DrawTraceLine(cl_entity_t *from, cl_entity_t *to);
} // namespace Tracer

#endif // VISUALS_TRACER_H
