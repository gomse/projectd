/**
    @file   d_scripter.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_SCRIPTER_H_
#define DOROTHY_SCRIPTER_H_

#include "d_btree.h"

typedef struct _ScriptArg {
    Uint8   length;
    Char    *data;
} DScriptArg;

typedef struct _ScriptLine {
    Dword       key;
    Uint8       argNums;
    DScriptArg  *args;
} DScriptLine;

typedef struct _Script {
    Uint16      lineNums;
    DScriptLine *lines;
} DScript;

typedef struct _Scripter {
    DScript *script;
    Uint16  curLine;
    Uint16  nextLine;
    BTree   procedures;
    BTree   variables;
} DScripter;

BEGIN_DOROTHY_API
    typedef Bool (*D_ScriptProc)(DScripter*, DScriptLine*);

    DScripter*  D_InitScripter(const Char *script);
    void        D_FreeScripter(DScripter *scripter);

    void    D_AddScriptProc(DScripter *scripter, const Char *name, D_ScriptProc proc);
    void    D_SetScriptVar(DScripter *scripter, Dword key, const Char *data);
    Char*   D_GetScriptVar(DScripter *scripter, Dword key);
    Bool    D_SetScript(DScripter *scripter, const Char *name);
    Bool    D_StepByScript(DScripter *scripter);
END_DOROTHY_API

#endif
