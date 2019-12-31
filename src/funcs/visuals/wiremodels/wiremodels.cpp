#include "funcs/visuals/wiremodels/wiremodels.h"
#include "globals.h"
#include "utils/cvars/cvars.h"
#include <GL/gl.h>



namespace Cvars
{
    cvar_t* wiremodels;
    cvar_t* wiremodels_line_width;
}

namespace WireModels {
    DEF_HOOK(StudioDrawPlayer)

    void Init()
    {
        ADD_HOOK(StudioDrawPlayer, gp_Studio)

        Cvars::wiremodels = CREATE_CVAR("wiremodels", "0");
        Cvars::wiremodels_line_width = CREATE_CVAR(
            "wiremodels_line_width", "1");
    }

    int StudioDrawPlayer(int flags, struct entity_state_s *pplayer)
    {
        if(Cvars::wiremodels->value == 0)
            return CALL_ORIG(StudioDrawPlayer, flags, pplayer);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(Cvars::wiremodels_line_width->value);

        int res = CALL_ORIG(StudioDrawPlayer, flags, pplayer);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        return res;
    }
} // namespace WireModels
