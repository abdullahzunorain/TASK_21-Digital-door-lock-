#include "eeprom.h"
#include "i2c.h" // Include your I2C library or driver

#define EEPROM_ADDRESS 0xA0 // 7-bit I2C address of the EEPROM (adjust as needed)

// Write data to EEPROM
void EEPROM_write(unsigned char address, unsigned char data) {
    I2C_Start();                     // Send start condition
    I2C_Write(EEPROM_ADDRESS);      // Send EEPROM address
    I2C_Write(address);             // Send data address in EEPROM
    I2C_Write(data);                // Send data to be written
    I2C_Stop();                      // Send stop condition
}

// Read data from EEPROM
unsigned char EEPROM_read(unsigned char address) {
    unsigned char data;
    
    I2C_Start();                     // Send start condition
    I2C_Write(EEPROM_ADDRESS);      // Send EEPROM address
    I2C_Write(address);             // Send data address in EEPROM
    I2C_Start();                     // Restart condition
    I2C_Write(EEPROM_ADDRESS | 0x01); // Send EEPROM address for read
    data = I2C_Read();              // Read data from EEPROM
    I2C_Stop();                      // Send stop condition

    return data;                    // Return the read data
}
