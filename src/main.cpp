#include "funcs/funcs.h"
#include "globals.h"
#include "symbols.h"
#include "utils/cmds/cmds.h"
#include "utils/cvars/cvars.h"
#include <dlfcn.h>

void Cvars_Clear();
void Cmds_Clear();

bool is_loaded = false;

void self_unload() {
    void* me = dlopen("libhlhack.so", RTLD_LAZY | RTLD_NOLOAD);
    dlclose(me);
    dlclose(me);
}

__attribute__((constructor)) //
void on_load()
{
    printf("\nhlhax loading\n");

    if(!findSymbols()) {
        self_unload();
        return;
    }
    copyOriginals();

    Funcs_Init();

    // file hlhax.cfg should be near hl.sh or in mod dir (cstrike, valve, etc.)
    gp_Engine->pfnClientCmd("exec hlhax.cfg");

    gp_Engine->Con_Printf("hlhax loaded\n");

    is_loaded = true;
}

__attribute__((destructor)) //
void on_unload()
{
    if(is_loaded) {
        gp_Engine->Con_Printf("hlhax unloading\n");

        restoreOriginals();

        Cmds_Clear();
        Cvars_Clear();
        Funcs_Terminate();
    }

    printf("hlhax unloaded\n");
}
