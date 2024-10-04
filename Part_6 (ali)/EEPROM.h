#ifndef EEPROM_H
#define EEPROM_H
#include <reg52.h>   

sbit EEPROM_SDA = P2^0;
sbit EEPROM_SCL = P2^1;

void us_delay(unsigned int k);

void EEPROM_Init(void);

void EEPROM_Start();

void EEPROM_Stop(void);

void EEPROM_ACK(void);

void EEPROM_nACK(void);

void EEPROM_send(unsigned char Data);

unsigned char EEPROM_Recev(void);

void EEPROM_Write_byte(unsigned char Data, unsigned char adrs, unsigned char page);

unsigned char EEPROM_Read_byte(unsigned char adrs, unsigned char page);

void EEPROM_Write_4Bytes(unsigned long counterValue, unsigned char startingAddress);

unsigned long EEPROM_Read_4Bytes(unsigned char startingAddress);

void EEPROM_erase_all();

#endif