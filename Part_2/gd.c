#include <reg51.h>
#include <stdlib.h>
#include <intrins.h>
#include "main.h"
unsigned char pin[5] ;
unsigned char Epin[5];
unsigned char serial_values[5]={0},aa,bb,cc,dd,ee,vj=0,g;
extern unsigned char op;
extern unsigned char cv;
unsigned int i=0,count=0,k,j,v,j,z,tt;
unsigned long x,y,total,jk;
unsigned char Mystring[]="DEAR EMPLOYES YOUR PASSWORD IS  ",u;
sbit btn=P3^1;
unsigned char array[10]={'\0','\0','\0','\0','\0'};  
unsigned char state=0;
//https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-srand-set-seed-rand-function
//https://embetronicx.com/tutorials/microcontrollers/8051/8051-i2c-interfacing-tutorial-eeprom/

void serial_data(void)
	{
	 for(z=0;z<6;z++)
	 {
	 SBUF= Mystring[z];
		 while(TI==0);
		  TI=0;
	    delay1(100);
	 }
 }

 void write_number_on_lcd(unsigned long digit)  
 {  
      char count;  
      unsigned long int constant=1;  
   
      if(digit==0)  
      {  
            LCD_Command(48); 
          LCD_Command(1);  				
           return;  
      }  
        
      for(;digit>=constant;constant*=10)  
           count++;  
      count--;  
      for(;count>=0;count--)  
      {  
           array[count]=digit%10+48;  
           digit/=10;  
      }  
      lcd_string(array);  
 }


/**
void eeprom (void)
{
    unsigned char rxbyte=0;
    unsigned char cSendByte = v;
 
    SDA_BUS = 0;
    SCL_BUS = 0;
    InitI2c();
    write_byte_to_eeprom(0x0001,pin[5]);
    rxbyte=read_byte_from_eeprom(0x0001);

    
       
    
} 
	*/


	
void timer(int msec)	 // Function for timer
{
	int i;
	TR1=1;
	for(i=0;i<msec;i++)
	{
		while(TF1==0);
		TF1=0;
	}
	TR1=0;
}





	

void main()
{
		IE=0x82; // enable timer 0 interrupt and serial interrupt
	TMOD=0x02; 		// Mode2

	TH0= -23;	
   SDA_BUS = 0;
    SCL_BUS = 0;
    InitI2c();
   
   lcd_init();

y=rand()+100000;
write_byte_to_eeprom(0x001,y);

write_number_on_lcd(y);
	



while(1)
{	
  
	
switch (state)
	{

  case 0:
		
	
            	 TMOD=0x20;
              	TH1=0xFD;
	             SCON=0x50;
	              TR1=1;
	              for(u=0;u<39;u++)
	              {
                	SBUF=Mystring[u];
                	while(TI==0);
                 	TI=0;}
	             for(u=0;u<14;u++)
	               {
               	SBUF=array[u];
	               while(TI==0);
                	TI=0;}
	            state++;
	  break;
  case 1:
		
			LCD_Command (0x01);	/* clear display */
      password();
			LCD_Command (0x01);	/* clear display */
    break;
	case 2:
		g++;
		if(g<2)
		{			
	    	LCD_Command (0x02);	
		    lcd_string ("KEYPAID");
	      LCD_Command (0xC0);	
			 lcd_string (" DISABLED ");}
			 	buzzer_pin=1;
				delay1(2);
			  buzzer_pin=0;
			  delay1(1);
			 buzzer_pin=1;
			  if(btn==0)
         { state=3;
         }
			
		break;
	case 3:
	        	if(vj<3)
		{
			cv=0;
		    LCD_Command (0x02);	
	  LCD_Command (0x01);	
		
			 lcd_string ("PASSWORD CHANGE");
				delay(1000);
			  LCD_Command (0xC0);	
			  lcd_string  ("    MOOD    ");
				delay(10000);
	         LCD_Command (0x01);
			 lcd_string ("Enter old pass ");
			op=0;
	         LCD_Command (0xC0);	
	          call();
	        if(y==total)
					{
					 LCD_Command (0x01);	
					 lcd_string ("Enter new pass ");
						 LCD_Command (0xC0);
					 delay1(100);
						call();
						y=total;
						v=0;
					g=0;
					}
					else
					{
						vj++;
					 LCD_Command (0x01);	
						 lcd_string (" WRONG PASSWORD ");
						 LCD_Command (0x01);	
					   lcd_string("Pass change ");
						 LCD_Command (0xC0);	
						  lcd_string("Wrong Attempt ");
						   x = 1;
             lcd_write(vj+48);
					delay(10000);
						state=1;
						 LCD_Command (0x01);	
		         	if(vj==3)
		          	{
			      	state=2;
              	}
									v=0;
		 			}
	         		g=0;
	           state=1;
				}
		else
	   	{
		 lcd_string ("KEYPAID DISABLE");
	      LCD_Command (0xC0);	
			 lcd_string (" PERMANENT  ");
	   	}
		break;
				
  }
}
}
 
  

void call()
{         tt=keypad();
	 if(op==0)
				{
          aa = keypad();
	      
	        bb = keypad();
         	cc = keypad();
	        dd = keypad();
	        ee = keypad();
           total=tt*100000+aa*10000+bb*1000+cc*100+dd*10+ee;}
}
void password()
{

 lcd_string ("ENTER GATE PASS");
  LCD_Command(0xc0); //decimal value: 192
      if(btn==0)
         { state=3;
         }
              	call();
				 if(op==0)
				 {
	           x=total;
				   if(btn==0)
         { state=3;
         }
            delay(1000);
  

 check();

			 }





}


	
void check()
{
    
 if (y==x)
    {
        delay(1000);
        LCD_Command(0x01);
        LCD_Command(0x81); 

        lcd_string("PIN CORRECT");
					
						for(k=0;k<60;k++)
		      {
						
				 		output=1;
					
		      timer(120);		 
			      output=0;
						   
		 
			   timer(720);
				
		
		     state=1;
					}
					for(j=0;j<1200;j++)
				
		       {
		          	buzzer_pin=1;
				    	 delay1(2);
					      buzzer_pin=0;
						 delay1(1);
					}
					buzzer_pin=1;
        LCD_Command(0xc1);
        lcd_string("DOOR OPENED");
        	for(k=0;k<60;k++)
		      {
						
				 		output=1;
		    	 timer(23);		 
			      output=0;
			     timer(360);
						j=0;
					}
     state=1;
       
    }
    else
    {
			
			v++;
       LCD_Command(0x01); 
       LCD_Command(0x80); 
       lcd_string("WRONG PIN");
       delay(100);
			 LCD_Command(0xc0); 
		   lcd_string("Wrong Attempt ");
      lcd_write(v+48);
			write_byte_to_eeprom(0x002,v);
			 state=1;
			 //  	savee();
			if(v==3)
			{
				state=2;
						LCD_Command (0x01);	/* clear display */
	
			}
			 delay(10000);
			 
     
    }
	}


void deelay(unsigned char p,unsigned char q)
{
TMOD=0x01;  //timer0 mode1(16 bit)
TL0=q;      //load TL0
TH0=p;      //load TH0
TR0=1;   //turn on T0
while(TF0==0); // wait for flag generation
TR0=0;   // turn off T0
TF0=0;    // clear TF0
}

void play(unsigned char j,unsigned char k)
{
int i;
for(i=0;i<1000;i++)  //to play sound
{
  buzzer_pin=1;
  deelay(j,k);
  buzzer_pin=0;
  deelay(j,k);
}
}

