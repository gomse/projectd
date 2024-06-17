#include "core.h"
#include "../d_memory.h"

#ifdef _SHOW_

#include <MXUserMemMgr.h>

#define D_MEMORY_BUFFER_SIZE    512000  ///< 500KB
//#define D_MEMORY_BUFFER_SIZE  1048576 ///< 1MB
//#define D_MEMORY_BUFFER_SIZE  1572864 ///< 1.5MB
//#define D_MEMORY_BUFFER_SIZE  1887436 ///< 1.8MB
//#define D_MEMORY_BUFFER_SIZE  2097152 ///< 2MB

static MC_UserMemInterface *m_umi = NULL;
static Byte m_buffer[D_MEMORY_BUFFER_SIZE] = {0};

Bool D_InitMemory(void) {
//  MC_knlGetFreeMemory();

    m_umi = MC_knlGetDLLInterface("MXUserMemInterf", -1, -1, NULL, NULL);
    if (m_umi == NULL) {
        return FALSE;
    }

    m_umi->memInit(m_buffer, D_MEMORY_BUFFER_SIZE);

    return TRUE;
}

void* D_Alloc(Size size) {
    return m_umi->memAlloc(m_buffer, size);
}

void* D_Calloc(Size size) {
    Byte *ptr = D_Alloc(size);
    D_SetMemory(ptr, 0, size);
    return ptr;
}

void D_Free(void *ptr) {
    m_umi->memFree(m_buffer, ptr);
}

void D_CopyMemory(void *dest, const void *src, Size size) {
    memcpy(dest, src, size);
}

void D_SetMemory(void *ptr, Byte val, Size size) {
    memset(ptr, val, size);
}

#endif
