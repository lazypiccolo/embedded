#ifndef __ST7735_CONFIG__H
#define __ST7735_CONFIG__H


//---------------------------wiring illustration-------------------------------------//
#define bl        P2_2//backlight, maybe wired to high or pwm
#define scl       P2_3//spi clock
#define sda       P2_4//spi data
#define rs        P2_5//d/c(data/command)
#define cs        P2_6//chip selection, wired to ce
#define reset     P2_7//reset pin or high

#define MCU_STC12 1


// set the origin point of the lcd
#define OFFSET_X 2
#define OFFSET_Y 3
#define SIZE_X 128
#define SIZE_Y 130

#endif
