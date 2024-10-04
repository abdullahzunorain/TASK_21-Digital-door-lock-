//#include "KEY_PAD.h"
//#include "LCD.h"

//unsigned char READ_SWITCHES(void)
//{
//	row_1 = 0; row_2 = 1; row_3 = 1; row_4 = 1;
//	if (C1 == 0) { ms_delay(100); while (C1==0); return '/'; } 
//	if (C2 == 0) { ms_delay(100); while (C2==0); return '9'; } 
//	if (C3 == 0) { ms_delay(100); while (C3==0); return '8'; } 
//	if (C4 == 0) { ms_delay(100); while (C4==0); return '7'; }
//	
//	row_1 = 1; row_2 = 0; row_3 = 1; row_4 = 1;
//	
//	if (C1 == 0) { ms_delay(100); while (C1==0); return 'x'; } 
//	if (C2 == 0) { ms_delay(100); while (C2==0); return '6'; } 
//	if (C3 == 0) { ms_delay(100); while (C3==0); return '5'; } 
//	if (C4 == 0) { ms_delay(100); while (C4==0); return '4'; }
//	
//	row_1 = 1; row_2 = 1; row_3 = 0; row_4 = 1;
//	
//	if (C1 == 0) { ms_delay(100); while (C1==0); return '-'; } 
//	if (C2 == 0) { ms_delay(100); while (C2==0); return '3'; } 
//	if (C3 == 0) { ms_delay(100); while (C3==0); return '2'; } 
//	if (C4 == 0) { ms_delay(100); while (C4==0); return '1'; }
//	
//	row_1 = 1; row_2 = 1; row_3 = 1; row_4 = 0;
//	
//	if (C1 == 0) { ms_delay(100); while (C1==0); return '+'; } 
//	if (C2 == 0) { ms_delay(100); while (C2==0); return '='; } 
//	if (C3 == 0) { ms_delay(100); while (C3==0); return '0'; } 
//	if (C4 == 0) { ms_delay(100); while (C4==0); return 'c'; }
//	return 'n';
//}

////void Disp_Error(unsigned int numb)           //displays differet error messages
////{
////	set_cursor(2,3);
////	switch(numb)
////	{
////	case 0: 	disp_string("INPUT ERROR");   break;
////	case 1: 	disp_string("FUNCN ERROR");   break;
////	case 2: 	disp_string("MATH ERROR");    break;
////	default:    disp_string("MATH ERROR");  break;
////	}
////}

////unsigned char get_button_pressed(void)           //get key from user
////{
////	char key = 'n';              //assume no key pressed

////	while(key=='n')              //wait untill a key is pressed
////		key = READ_SWITCHES();   //scan the keys again and again

////	return key;                  //when key pressed then return its value
////}

////unsigned int get_number_pressed(unsigned char ch)         //convert char into int
////{
////	switch(ch)
////	{
////		case '0': return 0; break;
////		case '1': return 1; break;
////		case '2': return 2; break;
////		case '3': return 3; break;
////		case '4': return 4; break;
////		case '5': return 5; break;
////		case '6': return 6; break;
////		case '7': return 7; break;
////		case '8': return 8; break;
////		case '9': return 9; break;
////		default: return 0;
////	}
////}