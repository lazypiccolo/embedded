#ifndef __ITOA__H
#define __ITOA__H

#include "types.h"

__code char hex_table[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void reverse(char *start, char *end) {
    for (; start < end; start++, end--) {
        char tmp = *start;
        *start = *end;
        *end = tmp;
    }
}

inline char i2a(uint num, int base, char *res) {
    uchar index = 0;
    uchar number_start = 0;
    switch (base) {
        case 10:
            do {
                res[index++] = num % 10 + '0';
                num /= 10;
            } while (num > 0);
            break;
        case 16:
            number_start = 2;
            res[index++] = '0';
            res[index++] = 'X';
            do {
                res[index++] = hex_table[num & 0x0f];
                num >>= 4;
            } while (num > 0);
            break;
        case 8:
            number_start = 1;
            res[index++] = '0';
            do {
                res[index++] = hex_table[num & 0x07];
                num >>= 3;
            } while (num > 0);
            break;
        default:
            break;
    }
    reverse(res + number_start, res + index - 1);
    return index;
}

inline char ui2dec(uint num, char *res) {
    return i2a(num, 10, res);
}

inline char ui2hex(uint num, char *res) {
    return i2a(num, 16, res);
}

inline char ui2oct(uint num, char *res) {
    return i2a(num, 8, res);
}

inline char i2dec(int num, char *res) {
    char negative = num < 0;
    if (negative)num = -num;
    uchar sign_len = 0;
    if (negative) {
        res[0] = '-';
        sign_len = 1;
    }
    return i2a(num, 10, res + sign_len) + sign_len;
}

inline char f2a(float value, int floating_num, char *res) {
    char negative = value < 0;
    uchar sign_len = 0;
    char *cursor = res;
    if (negative) {
        value = -value;
        sign_len = 1;
        res[0] = '-';
        cursor++;
    }

    int int_part = (int) (value);
    int scale = 1;
    int i;
    for (i = 0; i < floating_num; i++)scale *= 10;
    int float_part = (int) ((value - int_part) * scale);
    char int_len = ui2dec(int_part, cursor);
    cursor += int_len;
    *cursor = '.';
    cursor++;
    char float_len = ui2dec(float_part, cursor);;
    return sign_len + int_len + 1 + float_len;
}

uint a2i(char *data, uchar len) {
    uint res = 0;
    for (uchar i = 0; i < len; i++) {
        res *= 10;
        res += data[i] - '0';
    }
    return res;
}

uint hex2i(char *data, uchar len) {
    uint res = 0;
    for (uchar i = 0; i < len; i++) {
        res <<= 4;
        char c = data[i];
        if (c <= '9') {
            res += data[i] - '0';
        } else {
            res += data[i] - 'A' + 10;
        }
    }
    return res;
}

#endif

