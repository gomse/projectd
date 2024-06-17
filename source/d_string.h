/**
    @file   d_string.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_STRING_H_
#define DOROTHY_STRING_H_

#define D_Printk        MC_knlPrintk
#define D_Sprintk       MC_knlSprintk

BEGIN_DOROTHY_API
    Char*   D_ItoA(Int n, Char* num);
    Int     D_AtoI(const Char *str);

    Dword   D_StringToHash(const Char *str);

    Uint    D_CopyString(Char *buf, const Char *src);
    Uint    D_StringLength(const Char *str);
END_DOROTHY_API

#endif
