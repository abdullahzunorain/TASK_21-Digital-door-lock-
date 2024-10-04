#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H
#include <reg52.h>

sbit Servo_motor_Pin = P2^0;     // Define a bit for the servo motor control pin

void Timer0_Intilization (void);

void set_servomoter_position (float duty_cycle);

#endif