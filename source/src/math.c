#include "core.h"
#include "../d_math.h"

static Uint32 m_randSeed = 0;

unsigned D_MathPow(unsigned x, unsigned n) {
    unsigned r = x;
    while (--n) {
        r *= r;
    }
    return (r);
}

unsigned D_MathSqrt(unsigned x) {
    unsigned m = 0x40000000;    //=(1<<30)
    unsigned r = 0, nr;
    do {
        nr = m + r;
        r >>= 1;
        if (nr <= x) {
            x -= nr;
            r += m;
        }
        m >>= 2;
    } while (m);
    return (r);
}

void D_SetRandomSeed(Uint32 seed) {
    m_randSeed = seed;
}

/**
    Visual C++의 rand함수 알고리즘 사용.
*/
Int32 D_GetRandom(Int32 min, Int32 max) {
    Int32 random = (Int32)(((m_randSeed = m_randSeed * 214013L + 2531011L) >> 16) & 0x7fff);
/*
    Int32 _max = D_MathMax(min, max);
    Int32 _min = D_MathMin(min, max);

    max = _max;
    min = _min;
*/
    if (min > max) D_MathSwap(min, max);

    ++max;

    if (min == max) {
        return min;
    }

    random = random % (max - min);
    random = random + min;

    return random;
}
