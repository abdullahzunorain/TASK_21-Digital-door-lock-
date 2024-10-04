#ifndef EEPROM_H
#define EEPROM_H

void EEPROM_write(unsigned char address, unsigned char dataa);
unsigned char EEPROM_read(unsigned char address);

#endif
