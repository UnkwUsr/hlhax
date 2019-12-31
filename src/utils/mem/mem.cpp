#include "utils/mem/mem.h"

#include <unistd.h>
#include <fstream>

#include <cstring>
#include <cerrno>
#include <sys/mman.h>



uintptr_t getModuleAddr(const char * module_name)
{
    uintptr_t result = 0;
    char cmd[256];

    snprintf(cmd, 256, "grep /%s /proc/%i/maps | head -n 1 | cut -d \
        - -f1", module_name, getpid());
    FILE* maps = popen(cmd, "r");
    if(maps)
        fscanf(maps, "%018x", &result);
    pclose(maps);
    return result;
}

void unprotectAddr(void* place)
{
    int pgsz = getpagesize();
    void* p = getAlignedAddr(place);
    int res = mprotect(p, pgsz, PROT_READ | PROT_WRITE);
    if(res == -1)
    {
        auto er = errno;
        printf("Error unprotecting %p: %s\n", place, strerror(er));
    }
    }

void* getAlignedAddr(void* addr_not_aligned)
{
    int pgsz = getpagesize();

    for(int i = 0; 10000; i++)
    {
        int now_addr = i * pgsz;
        int next_addr = now_addr + pgsz;
        if((void*)next_addr > addr_not_aligned)
            return (void*)(now_addr);
    }

    return NULL;
}

