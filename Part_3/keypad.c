#include <reg51.h>
#include "KEYPAD.h"

#define keypad_data P1
sbit row1 = P2^0;
sbit row2 = P2^1;
sbit row3 = P2^2;
sbit row4 = P2^3;
sbit col1 = P2^4;
sbit col2 = P2^5;
sbit col3 = P2^6;

unsigned char keypad(void) {
    unsigned char row, col;
    keypad_data = 0x0F;
    while (1) {
        row1 = 0;
        if (keypad_data != 0x0F) {
            if (keypad_data == 0x0E) row = 1;
            if (keypad_data == 0x0D) row = 2;
            if (keypad_data == 0x0B) row = 3;
            if (keypad_data == 0x07) row = 4;
            keypad_data = 0xF0;
            col1 = 0;
            if (keypad_data != 0xF0) {
                if (keypad_data == 0xE0) col = 1;
                if (keypad_data == 0xD0) col = 2;
                if (keypad_data == 0xB0) col = 3;
                if (keypad_data == 0x70) col = 4;
                return (row - 1) * 4 + col;
            }
        }
        col1 = 1;
        row1 = 1;
        col2 = 0;
        if (keypad_data != 0xF0) {
            if (keypad_data == 0xE0) col = 1;
            if (keypad_data == 0xD0) col = 2;
            if (keypad_data == 0xB0) col = 3;
            if (keypad_data == 0x70) col = 4;
            return (row - 1) * 4 + col;
        }
        col2 = 1;
        col3 = 0;
        if (keypad_data != 0xF0) {
            if (keypad_data == 0xE0) col = 1;
            if (keypad_data == 0xD0) col = 2;
            if (keypad_data == 0xB0) col = 3;
            if (keypad_data == 0x70) col = 4;
            return (row - 1) * 4 + col;
        }
        col3 = 1;
    }
}
