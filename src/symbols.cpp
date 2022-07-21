#include "dlfcn.h"
#include "globals.h"
#include "utils/mem/mem.h"
#include <cstring>

namespace handles {
    void* hw;
    void** p_client;
}

cl_enginefunc_t* gp_Engine = NULL;
cl_clientfunc_t* gp_Client = NULL;
steamclient_funcs_t* gp_steamclient_funcs = NULL;
r_studio_interface_t* gp_Studio = NULL;
engine_studio_api_t* gp_EngStudio = NULL;
StudioModelRenderer_t* gp_StudioModelRenderer = NULL;

cl_enginefunc_t go_Engine;
cl_clientfunc_t go_Client;
steamclient_funcs_t go_steamclient_funcs;
r_studio_interface_t go_Studio;
engine_studio_api_t go_EngStudio;
StudioModelRenderer_t go_StudioModelRenderer;
triangleapi_t go_TriApi;

playermove_t* gp_pmove = NULL;
double* gp_host_frametime = NULL;
UserMsg* gp_ClientUserMsgs = NULL;
float* gp_speed_val = NULL;

f_malloc_cmd_t f_Cmds_AddMalloc = NULL;

bool getModulesHandles() {
    handles::hw = dlopen("hw.so", RTLD_LAZY | RTLD_NOLOAD);
    if(!handles::hw) {
        printf("[hlhax] Can't open hw.so\n");
        return false;
    }

    handles::p_client = (void**)dlsym(handles::hw, "hClientDLL");
    if(!handles::p_client) {
        printf("[hlhax] Can't find client library pointer\n");
        return false;
    }

    return true;
}

void findCmdsAddMallocCommandFunc() {
    f_Cmds_AddMalloc =
        (f_malloc_cmd_t)dlsym(handles::hw, "Cmd_AddMallocCommand");
}

void findSteamclientFuncs() {
    typedef void* (*SteamUser_func_t)();
    SteamUser_func_t SteamUser_func =
        (SteamUser_func_t)dlsym(handles::hw, "SteamUser");
    if(!SteamUser_func) {
        printf("[hlhax] Can't find SteamUser func\n");
        return;
    }

    void* SteamUser_ret = SteamUser_func();
    if(!SteamUser_ret) {
        printf("[hlhax] SteamUser func returned NULL\n");
        return;
    }
    gp_steamclient_funcs = *(steamclient_funcs_t**)SteamUser_ret;

    unprotectAddr(gp_steamclient_funcs);
}

void findClientUserMsgs() {
    void* shutdownusrmessages = dlsym(handles::hw, "CL_ShutDownUsrMessages");
    if(!shutdownusrmessages) {
        printf("[hlhax] Can't find ShutDownUsrMessages func\n");
        return;
    }

    // this function have interact with wanted pointer, so take it from
    // function body.
    gp_ClientUserMsgs = **(UserMsg***)((char*)shutdownusrmessages + 0x5);
}

void findStudioModelRenderer() {
    gp_StudioModelRenderer =
        *(StudioModelRenderer_t**)dlsym(*handles::p_client, "g_StudioRenderer");

    unprotectAddr(gp_StudioModelRenderer);
}


// speedhack method 'wavspeed'
void findSpeedPtr()
{
    void* host_speeds = host_speeds = dlsym(handles::hw, "Host_Speeds");
    if(!host_speeds) {
        printf("[hlhax] Can't find Host_Speeds func\n");
        return;
    }

    // this function have interact with wanted pointer, so take it from
    // function body.
    gp_speed_val = *(float**)((char*)host_speeds + 0x13);
    unprotectAddr(gp_speed_val);
}

bool checkLoadedSymbols() {
    if(!gp_Engine || !gp_Client || !gp_steamclient_funcs || !gp_Studio ||
       !gp_EngStudio || !gp_StudioModelRenderer || !gp_pmove ||
       !gp_host_frametime || !gp_ClientUserMsgs || !f_Cmds_AddMalloc ||
       !gp_speed_val) {
        printf("[hlhax] Some symbols not loaded\n");
        return false;
    }
    return true;
}

bool findSymbols() {
    if(!getModulesHandles())
        return false;

    // hw symbols
    gp_Engine = (cl_enginefunc_t*)dlsym(handles::hw, "cl_enginefuncs");
    gp_Client = (cl_clientfunc_t*)dlsym(handles::hw, "cl_funcs");
    gp_pmove = *(playermove_t**)dlsym(handles::hw, "pmove");
    gp_host_frametime = (double*)dlsym(handles::hw, "host_frametime");
    findSteamclientFuncs();
    findCmdsAddMallocCommandFunc();
    findClientUserMsgs();

    // client symbols
    gp_Studio = (r_studio_interface_t*)dlsym(*handles::p_client, "studio");
    gp_EngStudio =
        (engine_studio_api_t*)dlsym(handles::hw, "engine_studio_api");
    findStudioModelRenderer();
    findSpeedPtr();

    if(!checkLoadedSymbols())
        return false;

    return true;
}

void copyOriginals() {
    memcpy(&go_Engine, gp_Engine, sizeof(cl_enginefunc_t));
    memcpy(&go_Client, gp_Client, sizeof(cl_clientfunc_t));

    memcpy(&go_Studio, gp_Studio, sizeof(r_studio_interface_t));
    memcpy(&go_EngStudio, gp_EngStudio, sizeof(engine_studio_api_t));
    memcpy(&go_TriApi, gp_Engine->pTriAPI, sizeof(triangleapi_t));
    memcpy(&go_StudioModelRenderer, gp_StudioModelRenderer,
           sizeof(StudioModelRenderer_t));

    memcpy(&go_steamclient_funcs, gp_steamclient_funcs,
           sizeof(steamclient_funcs_t));
}

void restoreOriginals() {
    memcpy(gp_Engine, &go_Engine, sizeof(cl_enginefunc_t));
    memcpy(gp_Client, &go_Client, sizeof(cl_clientfunc_t));

    memcpy(gp_Studio, &go_Studio, sizeof(r_studio_interface_t));
    memcpy(gp_EngStudio, &go_EngStudio, sizeof(engine_studio_api_t));
    memcpy(gp_Engine->pTriAPI, &go_TriApi, sizeof(triangleapi_t));
    memcpy(gp_StudioModelRenderer, &go_StudioModelRenderer,
           sizeof(StudioModelRenderer_t));

    memcpy(gp_steamclient_funcs, &go_steamclient_funcs,
           sizeof(steamclient_funcs_t));
}
