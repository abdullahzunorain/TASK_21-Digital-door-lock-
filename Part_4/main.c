#include <reg52.h>
#include <stdlib.h>
#include "LCD.h"
#include "EEPROM.h"
 

void serial_display_psw(unsigned int Number, unsigned char Length)
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
        SBUF = dig + '0';
        divisor /= 10;
				ms_delay(100);
    }
}
void main(void)
{
	unsigned long int default_psw;
	unsigned long int number;
	
	unsigned int min = 100000;
  unsigned int max = 999999;
	
	srand(012345);
	
	number = min + rand() % (max - min + 1);
	
	TMOD = 0x20;		// Timer 1 8-bit auto reload mode
	TH1 = 0xFD;			//baud rate 9600
	SCON = 0x50;		//8-bit UART
	
	TR1 = 1;
	
	LCD_init();
	
	EEPROM_Init();
	
	
	EEPROM_Write_4Bytes(number,0);
	
	default_psw = EEPROM_Read_4Bytes(0);
	
	while(1)
	{
		set_cursor(1,1);
		disp_string("default password");
		
		set_cursor(2,5);
		LCD_default_psw_display(default_psw,6);
		
		ms_delay(1000);
		
  	serial_display_psw(default_psw,6);
		ms_delay(2000);
		
		while(TI == 0);
			TI = 0;
		ms_delay(1000);

	}
	
}