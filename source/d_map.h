/**
    @file   d_map.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_MAP_H_
#define DOROTHY_MAP_H_

#include "d_surface.h"
#include "d_tileset.h"

#define D_MAP_VIEW_WIDTH    10
#define D_MAP_VIEW_HEIGHT   13

typedef struct D_MapLayer {
    Byte *data;
} DMapLayer;

typedef struct D_MapInfo {
    Byte        reserved;
    Uint16      width;
    Uint16      height;
    Uint8       layerNums;

    Byte        *floor;
    DMapLayer   *layers;
    Byte        *attrib;
} DMapInfo;

typedef struct D_Map {
    DTileSet    *tileSet;
    DMapInfo *mapInfo;
} DMap;

BEGIN_DOROTHY_API
    DMap*   D_LoadMap(const Char *mapInfo, const Char *tlsName);
    void    D_FreeMap(DMap *map);

    void    D_DrawFloor(DSurface *dest, const DMap *map, Int sx, Int sy);
END_DOROTHY_API

#endif
