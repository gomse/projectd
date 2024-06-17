/**
    @file   d_image.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_IMAGE_H_
#define DOROTHY_IMAGE_H_

#include "d_resource.h"

typedef struct D_Image {
    Byte    type;
    Uint16  width, height;
    Int16   x, y;
    Index   *buffer;
    Byte    *alpha;
} DImage;

#define D_ALPHA_MIN 0
#define D_ALPHA_MAX 32
#define D_ALPHA_COMPOSITE(r, s, a, d)   {   \
    Byte v = D_ALPHA_MAX-(a);   \
    (r) = ((((((s)&0xF81F)*(a))+(((d)&0xF81F)*v))>>5)&0xF81F) | \
    ((((((s)&0x07E0)*(a))+(((d)&0x07E0)*v))>>5)&0x07E0);    \
    }

BEGIN_DOROTHY_API
    DImage* D_LoadImage(const Char *name);
    Bool    D_ReadImage(DImage *img, DResource *res);
    void    D_ClearImage(DImage *img);
    void    D_FreeImage(DImage *img);

    Bool    D_DrawImage(DSurface *dest, Int x, Int y, const DImage *img, Bool hflip);
    Bool    D_DrawImageScale(DSurface *dest, Int x, Int y, const DImage *img, Uint32 scale);
END_DOROTHY_API

#endif
