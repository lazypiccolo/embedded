#include "../uart/uart.h"
#include "../sys/sys.h"
#include "../lcd_st7735/lcd_st7735.h"
#include "../../common/util.h"

__xdata char data[255] = {0,};

int main() {
    init_uart(38400, NONE_PARITY);
    //init_uart_mode0(0);
    for (int i = 0; i <= 255; i++) {
        data[i] = i;
    }
    Mcu_InitIo();
    Lcd_Initial();
    Lcd_SingleColour(WHITE);
    TextStyle text_style = {LCD1602, RED, WHITE, 1};
    Lcd_ShowMessage1602("Aloha, world!", 13, 2, 2, &text_style);
    char usart_data = 'A';
    char lcd_buf[7] = "Data:  ";
    lcd_buf[6] = usart_data;
    while (1) {
        //uart_send_data(data, 10);
        //uart_send_data(data, 1);
        for (int i = 0; i < 10; i++) {
            //uart_send_data(data, 255);
            char tmp = uart_read_char();
            if (tmp) lcd_buf[6] = tmp;
//            uart_send_char(usart_data);
//            uart_send_char(10);
//            uart_send_char(13);
            Lcd_ShowMessage1602(lcd_buf, 7, 2, 3 + LCD1602HEIGHT, &text_style);
            lcd_buf[6]++;
            delay(10000);
        }
    }
}

