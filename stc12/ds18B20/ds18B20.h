#include "../../common/stc12x56xx.h"
#include "../../common/util.h"
#include "../io/io.h"

#define TX18B20PORT P1
#define TX18B20BIT 0
#define TX18B20 COMPOSE_IO_REG(TX18B20PORT, TX18B20BIT)

inline void ds1820_write0() {
    TX18B20 = 1;
    STRONG_PULL(TX18B20PORT, TX18B20BIT);
    fast_delay(1);
    TX18B20 = 0;
    fast_delay(100);
    HIGH_IMPEDANCE(TX18B20PORT, TX18B20BIT);
}

inline void ds1820_write1() {
    TX18B20 = 1;
    STRONG_PULL(TX18B20PORT, TX18B20BIT);
    fast_delay(1);
    TX18B20 = 0;
    fast_delay(1);
    HIGH_IMPEDANCE(TX18B20PORT, TX18B20BIT);
    fast_delay(100);
}

inline char ds1820_read_bit() {
    char level;
    TX18B20 = 1;
    STRONG_PULL(TX18B20PORT, TX18B20BIT);
    fast_delay(1);
    TX18B20 = 0;
    fast_delay(2);
    HIGH_IMPEDANCE(TX18B20PORT, TX18B20BIT);
    fast_delay(10);
    level = TX18B20;
    fast_delay(100);
    return level;
}

char ds1820_read_byte() {
    char data = 0;
    for (uchar i = 0; i < 8; i++) {
        data |= ds1820_read_bit() << i;
    }
    return data;
}

void ds1820_write_byte(char data) {
    for (uchar i = 0; i < 8; i++) {
        if (data & 0x01) {
            ds1820_write1();
        } else {
            ds1820_write0();
        }
        data >>= 1;
    }
}

void ds1820_reset() {
    STRONG_PULL(TX18B20PORT, TX18B20BIT);
    TX18B20 = 1;
    fast_delay(900);
    TX18B20 = 0;
    fast_delay(900);
    HIGH_IMPEDANCE(TX18B20PORT, TX18B20BIT);
    fast_delay(900);
}

uint ds1820_read_temperature_sync() {
    ds1820_reset();
    ds1820_write_byte(0xcc);
    ds1820_write_byte(0x44);

    // if use parasite mode, the following line should be uncommented.
//    STRONG_PULL(TX18B20PORT, TX18B20BIT);
//    TX18B20 = 1;
//    delay(20000);
//    HIGH_IMPEDANCE(TX18B20PORT, TX18B20BIT);

    while (!ds1820_read_bit());
    ds1820_reset();
    ds1820_write_byte(0xcc);
    ds1820_write_byte(0xbe);
    uchar lsb = ds1820_read_byte();
    uchar msb = ds1820_read_byte();
    return lsb + ((uint) msb << 8);
}

void ds1820_config(uchar th, uchar tl, uchar bitnum) {
    ds1820_reset();
    ds1820_write_byte(0xcc);
    ds1820_write_byte(0x4e);
    ds1820_write_byte(th);
    ds1820_write_byte(tl);
    uchar offset = (bitnum - 9) << 5;
    ds1820_write_byte(offset);
    ds1820_write_byte(0x48);
}


