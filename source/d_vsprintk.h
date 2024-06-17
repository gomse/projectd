/**
    @file   d_vsprintk.h
    @author 박세환 (gommse@gmail.com)
    @brief  구글 어딘가에서 주워온 임베디드용 vsprintf 함수.
*/
#ifndef DOROTHY_VSPRINTK_H_
#define DOROTHY_VSPRINTK_H_

#include <stdarg.h>

BEGIN_DOROTHY_API
    int D_Vsprintk(char *buffer, const char *format, va_list argptr);
END_DOROTHY_API

#endif
