/**
    @file   d_tileset.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_TILESET_H_
#define DOROTHY_TILESET_H_

#include "d_palette.h"

#define D_TILE_WIDTH        24
#define D_TILE_HEIGHT       24
#define D_TILE_DATA_SIZE    576 //(D_TILE_WIDTH * D_TILE_HEIGHT)

typedef struct D_Tile {
    Index data[D_TILE_DATA_SIZE];
} DTile;

typedef struct D_TileSet {
    DPalette *palette;
    Uint8 nums;
    DTile *tiles;
} DTileSet;

BEGIN_DOROTHY_API
    DTileSet*   D_LoadTileSet(const Char *name);
    void        D_FreeTileSet(DTileSet *tls);
END_DOROTHY_API

#endif
