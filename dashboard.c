
/* 
 * File:   dashboard.c
 * Author: kalaivanan D
 * Description : function of dashboard */
#include "main.h"
unsigned char address = 0;
extern char time[9];
/* Function to store data into EEPROM */
void store_eeprom(char *time, char speed, char ev[][3], char row)
{
    char arr[10];  // Temporary array to hold data to be written to EEPROM

    // Check if the EEPROM address exceeds the maximum limit (90 bytes)
    if (address > 90)
    {
        // Perform a circular overwrite by shifting data by 10 bytes
        for (address = 0; address < 90; address++)
        {
            write_eeprom(address, read_eeprom(address + 10));  // Overwrite older data
        }
    }

    // Format the data to be stored in EEPROM
    arr[0] = time[0];            // Hours tens
    arr[1] = time[1];            // Hours units
    arr[2] = time[3];            // Minutes tens
    arr[3] = time[4];            // Minutes units
    arr[4] = time[6];            // Seconds tens
    arr[5] = time[7];            // Seconds units
    arr[6] = ev[row][0];         // Event code first character
    arr[7] = ev[row][1];         // Event code second character
    arr[8] = speed / 10 + '0';   // Speed tens
    arr[9] = speed % 10 + '0';   // Speed units

    // Write the formatted data to the EEPROM
    for (int i = 0; i < 10; i++)
    {
        write_eeprom(address + i, arr[i]);
    }

    // Update the EEPROM address for the next write
    address = address + 10;
}

/* Function to handle the Dashboard functionality */
void Dashboard(char key, State *current_state)
{
    unsigned short adc_reg_val;  // ADC register value for speed measurement
    char speed;                  // Speed value calculated from ADC reading
    char speed_str[3];           // Speed string for display
    char ev[9][3] = {            // Array of event codes
        "ON", "GR", "GN", "G1", "G2", "G3", "G4", "G5", "CO"
    };
    static char row = 0;         // Current row selection for the event

    // Read ADC value from channel 4 to calculate speed
    adc_reg_val = read_adc(CHANNEL4);
    speed = (adc_reg_val / 10.33);  // Convert ADC value to speed

    // Handle event row logic when the last row is selected (row = 8)
    if (row == 8)
    {
        if (key == SW1 || key == SW2)  // Check for SW1 or SW2 keypress
        {
            row = 2;                  // Reset to row 2
            store_eeprom(time, speed, ev, row);  // Store updated event and speed in EEPROM
        }
    }
    else if (key == SW1)  // Increment row for SW1 keypress
    {
        if (row <= 6)
        {
            row++;
        }
        store_eeprom(time, speed, ev, row);
    }
    else if (key == SW2)  // Decrement row for SW2 keypress
    {
        if (row > 1)
        {
            row--;
        }
        store_eeprom(time, speed, ev, row);
    }
    else if (key == SW3)  // Select row 8 for SW3 keypress
    {
        row = 8;
        store_eeprom(time, speed, ev, row);
    }
    else if (key == SW4)  // Navigate to menu for SW4 keypress
    {
        *current_state = e_menu;  // Update state to menu
        CLEAR_DISP_SCREEN;        // Clear the display screen
        return;
    }

    // Format the speed value into a string
    speed_str[0] = (speed / 10) + '0';  // Speed tens
    speed_str[1] = (speed % 10) + '0';  // Speed units
    speed_str[2] = '\0';                // Null terminator

    // Display the dashboard content on the CLCD
    clcd_print("Time      EV  SP", LINE1(0));  // Header on line 1
    clcd_print(time, LINE2(0));                // Display time on line 2
    clcd_print(speed_str, LINE2(14));          // Display speed on line 2 at position 14
    clcd_print(ev[row], LINE2(10));            // Display event code on line 2 at position 10
}
