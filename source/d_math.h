/**
    @file   d_math.h
    @author 박세환 (gommse@gmail.com)
*/
#ifndef DOROTHY_MATH_H_
#define DOROTHY_MATH_H_

#define D_MathAbs(n)    (((n)<0)? -(n):(n))
#define D_MathMin(a,b)  (((a)<(b))? (a):(b))
#define D_MathMax(a,b)  (((a)<(b))? (b):(a))
#define D_MathSwap(a,b) ((a)^=(b)^=(a)^=(b))

BEGIN_DOROTHY_API
    unsigned D_MathPow(unsigned x, unsigned n);
    unsigned D_MathSqrt(unsigned x);

    void    D_SetRandomSeed(Uint32 seed);
    Int32   D_GetRandom(Int32 min, Int32 max);
END_DOROTHY_API

#endif
