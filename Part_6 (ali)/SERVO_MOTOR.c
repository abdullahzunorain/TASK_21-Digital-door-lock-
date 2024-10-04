#include "SERVO_MOTOR.h"
#include "LCD.h"

unsigned int  ON_pulse, OFF_pulse; // Variables to store ON and OFF pulse durations for PWM
float duty_cycle;                 // Variable to store the duty cycle for PWM

void Timer0_Intilization ()     // Function to initialize Timer0 for PWM generation
{
    TMOD = 0x01;                // Timer0 in 16-bit mode 1 
    TH0 = 0xB7;                 // Initial value for Timer0 High byte
    TL0 = 0xFD;                 // Initial value for Timer0 Low byte
    TR0 = 1;                    // Start Timer0
    IE = 0x82;                  // Enable Timer0 interrupt
}

void ISR_servo_moter() interrupt 1  // Timer0 Interrupt Service Routine (ISR) for PWM generation
{ 
    Servo_motor_Pin = ~Servo_motor_Pin ; // Toggle the servo motor control pin
    
    if (Servo_motor_Pin)
    {
        TH0 = ON_pulse >> 8;    // Set high byte for ON pulse duration
        TL0 = ON_pulse;         // Set low byte for ON pulse duration
    }
    else
    {
        TH0 = OFF_pulse >> 8;   // Set high byte for OFF pulse duration
        TL0 = OFF_pulse;        // Set low byte for OFF pulse duration
    }
}

void set_servomoter_position (float angle)  // Function to calculate ON and OFF pulse durations based on duty cycle
{  
    unsigned int Period;
		duty_cycle = ((angle + 45)/180)*10;
    Period = 65535 - 0xB7FD;     										 // Total time period for PWM
    
    ON_pulse = ((Period / 100.0) * duty_cycle);   // Calculate ON pulse duration
    OFF_pulse = Period - ON_pulse;               // Calculate OFF pulse duration
    
    ON_pulse = 65535 - ON_pulse;   								// Invert ON pulse duration
    OFF_pulse = 65535 - OFF_pulse;							 // Invert OFF pulse duration
}