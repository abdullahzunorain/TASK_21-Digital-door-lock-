
#include "EEPROM.h" 
#include "LCD.h"      

unsigned long counter = 0;

void us_delay(unsigned int k)
{
	while(k--);
}


void EEPROM_Init(void)
{
    EEPROM_SDA = 1; 		// Set SDA high.
    EEPROM_SCL = 1; 		// Set SCL high.
}


void EEPROM_Start()
{
    EEPROM_SCL = 0; 	// Set SCL low.
    us_delay(1);			 // Small delay.
    
    EEPROM_SCL = 1;		 // Set SCL high.
    us_delay(1); 				// Small delay.
    
    EEPROM_SDA = 0;		 // Set SDA low to indicate the start condition.
    us_delay(1); 				// Small delay.
    
    EEPROM_SCL = 0;		 // Set SCL low to prepare for data transfer.
}


void EEPROM_Stop(void)
{
    EEPROM_SCL = 0; 		// Set SCL low.
    us_delay(1);				 // Small delay.
    
    EEPROM_SDA = 0; 		// Set SDA low to indicate the stop condition.
    us_delay(1); 			// Small delay.
    
    EEPROM_SCL = 1; 		// Set SCL high.
    us_delay(1); 				// Small delay.
    
    EEPROM_SDA = 1;			 // Set SDA high.
}


void EEPROM_ACK(void)
{
    EEPROM_SDA = 0; 		// Set SDA low to send ACK.
    us_delay(1); 				// Small delay.
    
    EEPROM_SCL = 1; 		// Set SCL high to acknowledge.
    us_delay(1); 				// Small delay.
    
    EEPROM_SCL = 0; 			// Set SCL low.
    EEPROM_SDA = 1; 			// Set SDA high.
}


void EEPROM_nACK(void)
{
    EEPROM_SDA = 1; 		// Set SDA high to send NACK.
    us_delay(1);				 // Small delay.
    
    EEPROM_SCL = 1; 		// Set SCL high.
    us_delay(1); 				// Small delay.
    
    EEPROM_SCL = 0; 		// Set SCL low.
    EEPROM_SDA = 1; 		// Set SDA high.
}


void EEPROM_send(unsigned char Data)
{
    unsigned char i;
    for (i = 0; i < 8; i++)
    {
        EEPROM_SDA = Data & 0x80; 	// Set SDA according to the MSB of 'Data'.
        EEPROM_SCL = 1;							 // Set SCL high to send the bit.
        EEPROM_SCL = 0;						 // Set SCL low to prepare for the next bit.
        Data <<= 1;							 // Shift 'Data' left to get the next bit.
    }
    EEPROM_ACK();						 // Send ACK after sending the byte.
}


unsigned char EEPROM_Recev(void)
{
    unsigned char i, Data = 0;
    for (i = 0; i < 8; i++)
    {
        us_delay(1);				 // Small delay to stabilize the data.
        EEPROM_SCL = 1; 			// Set SCL high to read the bit from SDA.
        Data |= EEPROM_SDA; 		// Read the bit and store it in 'Data'.
        if (i < 7)
            Data <<= 1;				 // Shift 'Data' left to make space for the next bit.
        EEPROM_SCL = 0; 			// Set SCL low to prepare for the next bit.
    }
    return Data; 						// Return the received byte.
}


void EEPROM_Write_byte(unsigned char Data, unsigned char adrs, unsigned char page)
{
    EEPROM_Start(); 										// Start EEPROM communication.
    
    EEPROM_send(0xA0 | (page << 1)); 		// Send device address with page.
    EEPROM_send(adrs);									 // Send the memory address to write.
    EEPROM_send(Data); 									// Send the data to be written.
    
    EEPROM_Stop(); 										// Stop EEPROM communication.
    ms_delay(5); 											// Delay for EEPROM write cycle completion.
}


unsigned char EEPROM_Read_byte(unsigned char adrs, unsigned char page)
{
    unsigned char Data;
    
    EEPROM_Start();									 // Start EEPROM communication.
    
    EEPROM_send(0xA0 | (page << 1)); 		// Send device address with page for writing.
    EEPROM_send(adrs);								 // Send the memory address to read from.
    
    EEPROM_Start(); 										// Restart EEPROM communication.
    
    EEPROM_send(0xA1 | (page << 1)); 			// Send device address with page for reading.
    Data = EEPROM_Recev();							// Receive the data from EEPROM.
    
    EEPROM_nACK();											 // Send NACK to end the read operation.
    EEPROM_Stop(); 											// Stop EEPROM communication.
    us_delay(10); 											
    
    return Data; 												// Return the read data.
}

void EEPROM_Write_4Bytes(unsigned long counterValue, unsigned char startingAddress)
{
	unsigned int c;
    for (c = 0; c < 4; c++)
    {
        unsigned char byteValue = (counterValue >> (8 * c)) & 0xFF;
        EEPROM_Write_byte(byteValue, startingAddress + c, 0); // Starting address + i for consecutive memory locations
    }
}


unsigned long EEPROM_Read_4Bytes(unsigned char startingAddress)
{
	unsigned int d;
    unsigned long counterValue = 0;
    for (d = 0; d < 4; d++)
    {
        unsigned char byteValue = EEPROM_Read_byte(startingAddress + d, 0); // Starting address + i for consecutive memory locations
        counterValue |= ((unsigned long)byteValue << (8 * d));
    }
    return counterValue;
}