#include "core.h"
#include "graphics.h"
#include "../d_vsprintk.h"

DGraphics *g_graphics = NULL;

/**
    그래픽 장치를 초기화한다.
    어플리케이션 진입시 최초에 호출되어야 한다.

    @param  width   화면 가로 사이즈.
    @param  height  화면 세로 사이즈.
*/
Bool D_InitGraphics(Uint32 width, Uint32 height) {
    g_graphics = D_Alloc(sizeof(DGraphics));

    MC_grpGetDisplayInfo(0, &g_graphics->displayInfo);
    g_graphics->screen = D_InitScreen(width, height);

    if (g_graphics->displayInfo.m_width < (int)width ||
        g_graphics->displayInfo.m_height < (int)height) {
        return FALSE;
    }

    D_InitFont();

    return TRUE;
}

void D_ReleaseGraphics(void) {
    if (g_graphics) {
        D_ReleaseScreen(g_graphics->screen);
        D_Free(g_graphics);
    }

    g_graphics = NULL;
}

void D_DrawString(Int32 x, Int32 y, Color16 color, const Char *fmt, ...) {
    MC_GrpContext context;
    Char buf[255] = {0};
    Byte r, g, b;
    va_list v;

    va_start(v, fmt);
    D_Vsprintk(buf, fmt, v);
    va_end(v);

    r = D_GET_RED16(color);
    g = D_GET_GREEN16(color);
    b = D_GET_BLUE16(color);

    MC_grpInitContext(&context);
    MC_grpSetContext(&context, MC_GRP_CONTEXT_FG_PIXEL_IDX, (void*)MC_grpGetPixelFromRGB(r, g, b));
    MC_grpDrawString(g_graphics->screen->buffer, x, y, buf, -1, &context);
}
