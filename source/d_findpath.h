/**
    @file   d_findpath.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_FINDPATH_H_
#define DOROTHY_FINDPATH_H_

#define D_FINDPATH_LIMIT_STEPS  100

typedef struct D_FindPath {
    Uint steps;
    DPoint2 *pos;
} DFindPath;

BEGIN_DOROTHY_API
    typedef Bool (*D_FindPathProc)(DPoint2, void*);

    void        D_SetFindPathProc(D_FindPathProc proc);
    DFindPath*  D_ExcuteFindPath(DPoint2 start, DPoint2 goal, void *param);
    void        D_ClearFindPath(DFindPath *findPath);
END_DOROTHY_API

#endif
