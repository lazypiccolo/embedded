#ifndef __MATH__H
#define __MATH__H

#define __SDCC_FLOAT_LIB
#include <float.h>

#define MSB_SET(x) ((x >> (8*sizeof(x)-1)) & 1)

unsigned long long _divulonglong(unsigned long long x, unsigned long long y) {
    unsigned long long reste = 0L;
    unsigned char count = 64;
    char c;

    do {
        // reste: x <- 0;
        c = MSB_SET(x);
        x <<= 1;
        reste <<= 1;
        if (c)
            reste |= 1L;

        if (reste >= y) {
            reste -= y;
            // x <- (result = 1)
            x |= 1L;
        }
    } while (--count);
    return x;
}


#endif
