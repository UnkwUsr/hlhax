#include "main.h"
#include "utils/mem/mem.h"
#include "funcs/funcs.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"
#include <dlfcn.h>
#include <cstring>


bool is_loaded = false;


__attribute__((constructor))
void on_load()
{
    printf("\nhlhax loading\n");

    getModulesHandles();
    findSymbols();
    copyOriginals();

    Cmds_Init();
    Cvars_Init();
    Funcs_Init();

    gp_Engine->Con_Printf("hlhax loaded\n");

    is_loaded = true;
}

__attribute__((destructor))
void on_un_load()
{
    gp_Engine->Con_Printf("hlhax unloading\n");

    if(is_loaded) {
        restoreOriginals();

        Cmds_Terminate();
        Cvars_Terminate();
        Funcs_Terminate();
    }

    printf("hlhax unloaded\n");
}

void self_unload()
{
    void* me = dlopen("libhlhack.so", RTLD_LAZY | RTLD_NOLOAD);
    dlclose(me);
    dlclose(me);
}

void getModulesHandles()
{
    handles::hw = dlopen("hw.so", RTLD_LAZY | RTLD_NOLOAD);
    if(!handles::hw) {
        printf("[error] handles::hw is null, aborting\n");
        self_unload();
        // all next code is unreachable
    }

    handles::p_client = (void**)dlsym(handles::hw, "hClientDLL");
    if(!handles::p_client) {
        printf("[error] handles::p_client is null, aborting\n");
        self_unload();
        // all next code is unreachable
    }

    g_hw_addr = getModuleAddr("hw.so");
}

void findSymbols()
{
    gp_Engine = (cl_enginefunc_t*)dlsym(handles::hw,
        "cl_enginefuncs");
    gp_Client = (cl_clientfunc_t*)dlsym(handles::hw, "cl_funcs");

    find_steamclient_funcs();

    gp_Studio = (r_studio_interface_t*)dlsym(*handles::p_client,
        "studio");
    gp_EngStudio = (engine_studio_api_t*)dlsym(handles::hw,
        "engine_studio_api");
    findStudioModelRenderer();

    gp_pmove = *(playermove_t**)dlsym(handles::hw, "pmove");
    gp_host_frametime = (double*)dlsym(handles::hw, "host_frametime");

    /* gp_ClientUserMsgs = (UserMsg*)dlsym(handles::hw, "gClientUserMsgs"); */
    // due to we can't just dlsym "gClientUserMsgs", we use this hack.
    // Grub pointer from function body. This function has interact with wanted pointer.
    gp_ClientUserMsgs = **(UserMsg***)((char*)dlsym(handles::hw, "CL_ShutDownUsrMessages") + 0x5);
}

void copyOriginals()
{
    memcpy(&go_Engine, gp_Engine, sizeof(cl_enginefunc_t));
    memcpy(&go_Client, gp_Client, sizeof(cl_clientfunc_t));

    memcpy(&go_steamclient_funcs, gp_steamclient_funcs,
        sizeof(steamclient_funcs_t));

    memcpy(&go_Studio, gp_Studio, sizeof(r_studio_interface_t));
    memcpy(&go_EngStudio, gp_EngStudio, sizeof(engine_studio_api_t));
    memcpy(&go_StudioModelRenderer, gp_StudioModelRenderer,
        sizeof(StudioModelRenderer_t));
}

void restoreOriginals()
{
    memcpy(gp_Engine, &go_Engine, sizeof(cl_enginefunc_t));
    memcpy(gp_Client, &go_Client, sizeof(cl_clientfunc_t));

    memcpy(gp_steamclient_funcs, &go_steamclient_funcs,
        sizeof(steamclient_funcs_t));

    memcpy(gp_Studio, &go_Studio, sizeof(r_studio_interface_t));
    memcpy(gp_EngStudio, &go_EngStudio, sizeof(engine_studio_api_t));
    memcpy(gp_StudioModelRenderer, &go_StudioModelRenderer,
        sizeof(StudioModelRenderer_t));
}


void find_steamclient_funcs()
{
    typedef void* (*SteamUser_func_t)();
    SteamUser_func_t SteamUser_func = (SteamUser_func_t)dlsym(
        handles::hw, "SteamUser");
    void* SteamUser_ret = SteamUser_func();
    gp_steamclient_funcs = *(steamclient_funcs_t**)SteamUser_ret;

    unprotectAddr(gp_steamclient_funcs);
}

void findStudioModelRenderer()
{
    gp_StudioModelRenderer = *(StudioModelRenderer_t**)dlsym(
        *handles::p_client, "g_StudioRenderer");
    unprotectAddr(gp_StudioModelRenderer);
}

