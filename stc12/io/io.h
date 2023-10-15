#ifndef __IO__H
#define __IO__H

#include "../../common/stc12x56xx.h"

// macro expand parameter first
// use inner macro to use the real value and avoid concat the raw macro

#define _COMPOSE_IO_REG(PORT, n) PORT ## _ ## n
#define COMPOSE_IO_REG(PORT, n) _COMPOSE_IO_REG(PORT, n)

#define _COMPOSE_MODE_REG(PORT, n) PORT##M##n
#define COMPOSE_MODE_REG(PORT, n) _COMPOSE_MODE_REG(PORT,n)

#define BIDIRECTIONAL(PORT, BIT) do{ COMPOSE_MODE_REG(PORT,0) &=~(0x01<<BIT); COMPOSE_MODE_REG(PORT,1) &=~(0x01<<BIT);}while(0)
#define STRONG_PULL(PORT, BIT) do{ COMPOSE_MODE_REG(PORT,0) &=~(0x01<<BIT); COMPOSE_MODE_REG(PORT,1) |=(0x01<<BIT);}while(0)
#define HIGH_IMPEDANCE(PORT, BIT) do{ COMPOSE_MODE_REG(PORT,0) |=(0x01<<BIT); COMPOSE_MODE_REG(PORT,1) &=~(0x01<<BIT);}while(0)
#define OPEN_DRAIN(PORT, BIT) do{ COMPOSE_MODE_REG(PORT,0) =|(0x01<<BIT); COMPOSE_MODE_REG(PORT,1) |=(0x01<<BIT);}while(0)

#endif



