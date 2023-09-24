#ifndef __ITOA__H
#define __ITOA__H

#include "types.h"

__xdata char int_buf[20] = {0,};

__code char hex_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

char *i2a(uint num, int base) {
    uchar index = 18;
    switch (base) {
        case 10:
            do {
                int_buf[index--] = num % 10 + '0';
                num /= 10;
            } while (num > 0);
            break;
        case 16:
            do {
                int_buf[index--] = hex_table[num & 0x0f];
                num >>= 4;
            } while (num > 0);
            int_buf[index--] = 'X';
            int_buf[index--] = '0';
            break;
        case 8:
            do {
                int_buf[index--] = hex_table[num & 0x07];
                num >>= 3;
            } while (num > 0);
            int_buf[index--] = '0';
            break;
        default:
            break;
    }
    return int_buf + index + 1;
}

// not reentrant
char *ui2dec(uint num) {
    return i2a(num, 10);
}

// not reentrant
char *ui2hex(uint num) {
    return i2a(num, 16);
}

// not reentrant
char *ui2oct(uint num) {
    return i2a(num, 8);
}

// not reentrant
char *i2dec(int num) {
    char negative = num < 0;
    if (negative)num = -num;
    char *p = i2a(num, 10);
    if (negative) {
        *(p - 1) = '-';
        return p - 1;
    }
    return p;
}

__xdata char float_buf[20] = {0,};

// not reentrant
char *f2a(float value, int floating_num) {
    char negative = value < 0;
    if (negative)value = -value;
    int int_part = (int) (value);
    int scale = 1;
    int i;
    for (i = 0; i < floating_num; i++)scale *= 10;
    int float_part = (int) ((value - int_part) * scale);
    int index = 18;
    for (i = 0; i < floating_num; i++) {
        float_buf[index--] = float_part % 10 + '0';
        float_part /= 10;
    }
    float_buf[index--] = '.';
    do {
        float_buf[index--] = int_part % 10 + '0';
        int_part /= 10;
    } while (int_part > 0);
    if (negative) {
        float_buf[index--] = '-';
    }
    return float_buf + index + 1;
}

#endif
