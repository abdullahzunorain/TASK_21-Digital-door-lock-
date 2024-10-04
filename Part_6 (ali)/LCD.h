#ifndef LCD_H
#define LCD_H
#include <reg52.h>

#define LCD_data P0	/* P1 port as data port */

extern unsigned int i, j;
extern const unsigned char name[20];

sbit LCD_RS = P2^6;		/* Register select pin */
sbit LCD_WR = P2^5;	/* Read/Write pin */
sbit LCD_EN = P2^7; 	/* Enable pin */

void ms_delay(unsigned int x);
void LCD_write_cmd(unsigned char cmd);
void LCD_write_data(unsigned char d);
void LCD_clear (void);
void set_cursor (unsigned int row, unsigned int col);
void LCD_init (void);
void disp_string(unsigned int row, unsigned int col, char name[]);	
void LCD_disp_numb(unsigned int row, unsigned int col, unsigned long int Number, unsigned char Length);
void LCD_clear_2ndline(void);
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
void display_float_on_lcd(float value);
void Display_hour (unsigned char hour);
void LCD_display(unsigned char Number);
void LCD_disp_PSW(unsigned int row, unsigned int col, unsigned long int Number);
void LCD_default_psw_display(unsigned int row, unsigned int col, unsigned long int Number, unsigned char Length);
void serial_display_psw(unsigned long int Number, unsigned char Length);
	
#endif