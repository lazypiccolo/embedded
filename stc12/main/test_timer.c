#include "../sys/sys.h"
#include "../uart/uart.h"
#include "../timer/timer.h"
#include "../lcd_st7735/lcd_st7735.h"
#include "../../common/util.h"
#include "../../common/itoa.h"

extern TextStyle default_style;

int main() {
    init_uart(38400, NONE_PARITY);
    Mcu_InitIo();
    Lcd_Initial();
    init_t0(564);
    //init_t1(10100);
    Lcd_SingleColour(WHITE);
    Lcd_ShowMessage1602("Hello", 5, 10, 10, &default_style);
//    init_t1_mode2(77);
//    set_running_t1(1);
//    init_t1_mode2();
//    set_running_t1(1);

//    while (1) {
//        char buf[20];
//        for (uchar i = 0; i < 30; i++)buf[i] = ' ';
//        char *cursor = buf;
//        ui2hex(0x8a, cursor);
//        cursor += 5;
//        ui2dec(998, cursor);
//        cursor += 5;
//        f2a(-9.886787, 3, cursor);
//        cursor += 7;
//        i2dec(-998, cursor);
//        Lcd_ShowMessage1602(buf, 21, 0, 30, &default_style);
//        delay(10000);
//    }
    while (1) {
        char buf[16] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',};
        signed len = uart_read_line(buf);
        if (len >= 0) {
            Lcd_ShowMessage1602(buf, 10, 10, 20, &default_style);
            char raw[40];
            for (signed char j = 0; j < 40; j++) { raw[j] = ' '; }
            uint n = hex2i(buf, len);
            uint l = ui2dec(n, raw);
//            char *cursor = raw;
//            for (char j = 0; j < len; j++) {
//                char l = ui2hex(buf[j], cursor);
//                cursor += l;
//            }
            init_t0(n);
            Lcd_ShowMessage1602(raw, 20, 10, 30, &default_style);
        }
//        if (data) {
//            init_t0_mode1(100L * (data - '0'));
//        }
        delay(10000);
    }
}

