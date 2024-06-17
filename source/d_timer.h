/**
    @file   d_timer.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_TIMER_H_
#define DOROTHY_TIMER_H_

/*
Usage:
    start에서 timeout만큼 경과시킨 후 current가 증가되고, current가 limit이 되면 콜백 함수가 호출된다.
*/

typedef struct D_Timer {
    Uint id;
    Dword start;
    Dword timeout;
    Dword limit;
    Dword current;
} DTimer;

BEGIN_DOROTHY_API
    typedef Int (*D_TimerProc)(DTimer *timer, void *param);

    Dword   D_GetCurrentTime(void);
    DTimer  D_SetTimer(Uint id, Dword timeout, Dword limit);
    void    D_ResetTimer(DTimer *timer);
    Int     D_UpdateTimer(DTimer *timer, Bool loop, D_TimerProc proc, void *param);
END_DOROTHY_API
#endif
