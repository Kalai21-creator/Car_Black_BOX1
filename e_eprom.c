/* 
 * File:   e_eprom.c
 * Author: kalaivanan D
 * Description : function of e_eprom(AT24C02) */
#include "main.h"

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */


// Function to write data to EEPROM via I2C
void write_eeprom(unsigned char address, unsigned char data) {
  // Start I2C transmission
  i2c_start();
  
  // Send EEPROM write command (WRITE)
  i2c_write(WRITE);
  
  // Specify memory address in EEPROM to write data
  i2c_write(address);
  
  // Write actual data to the specified memory address
  i2c_write(data);
  
  // Stop I2C transmission
  i2c_stop();
  
  // Wait for EEPROM write cycle completion (approx. 3ms)
  for(int i=3000;i--;);
}
// Function to read data from EEPROM via I2C
unsigned char read_eeprom(unsigned char address) {
  unsigned char data;
  
  // Start I2C transmission
  i2c_start();
  
  // Send EEPROM write command (WRITE) to set address for reading
  i2c_write(WRITE);
  
  // Specify memory address in EEPROM to read data
  i2c_write(address);
  
  // Restart I2C transmission as read operation
  i2c_rep_start();
  
  // Send EEPROM read command (READ)
  i2c_write(READ);
  
  // Read actual data from the specified memory address
  data = i2c_read();
  
  // Stop I2C transmission
  i2c_stop();
  
  // Return the read data
  return data;
}
