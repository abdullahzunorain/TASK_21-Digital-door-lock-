#include "LCD.h"
#include <stdio.h>

unsigned int i = 0;
unsigned int j = 0;
unsigned int digit = 0;
unsigned int index = 0;

void ms_delay(unsigned int x)
{
	for(i=0; i<x; i++)
		for(j=0; j<112; j++);
}

void LCD_write_cmd(unsigned char cmd)
{
	LCD_data = cmd;
	
	LCD_RS = 0;
	LCD_WR = 0;
	LCD_EN = 1;
	ms_delay(10);
	LCD_EN = 0;
	ms_delay(10);
}
void LCD_write_data(unsigned char d)
{
	LCD_data = d;
	LCD_RS = 1;
	LCD_WR = 0;
	
	LCD_EN = 1;
	ms_delay(10);
	LCD_EN = 0;
	ms_delay(10);
}
void LCD_clear()
{
	LCD_write_cmd(0x01);		// Clear display and set DDRAM address 0x00
	ms_delay(10);
}

void LCD_init(void)
{
	LCD_write_cmd(0x38); 			// 8-bit, 2-line display, 5x8 font
	ms_delay(10);
	
	LCD_clear();
	ms_delay(10);
	
	LCD_write_cmd(0x06);
	ms_delay(10);
	
	LCD_write_cmd(0x0C); 			// Display on, cursor off, blink off
	ms_delay(10);
}

void set_cursor(unsigned int row, unsigned int col)
{
	if(row == 1)
	{
		LCD_write_cmd(0x80 | col-1);
		ms_delay(10);
	}
	else if(row == 2)
	{
		LCD_write_cmd(0xC0 | ((col-1)+0x40));
		ms_delay(10);
	}
}
void disp_string(char name[])
{
    int i = 0;
    while (name[i] != '\0')
    {
        LCD_write_data(name[i]);
        ms_delay(10);
        i++;
    }
}

void LCD_default_psw_display(unsigned int Number, unsigned char Length)
{
    unsigned int divisor = 1;
    unsigned char q;
    unsigned int dig = 0;
    unsigned int v;

    for (v = 1; v < Length; v++) {
        divisor *= 10;
    }

    for (q = 0; q < Length; q++) {
        dig = (Number / divisor) % 10;
        LCD_write_data(dig + '0');
        divisor /= 10;
    }
}
