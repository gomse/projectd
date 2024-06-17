/**
    @file   d_font.h
*/
#ifndef DOROTHY_FONT_H_
#define DOROTHY_FONT_H_

BEGIN_DOROTHY_API
    void    D_DrawFont(Int x, Int y, Color16 color, const Char *fmt, ...);

    Uint32  D_GetFontWidth(const Char *str);
    Uint32  D_GetFontHeight(void);
END_DOROTHY_API

#endif
