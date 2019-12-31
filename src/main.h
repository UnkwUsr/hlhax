#include "sdk.h"
#include <inttypes.h>



void getModulesHandles();
uintptr_t g_hw_addr;
namespace handles {
    void* hw;
    void** p_client;
}
void findSymbols();

void copyOriginals();
void restoreOriginals();

void find_steamclient_funcs();
void findStudioModelRenderer();
void findSpeedPtr();


cl_enginefunc_t *gp_Engine;
cl_clientfunc_t *gp_Client;

steamclient_funcs_t* gp_steamclient_funcs;

r_studio_interface_t *gp_Studio;
engine_studio_api_t* gp_EngStudio;
StudioModelRenderer_t* gp_StudioModelRenderer;


cl_enginefunc_t go_Engine;
cl_clientfunc_t go_Client;

steamclient_funcs_t go_steamclient_funcs;

r_studio_interface_t go_Studio;
engine_studio_api_t go_EngStudio;
StudioModelRenderer_t go_StudioModelRenderer;


playermove_t *gp_pmove;
double* gp_host_frametime;
float* gp_speed_val;
