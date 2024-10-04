#include <reg51.h>
#include "LCD.h"
#include <string.h>

#define lcd_data P0
sbit RW = P2^5;
sbit RS = P2^6;
sbit EN = P2^7;




void lcd_init() {
    lcd_command(0x38); // 8-bit mode, 2 lines, 5x7 dots
    lcd_command(0x0C); // Display ON, cursor OFF
    lcd_command(0x01); // Clear display
    lcd_command(0x80); // Set cursor to home position
}

void lcd_command(unsigned char cmd) {
    RS = 0;
    RW = 0;
    lcd_data = cmd;
    EN = 1;
    _nop_();
    EN = 0;
    _nop_();
}

void lcd_data(unsigned char dat) {
    RS = 1;
    RW = 0;
    lcd_data = dat;
    EN = 1;
    _nop_();
    EN = 0;
    _nop_();
}

void lcd_showchar(unsigned char row, unsigned char column, unsigned char char_data) {
    if (row == 0) {
        lcd_command(0x80 + column);
    } else if (row == 1) {
        lcd_command(0xC0 + column);
    }
    lcd_data(char_data);
}

void lcd_showstring(unsigned char row, unsigned char column, unsigned char *str) {
    if (row == 0) {
        lcd_command(0x80 + column);
    } else if (row == 1) {
        lcd_command(0xC0 + column);
    }
    while (*str) {
        lcd_data(*str++);
    }
}

void lcd_shownum(unsigned char row, unsigned char column, unsigned int num, unsigned char length) {
    char buffer[10];
    sprintf(buffer, "%0*d", length, num);
    lcd_showstring(row, column, buffer);
}

void lcd_clear() {
    lcd_command(0x01); // Clear display
    lcd_command(0x80); // Set cursor to home position
}
