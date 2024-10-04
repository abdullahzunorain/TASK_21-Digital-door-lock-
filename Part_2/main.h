#ifndef Main_H
#define Main_H

sbit buzzer_pin=P1^5;
sbit output=P3^0;  		//Output to motor
//buzzer pin make problem for keypaid 
sbit keyrow1 = P1 ^ 0;
sbit keyrow2 = P1 ^ 1;
sbit keyrow3 = P1 ^ 2;
sbit keyrow4 = P1 ^ 3;
sbit keycolumn1 = P1 ^ 4;
sbit keycolumn2 = P1 ^ 5;
sbit keycolumn3 = P1 ^ 6;
sbit keycolumn4 = P1 ^ 7;
sbit rs = P3 ^ 5;
sbit rw = P3 ^ 6;
sbit en = P3 ^ 7;

sbit SDA_BUS = P2^0;
sbit SCL_BUS = P2^1;

/*=========================================
   Prototypes for I2c functions
 ==========================================*/
void eeprom(void);
void InitI2c(void);
void StartI2c(void);
void RepeatedStartI2c(void);
void StopI2c(void);
void SendAckBit(void);
void SendNackBit(void);
void delay(unsigned int);
bit write_i2c(unsigned char);
unsigned char read_i2c(void);
void write_byte_to_eeprom(unsigned int,unsigned char);
unsigned char  read_byte_from_eeprom(unsigned int);
void deelay(unsigned char p,unsigned char q);
void play(unsigned char j,unsigned char k);
  void change();

// EEPROM
void write_number_on_lcd(unsigned int digit)  ;
void save();
void start();
void stop();
void aknowledge();
void send_byte(unsigned char);
unsigned char Read();
unsigned char read_byte();
void dddelay(unsigned int);
void call();

void savee();
void disp_num(float num)   ;
void UART_Init();

void password();
void lcd_write_int(int time_val)	;
void timer(int msec);
void lcd_init(void);
void lcd_write(unsigned char);
void LCD_Command (unsigned char);
void delay1(unsigned int);
void lcd_string(unsigned char *);

char keypad();
void check();
void delay(unsigned int);
void display_num_serial(unsigned int z);
void serial_data(void);

#endif