/**
    @file   d_graphics.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_GRAPHICS_H_
#define DOROTHY_GRAPHICS_H_

#define D_COLORKEY16    0xF81F
#define D_RGB16(r,g,b)  (((r << 8) & 0xf800) | ((g << 3) & 0x07e0) | ((b >> 3) & 0x1f))

BEGIN_DOROTHY_API
    Bool    D_InitGraphics(Uint32 width, Uint32 height);
    void    D_ReleaseGraphics(void);
    void    D_DrawString(Int32 x, Int32 y, Color16 color, const Char *fmt, ...);
END_DOROTHY_API

#endif
