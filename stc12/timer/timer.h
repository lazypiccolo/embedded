#ifndef __TIMER__H
#define __TIMER__H

#include "../../common/stc12x56xx.h"
#include "../../common/types.h"
#include "../sys/sys.h"

#define SYS_CLOCK 32000000L
uchar TH00, TL00, TH10, TL10;


inline void set_running_t0(char running) {
    TR0 = running; //timer0 start running if running = 1;
}

inline void enable_t0_interrupt(char status) {
    ET0 = status;
}

// timer = sys_clock / 2^13
inline void init_t0_mode0() {
    AUXR |= 0x80; // timer0 clock source = sys_clock
    TMOD |= 0x00; // mode 0
    //WAKE_CLKO |= 0x01; // enable timer0 clock output(P1.0)
}

// time range: 1us-24ms for 32M sys_clock
inline void init_t0_mode1(unsigned long long clock_num) {
    clock_num -= 20; // compensation for interrupt and timer load
    if (clock_num > 65536L) {
        AUXR &= ~0x80; // timer0 clock source = sys_clock/12
        clock_num /= 12;
    } else {
        AUXR |= 0x80; // timer0 clock source = sys_clock
    }
    TH0 = TH00 = ~((clock_num >> 8) & 0xff);
    TL0 = TL00 = ~(clock_num & 0xff);
    TMOD &= ~0x03;
    TMOD |= 0x01; // mode 1

    set_running_t0(1);
    enable_t0_interrupt(1);
    enable_sys_interrupt(1);
}

// time range: 30ns-8us for 32M sys_clock(1-256 sys_clock)
inline void init_t0_mode2(uchar tick) {
    AUXR |= 0x80; // timer1 clock source = sys_clock
    TH0 = TL0 = 256 - tick;
    TMOD &= ~0x03;
    TMOD |= 0x02; // mode 2, autoload TL1 from TH1 when timer1 overflow
    set_running_t0(1);
    //enable_t0_interrupt(1);
    enable_sys_interrupt(1);
}

// time range: 30ns-24ms for 32M sys_clock
inline void init_t0(unsigned long long time_ns) {
    unsigned long long clock_num = (unsigned long long) (SYS_CLOCK / 1000000 * time_ns / 1000);
    if (clock_num < 255) {
        init_t0_mode2(clock_num);
    } else {
        init_t0_mode1(clock_num);
    }
    WAKE_CLKO |= 0x01; // enable timer0 clock output(P1.0)
}


void t0_interrupt()

__interrupt 1 __using 0 {
// when using mode2, comment the following 2 lines;
if (TMOD&0x03!=0x02){
TH0 = TH00;
TL0 = TL00;
}
}


inline void set_running_t1(char running) {
    TR1 = running; //timer1 start running if running = 1;
}

inline void enable_t1_interrupt(char status) {
    ET1 = status;
}

// time range: 1us-24ms for 32M sys_clock(32-786000 sys_clock)
inline void init_t1_mode1(unsigned long long clock_num) {
    clock_num -= 20; // compensation for interrupt and timer load
    if (clock_num > 65536L) {
        AUXR &= ~0x40; // timer1 clock source = sys_clock/12
        clock_num /= 12;
    } else {
        AUXR |= 0x40; // timer1 clock source = sys_clock
    }
    TH1 = TH10 = ~((clock_num >> 8) & 0xff);
    TL1 = TL10 = ~(clock_num & 0xff);
    TMOD &= ~0x30;
    TMOD |= 0x10; // mode 1

    set_running_t1(1);
    enable_t1_interrupt(1);
    enable_sys_interrupt(1);
}

// time range: 30ns-8us for 32M sys_clock(1-256 sys_clock)
inline void init_t1_mode2(uchar tick) {
    AUXR |= 0x40; // timer1 clock source = sys_clock
    TH1 = TL1 = 256 - tick;
    TMOD &= ~0x30;
    TMOD |= 0x20; // mode 2, autoload TL1 from TH1 when timer1 overflow
    set_running_t1(1);
    //enable_t1_interrupt(1);
    enable_sys_interrupt(1);
}

// time range: 30ns-24ms for 32M sys_clock
inline void init_t1(unsigned long long time_ns) {
    unsigned long long clock_num = (unsigned long long) (SYS_CLOCK / 1000000 * time_ns / 1000);
    if (clock_num < 255) {
        init_t1_mode2(clock_num);
    } else {
        init_t1_mode1(clock_num);
    }
    WAKE_CLKO |= 0x02; // enable timer1 clock output(P1.1)
}


void t1_interrupt()

__interrupt 3 __using 0 {
// interrupt handler here
// when using mode2, comment the following 2 lines;
if(TMOD&0x30!=0x20)
TH1 = TH10;
TL1 = TL10;
}
#endif

