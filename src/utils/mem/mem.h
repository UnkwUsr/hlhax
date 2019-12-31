#include <inttypes.h>


uintptr_t getModuleAddr(const char * module_name);
void* getAlignedAddr(void* addr_not_aligned);
void unprotectAddr(void* place);

