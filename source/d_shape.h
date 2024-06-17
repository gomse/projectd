/**
    @file   d_shape.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_SHAPE_H_
#define DOROTHY_SHAPE_H_

typedef struct D_Point2 {
    Int32 x, y;
} DPoint2;

typedef struct D_Point3 {
    Int32 x, y, z;
} DPoint3;

typedef struct D_Bounds2 {
    Int32 w, h;
} DBounds2;

typedef struct D_Rect2 {
    Int32 x, y, w, h;
} DRect;

typedef struct D_Circle {
    DPoint2 center;
    Uint32 radius;
} DCircle;

BEGIN_DOROTHY_API
    DRect       D_SetRect(DRect *rect, Int32 x, Int32 y, Int32 w, Int32 h);
    DBounds2    D_SetBounds2(DBounds2 *bounds, Int32 w, Int32 h);

    DPoint2     D_SetPoint2(DPoint2 *point, Int32 x, Int32 y);
    DPoint3     D_SetPoint3(DPoint3 *point, Int32 x, Int32 y, Int32 z);

    DCircle     D_SetCircle(DCircle *circle, DPoint2 center, Uint32 radius);

    Uint32      D_GetDistance2(DPoint2 a, DPoint2 b);
    Bool        D_IsInRect(const DRect *rect, Int32 x, Int32 y);
END_DOROTHY_API

typedef DPoint2 DPoint;

#define D_SetPoint      D_SetPoint2
#define D_GetDistance   D_GetDistance2

#endif
