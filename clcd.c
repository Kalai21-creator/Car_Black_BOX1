
/* 
 * File:   clcd.c
 * Author: kalaivanan D
 * Description : function of clcd display */
#include <xc.h>
#include "clcd.h"
/* Function to write data or commands to the CLCD */
void clcd_write(unsigned char byte, unsigned char control_bit)
{
    // Set the Register Select (RS) pin based on control_bit (Data or Instruction)
    CLCD_RS = control_bit;

    // Place the data/command on the CLCD data port
    CLCD_PORT = byte;

    // Generate a high-to-low pulse on Enable (EN) pin for data/command latch
    CLCD_EN = HI;   // Enable high
    CLCD_EN = LO;   // Enable low

    // Set the port direction as input to read the busy flag
    PORT_DIR = INPUT;

    // Set the Read/Write (RW) pin to read mode
    CLCD_RW = HI;

    // Clear the RS pin for instruction command mode
    CLCD_RS = INSTRUCTION_COMMAND;

    // Wait until the CLCD is no longer busy
    do
    {
        CLCD_EN = HI;   // Enable high
        CLCD_EN = LO;   // Enable low
    } while (CLCD_BUSY); // Check busy flag

    // Reset the RW pin to write mode
    CLCD_RW = LO;

    // Set the port direction back to output
    PORT_DIR = OUTPUT;
}

/* Function to initialize the CLCD */
void init_clcd()
{
    // Configure PortD as output for CLCD data lines
    TRISD = 0x00;

    // Configure PortC bits for CLCD control lines as output
    TRISC = TRISC & 0xF8;

    // Set the Read/Write (RW) pin to write mode
    CLCD_RW = LO;

    // Allow startup time for the CLCD controller
    __delay_ms(30);

    // Initialization sequence for the CLCD
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);  // Set 8-bit mode
    __delay_us(4100);                                 // Wait for the command to execute
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);  // Repeat command
    __delay_us(100);                                  // Wait for the command to execute
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);  // Repeat command
    __delay_us(1);                                    // Wait for the command to execute

    // Set cursor to the home position
    CURSOR_HOME;
    __delay_us(100);

    // Configure display for 2 lines, 5x8 character matrix, and 8-bit mode
    TWO_LINE_5x8_MATRIX_8_BIT;
    __delay_us(100);

    // Clear the display screen
    CLEAR_DISP_SCREEN;
    __delay_us(500);

    // Turn on display and turn off cursor
    DISP_ON_AND_CURSOR_OFF;
    __delay_us(100);
}

/* Function to print a string of characters on the CLCD */
void clcd_print(const unsigned char *data, unsigned char addr)
{
    // Set the CLCD address for writing
    clcd_write(addr, INSTRUCTION_COMMAND);

    // Write characters one by one until the null terminator is encountered
    while (*data != '\0')
    {
        clcd_write(*data++, DATA_COMMAND);  // Write each character as data
    }
}

/* Function to write a single character to a specific address on the CLCD */
void clcd_putch(const unsigned char data, unsigned char addr)
{
    // Set the CLCD address for writing
    clcd_write(addr, INSTRUCTION_COMMAND);

    // Write the character data to the CLCD
    clcd_write(data, DATA_COMMAND);
}
