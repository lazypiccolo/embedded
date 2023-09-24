#ifndef __UTIL__H
#define __UTIL__H

#include "types.h"

void delay(uint tick) {
    while (tick--) {
        for (uchar i = 0; i < 250; ++i);
    }
}

#endif
