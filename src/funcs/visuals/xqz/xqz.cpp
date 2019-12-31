#include "funcs/visuals/xqz/xqz.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include "utils/shit/shit.h"



namespace Cvars
{
    cvar_t* xqz;
}

namespace Xqz {
    DEF_HOOK(StudioRenderModel)

    DEF_HOOK(glVertex3f)


    enum {NONE, BEHIND, IN_FRONT, TEST};
    int state_relative_wall;

    void Init()
    {
        ADD_HOOK(StudioRenderModel, gp_StudioModelRenderer)

        ADD_GL_HOOK(glVertex3f)

        Cvars::xqz = CREATE_CVAR("xqz", "1");
    }

    void Terminate()
    {
        REM_GL_HOOK(glVertex3f)
    }


    void StudioRenderModel(void* this_ptr)
    {
        if(Cvars::xqz->value == 0)
        {
            CALL_ORIG(StudioRenderModel, this_ptr);
            return;
        }

        cl_entity_t* ent = gp_EngStudio->GetCurrentEntity();
        if(!ent->player)
        {
            CALL_ORIG(StudioRenderModel, this_ptr);
            return;
        }

        if(!isAlive(ent->curstate))
            return;


        // TODO: bug: when the older-drawn objects hide the player
        // !! asdfvsd, если так (и без glDisable(depth test)),
        // ентити не перекрывают игрока, но тогда не работает chams
        // glDepthRange(0, 0.5);

        glDisable(GL_TEXTURE_2D);


        state_relative_wall = IN_FRONT;
        glDepthFunc(GL_LESS);
        gp_StudioModelRenderer->StudioRenderFinal(this_ptr);

        state_relative_wall = BEHIND;
        glDepthFunc(GL_GREATER);
        gp_StudioModelRenderer->StudioRenderFinal(this_ptr);


        // !! asdfvsd
        // glDepthRange(0, 1);

        glEnable(GL_TEXTURE_2D);
        state_relative_wall = NONE;
        glDepthFunc(GL_LESS);
    }

    void glVertex3f(GLfloat x, GLfloat y, GLfloat z)
    {
        if(state_relative_wall == NONE)
        {
            CALL_ORIG(glVertex3f, x, y, z);
            return;
        }

        if(state_relative_wall == BEHIND)
            glColor3f(255, 0, 0);
        else if(state_relative_wall == IN_FRONT)
            glColor3f(0, 255, 0);
        else if(state_relative_wall == TEST)
            glColor3f(0, 0, 255);

        CALL_ORIG(glVertex3f, x, y, z);
    }

} // namespace Xqz
