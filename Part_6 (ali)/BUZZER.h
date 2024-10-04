#ifndef BUZZER_H
#define BUZZER_H

sbit buzzer = P1^5; 			 //output pin 1

void UART_init(void);

void delay(unsigned char p,unsigned char q);

void buzzer_sound(int c,unsigned char j, unsigned char k);

#endif