#include "funcs/visuals/xqz/xqz.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "funcs/utils.h"
#include "funcs/filter/filter.h"
#include <cstring>



namespace Cvars
{
    cvar_t* xqz;
}

namespace Xqz {
    DEF_HOOK(StudioRenderModel)

    DEF_HOOK(glColor4f)


    enum {NONE, BEHIND, IN_FRONT, TEST};
    int state_relative_wall;

    void Init()
    {
        ADD_HOOK(StudioRenderModel, gp_StudioModelRenderer)

        ADD_GL_HOOK(glColor4f)

        Cvars::xqz = CREATE_CVAR("xqz", "1");
    }

    void Terminate()
    {
        REM_GL_HOOK(glColor4f)
    }


    void StudioRenderModel(void* this_ptr)
    {
        if(Cvars::xqz->value == 0) {
            return CALL_ORIG(StudioRenderModel, this_ptr);
        }

        cl_entity_t* ent = gp_EngStudio->GetCurrentEntity();

        // draw local player and hands with weapon
        if(ent->index == gp_Engine->GetLocalPlayer()->index)
            return CALL_ORIG(StudioRenderModel, this_ptr);

        if(!Filter::isValidPlayer(ent->index)) {
            return CALL_ORIG(StudioRenderModel, this_ptr);
        }

        // TODO: bug: next drawn entities hide players

        glDisable(GL_TEXTURE_2D);

        state_relative_wall = BEHIND;
        glDisable(GL_DEPTH_TEST);
        gp_StudioModelRenderer->StudioRenderFinal(this_ptr);

        state_relative_wall = IN_FRONT;
        glEnable(GL_DEPTH_TEST);
        gp_StudioModelRenderer->StudioRenderFinal(this_ptr);

        state_relative_wall = NONE;
        glEnable(GL_TEXTURE_2D);
    }

    void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        if(state_relative_wall == NONE) {
            return CALL_ORIG(glColor4f, red, green, blue, alpha);
        }

        if(state_relative_wall == BEHIND) {
            red = 1;
            green = 0;
            blue = 0;
        }
        else if(state_relative_wall == IN_FRONT) {
            red = 0;
            green = 1;
            blue = 0;
        }
        else if(state_relative_wall == TEST) {
            red = 0;
            green = 0;
            blue = 1;
        }

        CALL_ORIG(glColor4f, red, green, blue, alpha);
    }

} // namespace Xqz
