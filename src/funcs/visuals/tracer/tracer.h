#ifndef VISUALS_TRACER_H
#define VISUALS_TRACER_H

#include "sdk.h"
#include "utils/hooks/funcs.h"


namespace Tracer {
    void Init();
    void Terminate();

    DECL_HOOK(int, HUD_AddEntity, int type, cl_entity_t *ent,
        const char *modelname)
    DECL_HOOK(void, Begin, int primitiveCode)
} // namespace Tracer

#endif // VISUALS_TRACER_H
