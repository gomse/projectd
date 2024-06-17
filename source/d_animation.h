/**
    @file   d_animation.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_ANIMATION_H_
#define DOROTHY_ANIMATION_H_

typedef struct D_Animation {
    Uint8   frameNums;  ///< 프레임 갯수.
    Bool    loop;       ///< 반복 여부.
    Word    *delays;    ///< 프레임들의 딜레이.
    Uint8   curFrame;   ///< 현재 프레임.
    Dword   timer;      ///< 타이머에 사용될 변수.
} DAnimation;

BEGIN_DOROTHY_API
    DAnimation* D_LoadAnimation(const Char *name);
    void        D_FreeAnimation(DAnimation *ani);
    void        D_RewindAnimation(DAnimation *ani);
    Bool        D_PlayAnimation(DAnimation *ani, Dword elapse);
END_DOROTHY_API

#endif
