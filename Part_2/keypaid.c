#include<reg51.h>
#include "main.h"
extern char pin[] ;
extern char Epin[5];
extern char state;
unsigned char op=0,cv=0;
void delay(unsigned int j)
{
    int a, b;
    for (a = 0; a < 2*j; a++)
    {
        for (b = 0; b < 10; b++);
    }
}
char keypad()
{
    int x = 0;
    while (x == 0)
    {
        // assign values for first row
        keyrow1 = 0;
        keyrow2 = 1;
        keyrow3 = 1;
        keyrow4 = 1;
        if (keycolumn1 == 0)
        {
            lcd_write('#');
            delay(1000);
            x = 1;
            return '#';
        }
				    if (keycolumn2 == 0)
        {
            lcd_write('#');
            delay(1000);
            x = 1;
            return '#';
        }
   
        if (keycolumn3 == 0)
        {
            lcd_write('8');
            delay(1000);
            x = 1;
            return 8;
        }
				 if (keycolumn4 == 0)
        {
            lcd_write('4');
            delay(1000);
            x = 1;
            return 4;
        }
        // assign values for second row
        keyrow1 = 1;
        keyrow2 = 0;
        keyrow3 = 1;
        keyrow4 = 1;

        if (keycolumn1 == 0)
        {
            lcd_write('0');
            delay(1000);
            x = 1;
            return 0;
        }
           if (keycolumn2 == 0)
        {
            lcd_write('#');
            delay(1000);
            x = 1;
            return '#';
        }
        if (keycolumn3 == 0)
        {
            lcd_write('7');
            delay(1000);
            x = 1;
            return 7;
        }
        	 if (keycolumn4 == 0)
        {
            lcd_write('3');
            delay(1000);
            x = 1;
            return 3;
        }
        // assign values for third row
        keyrow1 = 1;
        keyrow2 = 1;
        keyrow3 = 0;
        keyrow4 = 1;
        if (keycolumn1 == 0)
        {
            lcd_write('9');
            delay(1000);
            x = 1;
            return 9;
        }
            if (keycolumn2 == 0)
        {
            lcd_write('#');
            delay(1000);
            x = 1;
            return '#';
        }
        if (keycolumn3 == 0)
        {
            lcd_write('6');
            delay(1000);
            x = 1;
            return 6;
        }
        	 if (keycolumn4 == 0)
        {
            lcd_write('2');
            delay(1000);
            x = 1;
            return 2;
        }
        // assign values for forth row
        keyrow1 = 1;
        keyrow2 = 1;
        keyrow3 = 1;
        keyrow4 = 0;

        if (keycolumn1 == 0)
        {  cv++;
					if(cv>5)
				  {	delay(7000);
						state=3;
					op=1;
						  x = 1;
           }
					if(cv<5)
					{   delay(7000);
	         
            x = 1;
					}
           
        }
              if (keycolumn2 == 0)
        {
            lcd_write('#');
            delay(1000);
            x = 1;
            return '#';
        }
        if (keycolumn3 == 0)
        {
            lcd_write('5');
            delay(1000);
            x = 1;
            return 5;
        }
					 if (keycolumn4 == 0)
        {
            lcd_write('1');
            delay(1000);
            x = 1;
            return 1;
        }
    }
	return 0;
}
