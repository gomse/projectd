#include "core.h"
#include "../d_shape.h"
#include "../d_math.h"

DRect D_SetRect(DRect *rect, Int32 x, Int32 y, Int32 w, Int32 h) {
    DRect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    if (rect) *rect = r;
    return r;
}

DBounds2 D_SetBounds2(DBounds2 *bounds, Int32 w, Int32 h) {
    DBounds2 b;
    b.w = w;
    b.h = h;
    if (bounds) *bounds = b;
    return b;
}

DPoint2 D_SetPoint2(DPoint2 *point, Int32 x, Int32 y) {
    DPoint2 p;
    p.x = x;
    p.y = y;
    if (point) *point = p;
    return p;
}

DPoint3 D_SetPoint3(DPoint3 *point, Int32 x, Int32 y, Int32 z) {
    DPoint3 p;
    p.x = x;
    p.y = y;
    p.x = z;
    if (point) *point = p;
    return p;
}

DCircle D_SetCircle(DCircle *circle, DPoint2 center, Uint32 radius) {
    DCircle c;
    c.center = center;
    c.radius = radius;
    if (circle) *circle = c;
    return c;
}

/**
    점 사이의 거리를 계산한다.
*/
Uint32 D_GetDistance2(DPoint2 a, DPoint2 b) {
    return (Uint32)D_MathSqrt(D_MathPow(D_MathAbs(a.x-b.x), 2) + D_MathPow(D_MathAbs(a.y-b.y), 2));
}

/**
    x,y가 Rect내에 존재하는지 검사.
*/
Bool D_IsInRect(const DRect *rect, Int32 x, Int32 y) {
    D_ASSERT(rect != NULL);

    if (rect->x <= x && rect->y <= y) {
        if ((rect->x + rect->w) > x && (rect->y + rect->h) > y) {
            return TRUE;
        }
    }

    return FALSE;
}

/**
    충돌 검사.
*/
Bool D_IntersectRect(DRect *r, const DRect *a, const DRect *b) {
    Int32 ax0 = a->x;
    Int32 ay0 = a->y;
    Int32 ax1 = a->x + a->w - 1;
    Int32 ay1 = a->y + a->h - 1;

    Int32 bx0 = b->x;
    Int32 by0 = b->y;
    Int32 bx1 = b->x + b->w - 1;
    Int32 by1 = b->y + b->h - 1;

    if (r) {
        r->x = 0; r->y = 0;
        r->w = 0; r->h = 0;
    }

    if (/*(bx0 < ax0) && */(bx1 < ax0)) return FALSE;
    if ((bx0 > ax1) /*&& (bx1 > ax1)*/) return FALSE;
    if (/*(by0 < ay0) && */(by1 < ay0)) return FALSE;
    if ((by0 > ay1) /*&& (by1 > ay1)*/) return FALSE;

    if (r) {
        Int32 rx0 = D_MathMax(ax0, bx0);
        Int32 rx1 = D_MathMin(ax1, bx1);
        Int32 ry0 = D_MathMax(ay0, by0);
        Int32 ry1 = D_MathMin(ay1, by1);

        r->x = rx0;
        r->y = ry0;
        r->w = (rx1 - rx0) + 1;
        r->h = (ry1 - ry0) + 1;
    }

    return TRUE;
}
