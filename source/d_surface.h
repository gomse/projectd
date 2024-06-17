/**
    @file   d_surface.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_SURFACE_H_
#define DOROTHY_SURFACE_H_

typedef struct D_Surface {
    Uint16 width;
    Uint16 height;
    Pixel *buffer;
} DSurface;

BEGIN_DOROTHY_API
    DSurface*   D_CreateSurface(Uint16 width, Uint16 height);
    void        D_ReleaseSurface(DSurface *surface);

    void        D_ClearSurface(DSurface *surface, Color16 color);
    Bool        D_DrawSurface(DSurface *dest, Int x, Int y, const DSurface *src, const DRect *rect, Byte alpha);
    Bool        D_DrawSurfaceScale(DSurface *dest, Int x, Int y, const DSurface *src, const DRect *rect, Uint32 scale, Byte alpha);
END_DOROTHY_API

#endif
