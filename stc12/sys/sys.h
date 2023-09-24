#ifndef __SYS__H
#define __SYS__H

#include "../../common/stc12x56xx.h"

inline void enable_sys_interrupt(char status) {
    EA = status;
}

#endif
