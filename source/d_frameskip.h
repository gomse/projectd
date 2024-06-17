/**
    @file   d_frameskip.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_FRAMESKIP_H_
#define DOROTHY_FRAMESKIP_H_

typedef struct D_FrameSkip {
    Int32 timer;
    Int32 secPerFrame;
} DFrameSkip;

BEGIN_DOROTHY_API
    DFrameSkip  D_SetFrameSkip(Uint fps);
    Bool        D_IsFrameSkip(DFrameSkip *fs, Dword elapse);
END_DOROTHY_API

#endif
