#include <reg52.h>
#include <BUZZER.h>
#include <intrins.h>

void delay(unsigned char p,unsigned char q)
{
	TMOD=0x01; 					 //timer0 mode1(16 bit)
	TL0=q;     					 //load TL0
	TH0=p;     					 //load TH0
	TR0=1;   						 //turn on T0
	while(TF0==0); 			 // wait for flag generation
		TR0=0;   				   // turn off T0
		TF0=0;    				 // clear TF0
}

void buzzer_sound(int c, unsigned char j, unsigned char k)
{
	int i;
	for(i = 0; i<c; i++)  //to play sound
		{
			buzzer = 1;
			delay(j,k);
			buzzer = 0;
			delay(j,k);
		}
}

void UART_init(void)
{
	TMOD = 0x20;		// Timer 1 8-bit auto reload mode
	TH1 = 0xFD;			//baud rate 9600
	SCON = 0x50;		//8-bit UART
	
	TR1 = 1;
}