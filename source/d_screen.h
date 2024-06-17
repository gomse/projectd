/**
    @file   d_screen.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_SCREEN_H_
#define DOROTHY_SCREEN_H_

#include "d_surface.h"

typedef struct D_Screen {
    MC_GrpFrameBuffer buffer;
    DRect rect;
} DScreen;

BEGIN_DOROTHY_API
    DScreen*    D_InitScreen(Uint32 width, Uint32 height);
    void        D_ReleaseScreen(DScreen *screen);

    void        D_ResetScreen(void);
    void        D_ClearScreen(Color16 color);
    void        D_FlushScreen(void);

    Word*       D_GetScreenBuffer(void);
    DSurface*   D_GetScreenSurface(void);

    Bool    D_CheckScreenSurface(DSurface **surface);
END_DOROTHY_API

#endif
