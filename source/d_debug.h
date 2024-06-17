/**
    @file   d_debug.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_DEBUG_H_
#define DOROTHY_DEBUG_H_

#ifdef D_DEBUG
//# define D_ASSERT(x)  ((x)? ((void)0) : D_Assert(#x, __FILE__, __LINE__))
#   define D_ASSERT(x)  { if (!(x)) D_Assert(#x, __FILE__, __LINE__); }
#else
#   define D_ASSERT(x)  ((void)0)
#endif

BEGIN_DOROTHY_API
    void    D_Assert(const Char *msg, const Char *file, Uint line);
END_DOROTHY_API

#endif
