#include       <reg52.h>
#include      <stdlib.h>
#include 				 "LCD.h"
#include 			"EEPROM.h"
#include "SERVO_MOTOR.h"
#include     "KEY_PAD.h"
#include      "BUZZER.h"

#define NEW_DEVICE	  1                    //stats of door lock system
#define ENTER_PASS 		2
#define DOOR_UNLOCKED 3
#define OLD_PASSWORD  4
#define NEW_PASS 			5
#define DISABLED 			6
#define RESET_STATE   7

void main(void)
{
	unsigned int c, reset      = 0;
	unsigned int new_p				 = 0;
	unsigned int warning_count = 0;
	unsigned int chnge_count   = 0;
	unsigned int new_dev 			 = 0;
	unsigned int Flag 				 = 0;
	unsigned int l, count		   = 0;
	unsigned char  r_button, state;
	unsigned long int PSW      = 0;
	unsigned long int new_psw  = 0;
	unsigned long int  default_psw;
	unsigned long int       number;
	unsigned long int min = 100000;
  unsigned long int max = 999999;
	
	state = NEW_DEVICE;
	
	UART_init();
	LCD_init();
	EEPROM_Init();
	
	new_dev =        EEPROM_Read_byte(52, 0);
	warning_count = EEPROM_Read_byte(100, 0);
	chnge_count =   EEPROM_Read_byte(150, 0);

//   disp_string(1, 2, "default password");

//		default_psw = EEPROM_Read_4Bytes(0);
//		LCD_default_psw_display(2, 5, default_psw,6);
	  ms_delay(250);
	


	
	while(1)
	{
		r_button = READ_SWITCHES();
			


		switch(state)
		{
			case NEW_DEVICE:
				number = min + rand() % (max - min + 1);
			
				EEPROM_Write_byte(new_dev, 52,0);
				
				Flag = EEPROM_Read_byte(52, 0);
			
				if(Flag == 0)
				{
					while(r_button != 'c')
					{
						Flag = 1;
						new_dev = 1;
						r_button = READ_SWITCHES();
						
						EEPROM_Write_byte(Flag, 52, 0);
			
						EEPROM_Write_4Bytes(number,0);
						default_psw = EEPROM_Read_4Bytes(0);
					
						disp_string(1, 2, "default password");
						LCD_default_psw_display(2, 5, default_psw,6);
		
						ms_delay(500);
		
						serial_display_psw(default_psw,6);
						ms_delay(500);
		
						while(TI == 0);
						TI = 0;
					}
				}
				if(warning_count >= 5 || chnge_count >= 5)
				{
					state = DISABLED;
				}
				else 
				{
					state = ENTER_PASS;
					warning_count = 0;
					chnge_count = 0;
				
					EEPROM_Write_byte(warning_count, 100, 0);
					EEPROM_Write_byte(chnge_count,150,0);
					
					LCD_clear();
					r_button = 'n';
				}
			break;
			case ENTER_PASS:
				
				disp_string(1, 2, "enter password");

				set_servomoter_position(0.0);
				if (r_button != 'n')
				{
					if(r_button >= '0' && r_button <= '9')
					{
						if(count < 6)
						{
							PSW = PSW * 10 + (r_button - '0');
							ms_delay(100);
							LCD_disp_PSW(2, 5, PSW);
						
							count++;
							
						}
					}
					if(r_button == '=')
					{
						if(PSW > 0)
						{
							default_psw = EEPROM_Read_4Bytes(0);
							if(PSW == default_psw)
							{
								state = DOOR_UNLOCKED;
								EEPROM_SDA = 0;
								EEPROM_SCL = 0;
								Timer0_Intilization();
								LCD_clear();
								buzzer_sound(500, 0xFF, 0xA3);
								PSW = 0;
								count = 0;
							}
							else
							{
								LCD_clear();
								if(warning_count < 5)
								{
									warning_count++;
								
									EEPROM_Write_byte(warning_count, 100, 0);	
									warning_count = EEPROM_Read_byte(100, 0);
					
									disp_string(1, 5, "alert!");	
									LCD_disp_numb(1, 2, warning_count, 1);
									disp_string(1, 1, " ");
									disp_string(2, 1, "wrong password");
							
									buzzer_sound(1000, 0xFF, 0xA3);
									ms_delay(2000);
									LCD_clear();
									PSW = 0;
									count = 0;
								}
								else if(warning_count >= 5)
								{
									state = DISABLED;
									LCD_clear();
									PSW = 0;
									count = 0;
								}
							}
						}
						else
						{
							LCD_clear();
							disp_string(1, 6, "ERROR");
							disp_string(2, 3, "EMPTY PASS");
							ms_delay(1000);
							LCD_clear();
							count = 0;
							PSW = 0;
						}
					}
					if(r_button == 'N')
					{
						state = OLD_PASSWORD;
						new_p = 1;
						LCD_clear();
						count = 0;
						new_p = 1;
						PSW = 0;
					}
					else if(r_button == 'R')
					{
						state = OLD_PASSWORD;
						LCD_clear();
						reset = 1;
						count = 0;
						PSW = 0;
					}
				}
			break;
				
			case DOOR_UNLOCKED:
				disp_string(1,1,"DOOR UNLOCKED");
				set_servomoter_position(180.0);
				ms_delay(1000);
				
				LCD_clear();
				disp_string(1,1,"LOCKING DOOR IN");
			
				for(l=5; l>0; l--)
				{
					LCD_disp_numb(2, 8, l, 1);
					ms_delay(1000);
				}
				ms_delay(300);
				
				LCD_clear();
				buzzer_sound(1000,0xFF,0xA3);
				disp_string(1,3,"DOOR LOCKED");
				set_servomoter_position(0.0);
				ms_delay(500);
				
				LCD_clear();
				state = ENTER_PASS;
			break;
				
			case OLD_PASSWORD:
				disp_string(1, 2, "enter old passw");
				if (r_button != 'n')
				{
					if(r_button >= '0' && r_button <= '9')
					{
						if(count < 6)
						{
							PSW = PSW * 10 + (r_button - '0');
							ms_delay(100);
							LCD_disp_PSW(2, 5, PSW);
						
							count++;
							
						}
					}
					if(r_button == '=')
					{
						default_psw = EEPROM_Read_4Bytes(0);
						if(PSW == default_psw && new_p == 1)
						{
							state = NEW_PASS;
							new_p = 0;
							LCD_clear();
							buzzer_sound(1000, 0xFF, 0xA3);
							PSW = 0;
							count = 0;
						}
						else if(PSW == default_psw && reset == 1)
						{
							state = RESET_STATE;
							reset = 0;
							LCD_clear();
							PSW = 0;
							count = 0;
						}
						else
						{
							LCD_clear();
							if(chnge_count <= 5)
							{
								chnge_count++;
								
								EEPROM_Write_byte(chnge_count,150,0);
								chnge_count = EEPROM_Read_byte(150,0);
								
								disp_string(1, 1, "wrong-password");
								disp_string(2, 5, "C");
								
								LCD_disp_numb(2, 6, chnge_count, 1);
								
								for(c = 0; c < 3; c++)
								{
									buzzer_sound(500, 0xFF, 0xA3);
									ms_delay(250);
								}
								ms_delay(500);
								LCD_clear();
								PSW = 0;
								count = 0;
							}
							else if(chnge_count > 5)
							{
								state = DISABLED;
								LCD_clear();
								PSW = 0;
								count = 0;
							}
						}
					}
					if(r_button == 'c')
					{
						state = ENTER_PASS;
						LCD_clear();
						PSW = 0;
						count = 0;
					}
				}
			break;
			case NEW_PASS:
				disp_string(1, 2, "enter new-passw");
				if (r_button != 'n')
				{
					if(r_button >= '0' && r_button <= '9')
					{
						if(count < 6)
						{
							new_psw = new_psw * 10 + (r_button - '0');
							ms_delay(100);
							LCD_disp_PSW(2, 5, new_psw);
							
							count++;
							
						}
					}
					if(r_button == '=')
					{
						LCD_disp_numb(2, 5, new_psw,6);
						ms_delay(2000);
						if(count == 6)
						{				
							ms_delay(500);
							LCD_clear();
							disp_string(1, 1, "changed password");
							EEPROM_Write_4Bytes(new_psw, 0);
							
							ms_delay(2000);
							state = ENTER_PASS;
							LCD_clear();
							count = 0;
							new_psw = 0;
						}
						else if(count < 6)
						{
							LCD_clear();
							disp_string(1, 1, "enter-6 digit");
							ms_delay(2000);
							count = 0;
							new_psw = 0;
						}
					}
				}
			break;
				
			case DISABLED:
				disp_string(1, 2, "DOOR DISABLED....");
				disp_string(2, 1, "PLZ REFER COMPNY");
				while(r_button != 'R')
				{
					buzzer_sound(5, 0xF0, 0x03);
					r_button = READ_SWITCHES();
				}
				if(r_button == 'R')
				{
					state = OLD_PASSWORD;
					reset = 1;
					LCD_clear();
				}
			break;
				
			case RESET_STATE:
				disp_string(1,3,"resetting..");
			
				EEPROM_erase_all();
				ms_delay(3000);
			
				Flag = 1;
				warning_count = 0;
				chnge_count = 0;
			
				EEPROM_Write_byte(Flag, 50,0);
				EEPROM_Write_byte(warning_count, 100, 0);
				EEPROM_Write_byte(chnge_count,150,0);
				
				ms_delay(500);
				disp_string(1, 3, "succesed..");
				ms_delay(1500);
			
				state = NEW_PASS;
				reset = 0;
				new_p = 0;
				LCD_clear();
			break;
			
			default:
				state = NEW_DEVICE;
		}
	}
}