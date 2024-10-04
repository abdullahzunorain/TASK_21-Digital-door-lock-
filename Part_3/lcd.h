#ifndef LCD_H
#define LCD_H

void lcd_init(void);
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char dat);
void lcd_showchar(unsigned char row, unsigned char column, unsigned char char_data);
void lcd_showstring(unsigned char row, unsigned char column, unsigned char *str);
void lcd_shownum(unsigned char row, unsigned char column, unsigned int num, unsigned char length);
void lcd_clear(void);

#endif
