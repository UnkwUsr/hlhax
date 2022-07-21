#ifndef GLOBALS_H
#define GLOBALS_H

#include "sdk.h"


// p - pointer
// o - original

namespace handles {
    extern void* hw;
    extern void** p_client;
}

extern cl_enginefunc_t *gp_Engine;
extern cl_clientfunc_t *gp_Client;

extern steamclient_funcs_t* gp_steamclient_funcs;

extern r_studio_interface_t *gp_Studio;
extern engine_studio_api_t* gp_EngStudio;
extern StudioModelRenderer_t* gp_StudioModelRenderer;
extern triangleapi_t go_TriApi;


extern cl_enginefunc_t go_Engine;
extern cl_clientfunc_t go_Client;

extern steamclient_funcs_t go_steamclient_funcs;

extern r_studio_interface_t go_Studio;
extern engine_studio_api_t go_EngStudio;
extern StudioModelRenderer_t go_StudioModelRenderer;


extern playermove_t *gp_pmove;
extern double* gp_host_frametime;
extern UserMsg* gp_ClientUserMsgs;
extern float* gp_speed_val;



#endif // GLOBALS_H
