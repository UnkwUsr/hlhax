#include <cerrno>
#include <cstring>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

void* getAlignedAddr(void* addr_not_aligned) {
    int pgsz = getpagesize();

    for(int i = 0; 10000; i++) {
        int now_addr = i * pgsz;
        int next_addr = now_addr + pgsz;
        if((void*)next_addr > addr_not_aligned)
            return (void*)(now_addr);
    }

    return NULL;
}

bool unprotectAddr(void* place) {
    void* p = getAlignedAddr(place);
    if(!p)
        return false;

    int pgsz = getpagesize();
    int res = mprotect(p, pgsz, PROT_READ | PROT_WRITE);
    if(res == -1) {
        auto er = errno;
        printf("[hlhax] Error unprotecting %p: %s\n", place, strerror(er));

        return false;
    }

    return true;
}
