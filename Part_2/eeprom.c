#include <reg51.h>
#include "main.h"
//ddelay for I2c
#define I2C_ddelay    50
//Define Led Toggle Time
#define TOGGLE_LED  20000
//control address of 24lc64
#define device_addr 0xA0
#define ACK_BIT    0
//Define the Pin for the I2c and lec

/*=========================================
   Prototypes for I2c functions
 ==========================================*/

/*=========================================
   Definition of I2c functions
 ==========================================*/
/**
\brief of  ddelay function.
This function provide the ddelay which is used in clock generation.
*/
void ddelay(unsigned int d)
{
    unsigned int i;
    for(i=0; i<d; i++);
}
/**
\brief of InitI2c function.
This function  use to make the data line and clock line idle to put the both line high
*/
void InitI2c(void)
{
    SDA_BUS =1;
    SCL_BUS =1;
}
/**
\brief of StartI2c function.
This function performs the start operation to initiate the communication.
*/
void StartI2c(void)
{
    SDA_BUS  = 1;
    SCL_BUS  = 1;
    ddelay(I2C_ddelay);
    SDA_BUS  = 0;
    ddelay(I2C_ddelay);
}
/**
\brief of void RepeatedStartI2c function.
When master does not want to relaese the control from the bus then it assert the repeated
start condition on the i2c bus.
*/
void RepeatedStartI2c()
{
    SCL_BUS  = 0;
    ddelay(I2C_ddelay/2);
    SDA_BUS  = 1;
    ddelay(I2C_ddelay/2);
    SCL_BUS  = 1;
    ddelay(I2C_ddelay/2);
    SDA_BUS  = 0;
    ddelay(I2C_ddelay);
}
/**
\brief of void StopI2c function.
When master want to stop the communication then it will assert the stop condition to the i2c bus.
*/
void StopI2c(void)
{
    SCL_BUS  = 0;
    ddelay(I2C_ddelay/2);
    SDA_BUS  = 0;
    ddelay(I2C_ddelay/2);
    SCL_BUS  = 1;
    ddelay(I2C_ddelay/2);
    SDA_BUS  = 1;
    ddelay(I2C_ddelay);
}
/**
\brief of  SendAckBit function.
This function use to send the acknoledgement(ACK) bit the i2c bus.
*/
void SendAckBit()
{
    SCL_BUS  = 0;
    ddelay(I2C_ddelay/2);
    SDA_BUS  = 0;
    ddelay(I2C_ddelay/2);
    SCL_BUS  = 1;
    ddelay(I2C_ddelay);
}
/**
\brief of  SendNackBit function.
This function use to send the Non-acknoledgement(NACK) bit the i2c bus.
*/
void SendNackBit(void)
{
    SCL_BUS  = 0;
    ddelay(I2C_ddelay/2);
    SDA_BUS  = 1;
    ddelay(I2C_ddelay/2);
    SCL_BUS  = 1;
    ddelay(I2C_ddelay);
}
/**
\brief of write_i2c function.
This function use to send signle byte to the I2C Data Bus
*/
bit write_i2c(unsigned char byte)
{
    unsigned char i;
    for(i=0; i<8; i++)
    {
        SCL_BUS  = 0;
        ddelay(I2C_ddelay);
        if((byte<<i)&0x80)
            SDA_BUS  = 1;
        else
            SDA_BUS  = 0;
        ddelay(I2C_ddelay/2);
        SCL_BUS  = 1;
        ddelay(I2C_ddelay);
    }
//ack from slave //
    SCL_BUS  = 0;
    SDA_BUS  = 0;
    ddelay(I2C_ddelay/2);
    SCL_BUS  = 1;
    ddelay(I2C_ddelay);
    return SDA_BUS;
}
/**
\brief of write_i2c function.
This function use to read the data from the I2C data bus
*/
unsigned char read_i2c(void)
{
    unsigned char i,d, rxdata=0;
    for(i=0; i<8; i++)
    {
        SCL_BUS  = 0;
        SDA_BUS  = 1;
        ddelay(I2C_ddelay);
        SCL_BUS  = 1;
        ddelay(I2C_ddelay/2);
        d=SDA_BUS;
        rxdata=rxdata|(d<<7-i);
        ddelay(I2C_ddelay);
    }
    return rxdata;
}
/**
\brief of write_byte_to_eeprom function.
This function use to single byte the eeprom at desire address
*///Write Data to eeprom memory
void write_byte_to_eeprom(unsigned int addr,unsigned char byte)
{
    StartI2c();
    while(write_i2c(device_addr|0)==1)
    {
        StartI2c();
    }
    write_i2c(addr>>8);
    write_i2c((unsigned char)addr);
    write_i2c(byte);
    StopI2c();
}
/**
\brief of read_byte_from_eeprom function.
This function use to read the data byte from eeprom at the desire the address
*/
unsigned char read_byte_from_eeprom(unsigned int addr)
{
    unsigned char rxdata =0;
    StartI2c();
    while(write_i2c(device_addr|0)==1)
    {
        StartI2c();
    }
    write_i2c(addr>>8);
    write_i2c((unsigned char)addr);
    RepeatedStartI2c();
    write_i2c(device_addr|1);
    rxdata=read_i2c();
    SendNackBit();
    StopI2c() ;
    return rxdata;
}
// Main function
