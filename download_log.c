/* 
 * File:   downloadlog.c
 * Author: kalaivanan D
 * Description : function of downloadlog  */
#include "main.h"
extern unsigned char address;
/* Function to download and display the log from EEPROM */
void downloadlog(State *current_state)
{
    static unsigned char index = 0;  // Static variable to keep track of the current log entry
    char arr[20];                    // Array to store a formatted log entry for transmission

    // Print the header for the log display
    puts("# Time     EV SP \n\r");

    // Loop through each log entry stored in the EEPROM
    while (index < (address / 10))  // Each log entry occupies 10 bytes in EEPROM
    {
        // Format the log entry
        arr[0] = index + '0';                       // Entry number (index)
        arr[1] = ' ';                               // Space separator
        arr[2] = read_eeprom((index * 10));         // Hours tens
        arr[3] = read_eeprom((index * 10) + 1);     // Hours units
        arr[4] = ':';                               // Colon separator
        arr[5] = read_eeprom((index * 10) + 2);     // Minutes tens
        arr[6] = read_eeprom((index * 10) + 3);     // Minutes units
        arr[7] = ':';                               // Colon separator
        arr[8] = read_eeprom((index * 10) + 4);     // Seconds tens
        arr[9] = read_eeprom((index * 10) + 5);     // Seconds units
        arr[10] = ' ';                              // Space separator
        arr[11] = read_eeprom((index * 10) + 6);    // Event code first character
        arr[12] = read_eeprom((index * 10) + 7);    // Event code second character
        arr[13] = ' ';                              // Space separator
        arr[14] = read_eeprom((index * 10) + 8);    // Speed tens
        arr[15] = read_eeprom((index * 10) + 9);    // Speed units
        arr[16] = '\n';                             // Newline character
        arr[17] = '\r';                             // Carriage return
        arr[18] = '\0';                             // Null terminator

        // Send the formatted log entry over the serial interface
        puts(arr);

        // Increment the index to process the next log entry
        index++;
    }

    // Add a delay for user readability
    for (unsigned long wait = 500000; wait--;);

    // Update the current state to menu
    *current_state = e_menu;

    // Reset the index for future log downloads
    index = 0;

    return;
}
