#include "KEY_PAD.h"
#include "BUZZER.h"
#include "LCD.h"

unsigned int second_count = 0;

unsigned char READ_SWITCHES(void)
{
	row_1 = 0; row_2 = 1; row_3 = 1; row_4 = 1;
	if (C1 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C1==0); return '/'; } 
	if (C2 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C2==0); return '9'; } 
	if (C3 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C3==0); return '8'; } 
	if (C4 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C4==0); return '7'; }
	
	row_1 = 1; row_2 = 0; row_3 = 1; row_4 = 1;
	
	if (C1 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C1==0); return 'x'; } 
	if (C2 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C2==0); return '6'; } 
	if (C3 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C3==0); return '5'; } 
	if (C4 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C4==0); return '4'; }
	
	row_1 = 1; row_2 = 1; row_3 = 0; row_4 = 1;
	
	if (C1 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C1==0); return '-'; } 
	if (C2 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C2==0); return '3'; } 
	if (C3 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C3==0); return '2'; } 
	if (C4 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C4==0); return '1'; }
	
	row_1 = 1; row_2 = 1; row_3 = 1; row_4 = 0;
	
	if (C1 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C1==0); return '+'; }
	if (C3 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C3==0); return '0'; }
	if (C2 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C2==0) { second_count ++; ms_delay(400);}
	if(second_count >= 10) { second_count = 0; return 'R'; }
	else if(second_count < 10) { second_count = 0; return '='; } } 
	 
	if (C4 == 0) { buzzer_sound(500,0xFF,0xA3); ms_delay(100); while (C4 == 0) { second_count ++; ms_delay(300); }
	if(second_count >= 10) { second_count = 0; return 'N'; }
	else if(second_count < 10) { second_count = 0; return 'c'; } }
	return 'n';
}