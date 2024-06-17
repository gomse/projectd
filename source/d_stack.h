/**
    @file   d_stack.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_STACK_H_
#define DOROTHY_STACK_H_

typedef struct D_Stack {
    Uint32 count;
    void *ptr;
} DStack;

typedef Bool (*D_StackSearchProc)(void*);

BEGIN_DOROTHY_API
    void    D_PushStack(DStack *stack, void *data);
    void*   D_PopStack(DStack *stack);
    void    D_ClearStack(DStack *stack);
    void    D_SearchStack(DStack *stack, D_StackSearchProc proc);
END_DOROTHY_API

#endif
