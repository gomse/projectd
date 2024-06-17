/**
    @file   d_palette.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_PALETTE_H_
#define DOROTHY_PALETTE_H_

#include "d_resource.h"

typedef struct D_Palette {
    Byte    lastIdx;
    Color16 *colors;
} DPalette;

BEGIN_DOROTHY_API
    DPalette*   D_CreatePalette(Byte lastIdx);
    DPalette*   D_LoadPalette(const Char *name);
    DPalette*   D_ReadPalette(DResource *res);
    void        D_FreePalette(DPalette *pal);

    DPalette*   D_CopyPalette(const DPalette *src);
    DPalette*   D_MakeGrayPalette(const DPalette *src);

    DPalette*   D_SetPalette(DPalette *pal);
    DPalette*   D_GetPalette(void);
END_DOROTHY_API

#endif
