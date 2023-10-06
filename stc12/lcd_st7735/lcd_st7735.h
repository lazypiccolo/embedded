#ifndef __LCD_ST7735__H
#define __LCD_ST7735__H

#include "../../common/lcd1602_encoding.h"
#include "config.h"
#include "../../common/types.h"
// commonly used colors, only for 16bits(RGB565)
#define RED     0xf800
#define GREEN   0x07e0
#define BLUE    0x001f
#define WHITE   0xffff
#define BLACK   0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D
#define GRAY1   0x8410
#define GRAY2   0x4208

void Mcu_DelayMs(uint time) {
    uint i, j;
    for (i = 0; i < time; i++)
        for (j = 0; j < 250; j++);
}


// send 8 bits by pseudo-spi
inline void Mcu_WriteData(uchar Data) {
    uchar i = 0;
    for (i = 8; i > 0; i--) {
        if (Data & 0x80)
            sda = 1;
        else
            sda = 0;
        scl = 0;
        scl = 1;
        Data <<= 1;
    }
}

// write command(8bits) to lcd
inline void Lcd_WriteIndex(uchar Data) {
    cs = 0;
    rs = 0;
    Mcu_WriteData(Data);
    cs = 1;
}

// write data(8bits) to lcd
void Lcd_WriteData(uchar Data) {
    uchar i = 0;
    cs = 0;
    rs = 1;
    Mcu_WriteData(Data);
    cs = 1;
}

// write data(16bits) to lcd
void Lcd_WriteData_16Bit(uint Data) {
    uchar i = 0;
    cs = 0;
    rs = 1;
    Mcu_WriteData(Data >> 8);         // write msb 8
    Mcu_WriteData(Data);                    // write lsb 8
    cs = 1;

}

void Lcd_Reset() {
    reset = 0;
    Mcu_DelayMs(100);
    reset = 1;
    Mcu_DelayMs(100);
}

void Mcu_InitIo() {
#ifdef MCU_STC12
    P2M1 &= ~(1 << 2), P2M0 |= (1 << 2);
#endif
#ifdef MCU_STC89
#endif

#ifdef MCU_ATMEGA
#endif
}

void Lcd_Initial() {
    Lcd_Reset();// reset before LCD Init.

    Lcd_WriteIndex(0x11);// sleep exit & booster on
    Mcu_DelayMs(120);

    Lcd_WriteIndex(0x20); // display inversion off
    // Lcd_WriteIndex(0x21); // display inversion on

    Lcd_WriteIndex(0xB1); // frame rate control. in normal mode(full colors)
    Lcd_WriteData(0x05);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);

    Lcd_WriteIndex(0xB2);
    Lcd_WriteData(0x05);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);

    Lcd_WriteIndex(0xB3);
    Lcd_WriteData(0x05);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x05);
    Lcd_WriteData(0x3A);
    Lcd_WriteData(0x3A);

    Lcd_WriteIndex(0xB4); // display inversion mode control
    Lcd_WriteData(0x03);

    Lcd_WriteIndex(0xC1); // power control: vgh=9.8;vgl=-7.35
    Lcd_WriteData(0xC0);

    Lcd_WriteIndex(0xC2);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x00);

    Lcd_WriteIndex(0xC3);
    Lcd_WriteData(0x8D);
    Lcd_WriteData(0x6A);

    Lcd_WriteIndex(0xC4);
    Lcd_WriteData(0x8D);
    Lcd_WriteData(0xEE);

    Lcd_WriteIndex(0xE0); // gamma correction, '+' polar
    Lcd_WriteData(0x10);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x07);
    Lcd_WriteData(0x0A);
    Lcd_WriteData(0x12);
    Lcd_WriteData(0x27);
    Lcd_WriteData(0x37);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0xE1); // gamma correction, '-' polar
    Lcd_WriteData(0x10);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x03);
    Lcd_WriteData(0x0F);
    Lcd_WriteData(0x06);
    Lcd_WriteData(0x02);
    Lcd_WriteData(0x08);
    Lcd_WriteData(0x0A);
    Lcd_WriteData(0x13);
    Lcd_WriteData(0x26);
    Lcd_WriteData(0x36);
    Lcd_WriteData(0x00);
    Lcd_WriteData(0x0D);
    Lcd_WriteData(0x0E);
    Lcd_WriteData(0x10);

    Lcd_WriteIndex(0x3A); // color mode
    Lcd_WriteData(0x05); // 16-bit/pixel

    Lcd_WriteIndex(0x36); // memory data access control
    Lcd_WriteData(0xC8);

    Lcd_WriteIndex(0x29); // display on

}


void Lcd_SetRegion(uint x_start, uint y_start, uint x_end, uint y_end) {

    Lcd_WriteIndex(0x2a);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_start + OFFSET_X);
    Lcd_WriteData(0x00);
    Lcd_WriteData(x_end + OFFSET_X);

    Lcd_WriteIndex(0x2b);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_start + OFFSET_Y);
    Lcd_WriteData(0x00);
    Lcd_WriteData(y_end + OFFSET_Y);
    Lcd_WriteIndex(0x2c);
}


inline void Lcd_SingleColour(int color) {
    uchar i, j;
    Lcd_SetRegion(0, 0, SIZE_X, SIZE_Y);
    for (i = 0; i < SIZE_Y; i++)
        for (j = 0; j < SIZE_X; j++)
            Lcd_WriteData_16Bit(color);
}

void show_gradual() {
    Lcd_SingleColour((int) WHITE);
    int w = 142, h = 128;
    Lcd_SetRegion(-31, 0, 111, 160);
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            if (i > w / 2) {
                Lcd_WriteData_16Bit((int) (0.0014 * i * j));
            } else {
                Lcd_WriteData_16Bit(((int) (0.0014 * i * j * 2)) << 11);
            }
        }
    }
}

enum CharSet {
    LCD1602 = 1,
    LCD8x8 = 2,
    LCD16x16 = 3,
};
typedef struct {
    enum CharSet char_set;
    int foreground_color;
    int background_color;
    uchar char_gap;
} TextStyle;

inline void Lcd_ShowLcd1602Char(int x, int y, const uchar data, TextStyle *text_style) {
    Lcd_SetRegion(x, y, x + LCD1602WIDTH - 1 + text_style->char_gap, y + LCD1602HEIGHT);
    const char *c = lcd1602[data - ' '];
    for (int i = 0; i < LCD1602HEIGHT; i++) {
        char d = *(c + i);
        for (int j = 0; j < LCD1602WIDTH + text_style->char_gap; j++) {
            int color = text_style->background_color;
            if (d & 0x10) { color = text_style->foreground_color; }
            Lcd_WriteData_16Bit(color);
            d <<= 1;
        }
    }
}

void Lcd_ShowMessage1602(char *message, uint len, int x, int y, TextStyle *text_style) {
    int char_width = LCD1602WIDTH + text_style->char_gap;
    for (uint i = 0; i < len; i++) {
        uchar data = message[i];
        Lcd_ShowLcd1602Char(x + char_width * i, y, data, text_style);
    }
}

inline void Lcd_ShowImageEncoding565(uint **image, uchar top, uchar left, uchar height, uchar width) {
    Lcd_SetRegion(left, top, left + width - 1, top + height - 1);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            uint color = *((uint *) image + i * width + j);
            Lcd_WriteData_16Bit(color);
        }
    }
}

TextStyle default_style = {
        .char_set = LCD1602,
        . foreground_color = BLACK,
        . background_color= WHITE,
        . char_gap = 1,
};
#endif

