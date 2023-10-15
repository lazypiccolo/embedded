#include "../../common/stc12x56xx.h"
#include "../ds18B20/ds18B20.h"
#include "../io/io.h"
#include "../lcd_st7735/lcd_st7735.h"
#include "../../common/itoa.h"
#include <string.h>

__xdata char buf[20];
__xdata char buf2[20];

int main() {
    int loop = 0;
    Mcu_InitIo();
    Lcd_Initial();
    Lcd_SingleColour(WHITE);
    Lcd_ShowMessage1602("hello", 5, 10, 10, &default_style);


    ds1820_config(0x80, 0xff, 9);

    while (1) {

        uint temp = ds1820_read_temperature_sync();
        uchar len = ui2hex(temp, buf);
        Lcd_ShowMessage1602(buf, len, 10, 40, &default_style);
        char loop_buf[6];
        len = ui2dec(loop, loop_buf);
        Lcd_ShowMessage1602(loop_buf, len, 10, 100, &default_style);
        loop++;
    }
}
