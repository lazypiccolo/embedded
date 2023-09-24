#include "../../common/types.h"
#include "../../common/stc12x56xx.h"
#include "../timer/timer.h"

/*Define UART parity mode*/
#define NONE_PARITY 0 //None parity
#define ODD_PARITY 1 //Odd parity
#define EVEN_PARITY 2 //Even parity
#define MARK_PARITY 3 //Mark parity
#define SPACE_PARITY 4 //Space parity

#define PARITYTYPE EVEN_PARITY //Testing even parity

#define UART_BUF_LEN 20
__xdata char uart_buf[UART_BUF_LEN] = {0,};
#if PARITYTYPE != NONE_PARITY
__xdata char uart_RB8_buf[UART_BUF_LEN / 8 + 1] = {0};
#endif

uchar busy = 0;
uchar head = 0, tail = 0;


void enable_uart_interrupt(char status) {
    ES = status;
}

// 8bit shift register.
// RXD<->Data, TXD<->Clock, LSB First, fixed baud rate = sys_clock/(1 or 12)
void init_uart_mode0(char x6) {
    SCON |= 0x00;
    if (x6) {
        AUXR |= 0x20;
    } else {
        AUXR &= ~0x20;
    }
    enable_uart_interrupt(1);
    enable_sys_interrupt(1);
}

// baud rate range: 1.3-2,000,000(1.3 is accurate and 2M is raw)
// timer1 will be taken for clock.
inline void init_uart(unsigned long long baud, char parity) {
    // Baud rate in mode 1 = (2^SMOD /32 ) x Timer 1 overflow rate
    // When T1x12=0, Timer 1 overflow rate = sys_clock/12/(256-TH1);
    // When T1x12=1, Timer 1 overflow rate = sys_clock / (256-TH1);

    // baud rate > SYS_CLOCK/32, use SMOD = 1;
    if (baud > (SYS_CLOCK >> 5)) {
        PCON |= 0x80; // SMOD = 1
        baud >>= 1;
    } else {
        PCON &= ~0x80;
    }
    unsigned long long time_ns = (unsigned long long) (1000000000L / 32 / baud);
    init_t1(time_ns);
    if (parity == NONE_PARITY) {
        // mode 1
        SCON |= 0x50;
    } else {
        // mode 3
        SCON |= 0xd0;
    }
    enable_uart_interrupt(1);
    enable_sys_interrupt(1);
}

void init_uart_mode1(uint baud) {
    // 8bit
    // Baud rate in mode 1 = (2^SMOD /32 ) x Timer 1 overflow rate
    // When T1x12=0, Timer 1 overflow rate = sys_clock/12/(256-TH1);
    // When T1x12=1, Timer 1 overflow rate = sys_clock / (256-TH1);

}

void init_uart_mode2() {
    // Baud rate in mode 2 = (2^SMOD/64) x SYSclk

}

void init_uart_mode3(uint baud) {
    // Baud rate in mode 3 = (2^SMOD /32 ) x Timer 1 overflow rate
    // When T1x12=0, Timer 1 overflow rate = sys_clock/12/(256-TH1);
    // When T1x12=1, Timer 1 overflow rate = sys_clock / (256-TH1);

}

void uart_send_char(char data) {
    while (busy);
    SBUF = data;
    busy = 1;
    //while (!TI) { TI = 0; }
}

void uart_send_data(char *data, uchar len) {
    for (uchar i = 0; i < len; i++) {
        uart_send_char(data[i]);
    }
}

// not thread-safe
char uart_read() {
    if (tail == head) return 0;
    char data = uart_buf[tail];
#if PARITYTYPE != NONE_PARITY
//uart_RB8_buf[head>>8]&=; // handle parity
#endif
    tail++;
    if (tail == UART_BUF_LEN)tail = 0;
    return data;
}

void uart_interrupt()

__interrupt 4 __using 1{
if (TI) {
TI = 0;
busy = 0;
} // psw should be accessed, or it does not work
if (RI) {
RI = 0;
uart_buf[head] =
SBUF;
#if PARITYTYPE != NONE_PARITY
//uart_RB8_buf[head>>8]&=; // handle parity
#endif
head++;
if (head == UART_BUF_LEN)
head = 0;
}
}
