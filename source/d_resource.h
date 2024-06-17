/**
    @file   d_resource.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_RESOURCE_H_
#define DOROTHY_RESOURCE_H_

typedef struct D_Resource {
    Size size;
    void *data;
    Uint32 offset;
} DResource;

BEGIN_DOROTHY_API
    DResource*  D_LoadResource(const Char *name);
    void        D_FreeResource(DResource *res);
    Bool        D_ReadResource(void *buf, DResource *res, Size size);
END_DOROTHY_API

#endif
