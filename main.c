/* 
 * File:   main.c
 * Author: kalaivanan D
 * Description : function of main  */
#include "main.h"

unsigned char clock_reg[3];
char time[9];
unsigned char hour, min, sec;
/* Function to initialize all system configurations */
static void init_config(void)
{
    init_clcd();   // Initialize the character LCD (CLCD) display
    init_adc();    // Initialize the ADC (Analog to Digital Converter)
    init_mkp();    // Initialize the matrix keypad (MKP)
    init_uart();   // Initialize the UART (Universal Asynchronous Receiver-Transmitter)
    init_i2c();    // Initialize the I2C communication protocol
    init_ds1307(); // Initialize the DS1307 real-time clock (RTC)
}

/* Main function where the program execution begins */
void main(void)
{
    init_config();   // Initialize all the system components
    unsigned char key;  // Variable to store the key pressed from the keypad
    State current_state = e_Dashboard;  // Initialize the system state to Dashboard

    /* Main loop to continuously check for user input and process the current state */
    while (1)
    {
        get_time();  // Get the current time from the DS1307 RTC

        key = read_matrix_keypad(STATE);  // Read the key pressed from the keypad

        /* State Machine: Switch between different states based on the current state */
        if (current_state == e_Dashboard)
        {
            Dashboard(key, &current_state);  // Call Dashboard function for state e_Dashboard
        }
        else if (current_state == e_menu)
        {
            menu(key, &current_state);  // Call menu function for state e_menu
        }
        else if (current_state == e_viewlog)
        {
            viewlog(key, &current_state);  // Call viewlog function for state e_viewlog
        }
        else if (current_state == e_downloadlog)
        {
            downloadlog(&current_state);  // Call downloadlog function for state e_downloadlog
        }
        else if (current_state == e_clearlog)
        {
            clearlog(&current_state);  // Call clearlog function for state e_clearlog
        }
        else if (current_state == e_settime)
        {
            settime(key, &current_state);  // Call settime function for state e_settime
        }
    }

    return;
}

/* Function to read the current time from the DS1307 RTC */
static void get_time(void)
{
    /* Read the current hour, minute, and second from the DS1307 RTC */
    clock_reg[0] = read_ds1307(HOUR_ADDR);  // Read the hour register
    clock_reg[1] = read_ds1307(MIN_ADDR);   // Read the minute register
    clock_reg[2] = read_ds1307(SEC_ADDR);   // Read the second register

    /* Convert the hour from binary-coded decimal (BCD) format to ASCII */
    if (clock_reg[0] & 0x40)  // Check if the hour is in 12-hour format
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);  // Get tens place of hour
        time[1] = '0' + (clock_reg[0] & 0x0F);           // Get ones place of hour
    }
    else  // If in 24-hour format
    {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);  // Get tens place of hour
        time[1] = '0' + (clock_reg[0] & 0x0F);           // Get ones place of hour
    }

    /* Convert the minutes and seconds from BCD format to ASCII */
    time[2] = ':';  // Colon separator
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);  // Get tens place of minutes
    time[4] = '0' + (clock_reg[1] & 0x0F);         // Get ones place of minutes
    time[5] = ':';  // Colon separator
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);  // Get tens place of seconds
    time[7] = '0' + (clock_reg[2] & 0x0F);         // Get ones place of seconds

    time[8] = '\0';  // Null terminator for the time string
}
