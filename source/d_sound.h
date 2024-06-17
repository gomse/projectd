/**
@file   d_sound.h
*/
#ifndef DOROTHY_SOUND_H_
#define DOROTHY_SOUND_H_

BEGIN_DOROTHY_API
    void    D_InitSound(void);
    void    D_ReleaseSound(void);
    void    D_SetSoundVolume(Int level);
    void    D_PlayMusic(const Char *name);
    void    D_PlaySound(const Char *name);
    void    D_StopMusic(void);
    void    D_StopSound(void);
END_DOROTHY_API

#endif
