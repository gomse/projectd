/**
    @file   d_sprite.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_SPRITE_H_
#define DOROTHY_SPRITE_H_

#include "d_image.h"

typedef DImage  DSpriteFrame;
typedef struct D_Sprite {
    Uint8           frameNums;
    DSpriteFrame    *frames;
} DSprite;

BEGIN_DOROTHY_API
    DSprite*    D_LoadSprite(const Char *name);
    DSprite*    D_ReadSprite(DResource *res);
    void        D_FreeSprite(DSprite *spr);

    Bool        D_DrawSprite(DSurface *dest, Int x, Int y, const DSprite *spr, Byte frame, Bool hflip);
    Bool        D_DrawSpriteScale(DSurface *dest, Int x, Int y, const DSprite *spr, Byte frame, Uint32 scale);
END_DOROTHY_API

#endif
