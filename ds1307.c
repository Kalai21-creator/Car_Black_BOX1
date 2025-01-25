/* 
 * File:   ds1307.c
 * Author: kalaivanan D
 * Description : function of ds1307(RTC)  */
#include "main.h"
#include "ds1307.h"
#include "i2c.h"
#include <xc.h>

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */

void init_ds1307(void)
{
	unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy | 0x80); 

	/* Seting 12 Hr Format */
	dummy = read_ds1307(HOUR_ADDR);
	write_ds1307(HOUR_ADDR, dummy | 0x40); 

	/* 
	 * Control Register of DS1307
	 * Bit 7 - OUT
	 * Bit 6 - 0
	 * Bit 5 - OSF
	 * Bit 4 - SQWE
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1
	 * Bit 0 - RS0
	 * 
	 * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
	 */
    
	write_ds1307(CNTL_ADDR, 0x93); 

	/* Clearing the CH bit of the RTC to Start the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy & 0x7F); 

}

// Function to write data to DS1307 RTC chip via I2C
void write_ds1307(unsigned char address, unsigned char data) {
  // Start I2C transmission
  i2c_start();
  
  // Send slave device write command (SLAVE_WRITE = 0xD0)
  i2c_write(SLAVE_WRITE);
  
  // Write register address to access in DS1307
  i2c_write(address);
  
  // Write data to the specified register address
  i2c_write(data);
  
  // Stop I2C transmission
  i2c_stop();
}
// Function to read data from DS1307 RTC chip via I2C
unsigned char read_ds1307(unsigned char address) {
  unsigned char data;
  
  // Start I2C transmission
  i2c_start();
  
  // Send slave device write command (SLAVE_WRITE = 0xD0) to set register address
  i2c_write(SLAVE_WRITE);
  
  // Write register address to access in DS1307
  i2c_write(address);
  
  // Restart I2C transmission as read operation
  i2c_rep_start();
  
  // Send slave device read command (SLAVE_READ = 0xD1)
  i2c_write(SLAVE_READ);
  
  // Read data from the specified register address
  data = i2c_read();
  
  // Stop I2C transmission
  i2c_stop();
  
  // Return the read data
  return data;
}
