#include <cerrno>
#include <cstring>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

// source: linux kernel, tools/virtio/linux/kernel.h
#define PAGE_SIZE getpagesize()
#define PAGE_MASK (~(PAGE_SIZE-1))
#define PAGE_ALIGN(x) ((x + PAGE_SIZE - 1) & PAGE_MASK)

#define PAGE_ALIGN_DOWN(x) (PAGE_ALIGN(x) - PAGE_SIZE)

bool unprotectAddr(void* place) {
    void* p = (void*)PAGE_ALIGN_DOWN((int)place);

    int pgsz = getpagesize();
    int res = mprotect(p, pgsz, PROT_READ | PROT_WRITE);
    if(res == -1) {
        auto er = errno;
        printf("[hlhax] Error unprotecting %p: %s\n", place, strerror(er));

        return false;
    }

    return true;
}
