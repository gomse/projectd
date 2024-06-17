#include "core.h"
#include "../d_scripter.h"
#include "../d_resource.h"

#define D_SCRIPT_KEY_IF     0x0f006966
#define D_SCRIPT_KEY_END    0x6f656e64
#define D_SCRIPT_KEY_RUN    0x6972756e
#define D_SCRIPT_KEY_SET    0x62736574
#define D_SCRIPT_KEY_GOTO   0x136f75a4
#define D_SCRIPT_KEY_LABEL  0x3a00003a
#define D_SCRIPT_KEY_PRINT  0x716abfca

static Char *D_SCRIPT_NIL = "nil";


/**
    문자열이 서로 같은지 비교한다.
*/
static Bool IsEqual(const Char *a, const Char *b) {
    if (a == b) return TRUE;
    else if (a && b) {
        Uint length = D_StringLength(a);
        if (length == D_StringLength(b)) {
            Uint i;
            for (i = 0; i < length; i++) {
                if (*a++ != *b++) return FALSE;
            }

            return TRUE;
        }
    }

    return FALSE;
}

/**
    문자열이 숫자로만 이루어져 있는지 검사한다.
*
static Bool IsDigit(const Char *str) {
    Uint length = D_StringLength(str);
    Uint i;

    for (i = 0; i < length; i++) {
        char c = str[i];

        if (c >= '0' && c <= '9') continue;
        if (c == '-') continue;

        return FALSE;
    }

    return TRUE;
}*/

static DScript* LoadScript(const Char *name) {
    DScript *script = D_Alloc(sizeof(DScript));
    DResource *res = D_LoadResource(name);
    Byte reserved = 0;
    Uint i, j;

    D_ReadResource(&reserved, res, 1);
    D_ReadResource(&script->lineNums, res, 2);

    script->lines = D_Alloc(sizeof(DScriptLine) * script->lineNums);

    for (i = 0; i < script->lineNums; i++) {
        DScriptLine *line = &script->lines[i];

        D_ReadResource(&line->key, res, 4);
        D_ReadResource(&line->argNums, res, 1);

        line->args = NULL;

        if (line->argNums > 0) {
            line->args = D_Alloc(sizeof(DScriptArg) * line->argNums);

            for (j = 0; j < line->argNums; j++) {
                DScriptArg *arg = &line->args[j];

                D_ReadResource(&arg->length, res, 1);

                arg->data = D_Alloc(arg->length + 1);
                D_ReadResource(arg->data, res, arg->length);
                arg->data[arg->length] = 0;
            }
        }
    }

    D_FreeResource(res);

    return script;
}

static void FreeScript(DScript *script) {
    Uint i, j;

    for (i = 0; i < script->lineNums; i++) {
        DScriptLine *line = &script->lines[i];

        for (j = 0; j < line->argNums; j++) {
            D_Free(line->args[j].data);
        }

        if (line->args) {
            D_Free(line->args);
        }
    }

    D_Free(script->lines);
    D_Free(script);
}

static void FreeBTreeVar(Dword key, void *data, void *param) {
    if (data) {
        D_Free(data);
    }
    data = NULL;
}

static void SetLine(DScripter *scripter, Uint line) {
    scripter->curLine = (Uint16)line;
    scripter->nextLine = (Uint16)line;
}

static D_ScriptProc FindScriptProc(DScripter *scripter, Dword key) {
    return (D_ScriptProc)D_FindBTree(&scripter->procedures, key);
}

void D_AddScriptProc(DScripter *scripter, const Char *name, D_ScriptProc proc) {
    D_InsertBTree(&scripter->procedures, D_StringToHash(name), (void*)proc);
}

DScripter* D_InitScripter(const Char *script) {
    DScripter *scripter = D_Alloc(sizeof(DScripter));

    scripter->script = LoadScript(script);
    scripter->curLine = 0;
    scripter->nextLine = 0;
    scripter->procedures = NULL;
    scripter->variables = NULL;

    return scripter;
}

void D_FreeScripter(DScripter *scripter) {
    D_ClearBTree(&scripter->variables, FreeBTreeVar);
    D_ClearBTree(&scripter->procedures, NULL);

    if (scripter->script) {
        FreeScript(scripter->script);
    }

    D_Free(scripter);
}

void D_DelScriptVar(DScripter *scripter, Dword key) {
    Char *data = D_DeleteBTree(&scripter->variables, key);
    if (data) {
        D_Free(data);
    }
}

void D_SetScriptVar(DScripter *scripter, Dword key, const Char *data) {
    if (IsEqual(data, "nil")) {
        D_DelScriptVar(scripter, key);
    }
    else {
        Char *tmp = NULL;
        Char *var = D_Alloc(D_StringLength(data)+1);

        D_CopyString(var, data);
        tmp = D_InsertBTree(&scripter->variables, key, var);

        if (tmp) D_Free(tmp);
    }
}

Char* D_GetScriptVar(DScripter *scripter, Dword key) {
    Char *data = D_FindBTree(&scripter->variables, key);
    if (data) {
        return data;
    }

    return D_SCRIPT_NIL;
}

Bool D_SetScript(DScripter *scripter, const Char *name) {
    DScript *script = LoadScript(name);
    if (script) {
        if (scripter->script) {
            FreeScript(scripter->script);
        }

        SetLine(scripter, 0);
        scripter->script = script;

        return TRUE;
    }

    return FALSE;
}

static Bool DoRun(DScripter *scripter, DScriptLine *line) {
    return D_SetScript(scripter, line->args[0].data);
}

static Bool DoGoto(DScripter *scripter, DScriptLine *line) {
    Uint i;
    for (i = 0; i < scripter->script->lineNums; i++) {
        DScriptLine *search = &scripter->script->lines[i];

        if (search->key == D_SCRIPT_KEY_LABEL) {
            if (IsEqual(line->args[0].data, search->args[0].data)) {
                SetLine(scripter, i);
                return TRUE;
            }
        }
    }

    return FALSE;
}

static Bool DoSet(DScripter *scripter, DScriptLine *line) {
    Dword hash  = D_StringToHash(line->args[0].data);
    Char *op    = line->args[1].data;
    Char *v2    = line->args[2].data;

    if (IsEqual(op, "=")) {
        D_SetScriptVar(scripter, hash, v2);
    }
    else {
        Char *v1 = D_GetScriptVar(scripter, hash);
        Int a = D_AtoI(v1);
        Int b = D_AtoI(v2);
        Int v = a;

        if (IsEqual(op, "-=")) a -= b;
        else if (IsEqual(op, "+=")) a += b;
        else if (IsEqual(op, "*=")) a *= b;
        else if (IsEqual(op, "/=")) {
            if (b == 0) b = 1;
            a /= b;
        }

        if (a != v) {
            Char buf[255];
            D_SetScriptVar(scripter, hash, D_ItoA(a, buf));
        }
    }

    return TRUE;
}

static Bool DoIf(DScripter *scripter, DScriptLine *line) {
    Char*   v1      = line->args[0].data;
    Char*   v2      = line->args[2].data;
    Char*   op      = line->args[1].data;
    Char*   _v1     = D_GetScriptVar(scripter, D_StringToHash(v1));
    Char*   _v2     = D_GetScriptVar(scripter, D_StringToHash(v2));
    Bool    isTrue  = FALSE;

    if (_v1 != D_SCRIPT_NIL) v1 = _v1;
    if (_v2 != D_SCRIPT_NIL) v2 = _v2;

    if (IsEqual(op, "=")) {
        if (IsEqual(v1, v2)) {
            isTrue = TRUE;
        }
    }
    else if (IsEqual(op, "!=")) {
        if (!IsEqual(v1, v2)) {
            isTrue = TRUE;
        }
    }
    else {
        Int a = D_AtoI(v1);
        Int b = D_AtoI(v2);

        if (a < b && IsEqual(op, "<")) isTrue = TRUE;
        else if (a > b && IsEqual(op, ">")) isTrue = TRUE;
        else if (a <= b && IsEqual(op, "<=")) isTrue = TRUE;
        else if (a >= b && IsEqual(op, ">=")) isTrue = TRUE;
    }

    if (!isTrue) {
        Uint i, depth=1;
        for (i = scripter->nextLine; i < scripter->script->lineNums; i++) {
            Dword key = scripter->script->lines[i].key;
            if (key == D_SCRIPT_KEY_IF) {
                ++depth;
            }
            else if (key == D_SCRIPT_KEY_END) {
                if (IsEqual(scripter->script->lines[i].args[0].data, "if")) {
                    if (--depth <= 0) {
                        SetLine(scripter, i + 1);
                        break;
                    }
                }
            }
        }
    }

    return TRUE;
}

/**
    print함수의 인자를 파싱한다.
*/
static Char* ParsePrint(DScripter *scripter, DScriptLine *line, Char *buf) {
    Char *str = line->args[0].data;
    Uint i, j = 0, count = 1;

    for (i = 0; i < line->args[0].length; i++) {
        char ch = str[i];
        if (ch == '%') {
            Char *val = D_GetScriptVar(scripter, D_StringToHash(line->args[count++].data));
            Uint len = D_StringLength(val);
            memcpy(&buf[j], val, len);
            j += len;
        }
        else if (ch == '\\') {
            buf[j++] = '\n';
        }
        else {
            buf[j++] = str[i];
        }
    }

    return buf;
}

static Bool DoPrint(DScripter *scripter, DScriptLine *line) {
    Char buffer[255] = {0};
    D_Printk("%s", ParsePrint(scripter, line, buffer));

    return TRUE;
}

Bool D_StepByScript(DScripter *scripter) {
    DScript *script = scripter->script;
    DScriptLine *line;

    if (scripter->nextLine >= scripter->script->lineNums) {
        return FALSE;
    }

    line = &script->lines[scripter->nextLine];

    if (line->key == D_SCRIPT_KEY_IF) {
        ++scripter->nextLine;
        return DoIf(scripter, line);
    }
    else if (line->key == D_SCRIPT_KEY_SET) {
        ++scripter->nextLine;
        return DoSet(scripter, line);
    }
    else if (line->key == D_SCRIPT_KEY_GOTO) {
        return DoGoto(scripter, line);
    }
    else if (line->key == D_SCRIPT_KEY_RUN) {
        return DoRun(scripter, line);
    }
    else if (line->key == D_SCRIPT_KEY_PRINT) {
        ++scripter->nextLine;
        return DoPrint(scripter, line);
    }
    else {
        D_ScriptProc proc = FindScriptProc(scripter, line->key);
        ++scripter->nextLine;
        if (proc) {
            return proc(scripter, line);
        }
    }

    return TRUE;
}
