#ifndef VISUALS_XQZ_H
#define VISUALS_XQZ_H

#include "sdk.h"
#include "utils/hooks/funcs.h"
#include "utils/hooks/gl.h"


namespace Xqz {
    void Init();
    void Terminate();

    DECL_HOOK(void, StudioRenderModel, void* this_ptr)

    DECL_HOOK(void, glColor4f, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
} // namespace Xqz

#endif
