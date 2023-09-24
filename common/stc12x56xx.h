/*-------------------------------------------------------------------------
   stc12x56xx.h - Register Declarations for STC10/11/12 Series
   Based on 8051.h and compiler.h

   Copyright (c) 2012, intron@intron.ac

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library; see the file COPYING. If not, write to the
   Free Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.

   As a special exception, if you link this library with other files,
   some of which are compiled with SDCC, to produce an executable,
   this library does not by itself cause the resulting executable to
   be covered by the GNU General Public License. This exception does
   not however invalidate any other reasons why the executable file
   might be covered by the GNU General Public License.
-------------------------------------------------------------------------*/

/*
   Brief:

       STC10/11/12 series are 8051-compatible MCU's. The "official" website
   is http://www.stcmcu.com/ (In Chinese Han only), and datasheets in Chinese
   Han and English can be downloaded there.

   Reference:

   1. The "official" C header file (written for another C51 compiler):
        http://www.stcmcu.com/datasheet/stc/STC-AD-PDF/STC_NEW_8051.H
   2. Datasheets for STC12(C/LE)5Axx(S2/AD) series:
      Chinese Han:
        http://www.stcmcu.com/datasheet/stc/STC-AD-PDF/STC12C5A60S2.pdf
      English:
        http://www.stcmcu.com/datasheet/stc/STC-AD-PDF/STC12C5A60S2-english.pdf
   3. Datasheets for STC12(C/LE)52xxAD series:
      Chinese Han:
        http://www.stcmcu.com/datasheet/stc/STC-AD-PDF/STC12C5201AD.pdf
      English:
        http://www.stcmcu.com/datasheet/stc/STC-AD-PDF/STC12C5201AD-english.pdf
   4. Datasheets for STC11/10 series:
      Chinese Han:
        http://www.stcmcu.com/datasheet/stc/STC-AD-PDF/STC11F-10Fxx.pdf
      English:
        http://www.stcmcu.com/datasheet/stc/STC-AD-PDF/STC11F-10Fxx-english.pdf
 */

#ifndef _STC12x56xx_H_
#define _STC12x56xx_H_

#include <8051.h>
#include <compiler.h>

#ifdef REG8051_H
#undef REG8051_H
#endif

/*
 * Auxiliary Register
 *   Bit Mapping: T0x12 T1x12 UART_M0x6 EADCI ESPI ELVDI - -
 *   Reset Value: 0000,00xx
 */
SFR(AUXR, 0x8E);

/*
 * Control Register for Clock Output and Power Down Wake-up
 *   Bit Mapping: PCAWAKEUP RXD_PIN_IE T1_PIN_IE T0_PIN_IE
 *                - - T1CLKO T0CLKO
 *                (Here "O" is the letter meaning "output", not the digit.)
 *   Reset Value: 0000,xx00
 */
SFR(WAKE_CLKO, 0x8F);

/*
 * Clock Devider Register
 *   Bit Mapping: - - - - - CLKS2 CLKS1 CLKS0
 *   Reset Value: xxxx,x000
 */
SFR(CLK_DIV, 0xC7);

/* Two extended bits in IE */
SBIT(EPCA_LVD, 0xA8, 6); /* Enable PCA & Low Voltage Detection Interrupt */
SBIT(EADC_SPI, 0xA8, 5); /* Enable ADC & SPI Interrupt */

/* Three extended bits in IP */
SBIT(PPCA_LVD, 0xB8, 6); /* Interrupt Priority for PCA & Low Voltage Detection */
SBIT(PADC_SPI, 0xB8, 5); /* Interrupt Priority for ADC & SPI */

/*
 * Higher bits for Interrupt Priority
 *   Bit Mapping: - PPCA_LVDH PADC_SPIH PSH PT1H PX1H PT0H PX0H
 *   Reset Value: x000,0000
 */
SFR(IPH, 0xB7);

/* Working Mode Registers for P0, P1, P2, P3, P4 and P5 */
SFR(P0M0, 0x93);
SFR(P0M1, 0x94);
SFR(P1M0, 0x91);
SFR(P1M1, 0x92);
SFR(P2M0, 0x95);
SFR(P2M1, 0x96);
SFR(P3M0, 0xB1);
SFR(P3M1, 0xB2);

/* Slave Address Mask for Serial Communication */
SFR(SADEN, 0xB9);

/* Slave Address for Serial Communication */
SFR(SADDR, 0xA9);

/*
 * Watchdog Timer Control Register
 *   Bit Mapping: WDT_FLAG - EN_WDT CLR_WDT IDLE_WDT PS2 PS1 PS0
 *   Reset Value: xx00,0000
 */
SFR(WDT_CONTR, 0xE1);

/*
 * PCA Control Register
 *   Bit Mapping: CF CR - - CCF3 CCF2 CCF1 CCF0
 *   Reset Value: 00xx,0000
 */
SFR(CCON, 0xD8);
SBIT(CF, 0xD8, 7);
SBIT(CR, 0xD8, 6);
SBIT(CCF3, 0xD8, 3);
SBIT(CCF2, 0xD8, 2);
SBIT(CCF1, 0xD8, 1);
SBIT(CCF0, 0xD8, 0);

/*
 * PCA Mode Register
 *   Bit Mapping: CIDL - - - - CPS1 CPS0 ECF
 *   Reset Value: 0xxx,x000
 */
SFR(CMOD, 0xD9);

/* PCA Counter Registers */
SFR(CL, 0xE9); /* Lower 8 bits */
SFR(CH, 0xF9); /* Higher 8 bits */

/*
 * PCA Module 0 PWM Register
 *   Bit Mapping: - ECOM0 CAPP0 CAPN0 MAT0 TOG0 PWM0 ECCF0
 *   Reset Value: x000,0000
 */
SFR(CCAPM0, 0xDA);

/*
 * PCA Module 1 PWM Register
 *   Bit Mapping: - ECOM1 CAPP1 CAPN1 MAT1 TOG1 PWM1 ECCF1
 *   Reset Value: x000,0000
 */
SFR(CCAPM1, 0xDB);

/*
 * PCA Module 2 PWM Register
 *   Bit Mapping: - ECOM CAPP2 CAPN2 MAT2 TOG2 PWM2 ECCF2
 *   Reset Value: x000,0000
 */
SFR(CCAPM2, 0xDC);

/*
 * PCA Module 3 PWM Register
 *   Bit Mapping: - ECOM3 CAPP3 CAPN3 MAT3 TOG3 PWM3 ECCF3
 *   Reset Value: x000,0000
 */
SFR(CCAPM3, 0xDD);

/* PCA Module 0/1/2/3 Capture/Comparison Registers */
SFR(CCAP0L, 0xEA);
SFR(CCAP0H, 0xFA);
SFR(CCAP1L, 0xEB);
SFR(CCAP1H, 0xFB);
SFR(CCAP2L, 0xEC);
SFR(CCAP2H, 0xFC);
SFR(CCAP3L, 0xED);
SFR(CCAP3H, 0xFD);

/*
 * PCA Module 0 PWM Auxiliary Register
 *   Bit Mapping: - - - - - - EPC0H EPC0L
 *   Reset Value: xxxx,xx00
 */
SFR(PCA_PWM0, 0xF2);

/*
 * PCA Module 1 PWM Auxiliary Register
 *   Bit Mapping: - - - - - - EPC1H EPC1L
 *   Reset Value: xxxx,xx00
 */
SFR(PCA_PWM1, 0xF3);

/*
 * PCA Module 2 PWM Auxiliary Register
 *   Bit Mapping: - - - - - - EPC2H EPC2L
 *   Reset Value: xxxx,xx00
 */
SFR(PCA_PWM2, 0xF4);

/*
 * PCA Module 3 PWM Auxiliary Register
 *   Bit Mapping: - - - - - - EPC3H EPC3L
 *   Reset Value: xxxx,xx00
 */
SFR(PCA_PWM3, 0xF5);

/*
 * ADC Control Register
 *   Bit Mapping: ADC_POWER SPEED1 SPEED0 ADC_FLAG ADC_START CHS2 CHS1 CHS0
 *   Reset Value: 0000,0000
 */
SFR(ADC_CONTR, 0xC5);

/* ADC Converting Result Registers */
SFR(ADC_DATA, 0xC6); /* Higher Bits */
SFR(ADC_LOW2, 0xBE); /* Lower Bits */

/*
 * SPI Control Register
 *   Bit Mapping: SSIG SPEN DORD MSTR CPOL CPHA SPR1 SPR0
 *   Reset Value: 0000,0100
 */
SFR(SPCTL, 0x85);

/*
 * SPI Status Register
 *   Bit Mapping: SPIF WCOL - - - - - -
 *   Reset Value: 00xx,xxxx
 */
SFR(SPSTAT, 0x84);

/* SPI Data Register */
SFR(SPDAT, 0x86);

/* ISP/In-Application-Programming Data Register */
SFR(ISP_DATA, 0xE2);

/* ISP/In-Application-Programming Address Registers */
SFR(ISP_ADDRH, 0xE3); /* Higher 8 bits */
SFR(ISP_ADDRL, 0xE4); /* Lower 8 bits */

/*
 * ISP/In-Application-Programming Address Registers
 *   Bit Mapping: - - - - - - MS1 MS0
 *   Reset Value: xxxx,xx00
 */
SFR(ISP_CMD, 0xE5);

/* ISP/In-Application-Programming Trigger Registers */
SFR(ISP_TRIG, 0xE6);

/*
 * ISP/In-Application-Programming Control Register
 *   Bit Mapping: IAPEN SWBS SWRST CFAIL - WT2 WT1 WT0
 *   Reset Value: 0000,x000
 */
SFR(ISP_CONTR, 0xE7);

#endif /* _STC12_H_ */


