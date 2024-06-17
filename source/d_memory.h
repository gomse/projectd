/**
    @file   d_memory.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_MEMORY_H_
#define DOROTHY_MEMORY_H_

BEGIN_DOROTHY_API
    Bool    D_InitMemory(void);

    void*   D_Alloc(Size size);
    void*   D_Calloc(Size size);
    void    D_Free(void *ptr);

    void    D_CopyMemory(void *dest, const void *src, Size size);
    void    D_SetMemory(void *ptr, Byte val, Size size);

#   define  D_ZeroMemory(p, n)  D_SetMemory((p), 0, (n))
END_DOROTHY_API

#endif
