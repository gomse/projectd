#include "core.h"
#include "../d_animation.h"
#include "../d_resource.h"


DAnimation* D_LoadAnimation(const Char *name) {
    DResource *res = D_LoadResource(name);
    DAnimation *ani = D_Calloc(sizeof(DAnimation));

    D_ReadResource(&ani->frameNums, res, 1);
    D_ReadResource(&ani->loop, res, 1);

    ani->delays = D_Alloc(ani->frameNums * 2);

    D_ReadResource(ani->delays, res, ani->frameNums*2);
    D_FreeResource(res);

    return ani;
}

void D_FreeAnimation(DAnimation *ani) {
    if (ani) {
        if (ani->delays) {
            D_Free(ani->delays);
            ani->delays = NULL;
        }

        D_Free(ani);
    }
}

void D_RewindAnimation(DAnimation *ani) {
    D_ASSERT(ani != NULL);

    ani->timer = 0;
    ani->curFrame = 0;
}

Bool D_PlayAnimation(DAnimation *ani, Dword elapse) {
    D_ASSERT(ani != NULL);

    ani->timer += elapse;

    if (ani->timer >= ani->delays[ani->curFrame]) {
        if (++ani->curFrame >= ani->frameNums) {
            ani->curFrame = ani->frameNums - 1;

            if (ani->loop) {
                D_RewindAnimation(ani);
            }

            return FALSE;
        }

        ani->timer = 0;
    }

    return TRUE;
}
