/* 
 * File:   view_log.c
 * Author: kalaivanan D
 * Description : function of view_log */
#include "main.h"
extern unsigned char address;
char index = 0;
/* 
 * Function to display log entries stored in EEPROM.
 * This function allows the user to view log entries (time, event, and SP values) stored in EEPROM.
 * It supports navigation through the log entries using the keypad (SW1, SW2, SW4).
 */
void viewlog(char key, State *current_state)
{
    /* Handle key press for navigating forward in the log entries */
    if (key == SW2)
    {
        // If there are more log entries available, increment the index
        if (index < (address / 10) - 1)
            index++;  // Move to the next log entry
    }

    /* Handle key press for navigating backward in the log entries */
    if (key == SW1)
    {
        // If not at the first entry, decrement the index
        if (index > 0)
            index--;  // Move to the previous log entry
    }

    /* If there are no logs stored (address == 0), show a message and return to the menu */
    if (address == 0)
    {
        clcd_print("No Data found    ", LINE1(0));  // Display no data found message
        clcd_print("                ", LINE2(0));  // Clear second line

        // Wait for a short period before returning to the menu
        for (unsigned long wait = 500000; wait--;)
            ;

        // Transition to the menu state
        *current_state = e_menu;
        return;
    }

    /* Handle key press for returning to the menu */
    if (key == SW4)
    {
        CLEAR_DISP_SCREEN;  // Clear the display
        *current_state = e_menu;  // Transition back to the menu state
        index = 0;  // Reset the index to 0
        return;
    }

    /* Display the log entry format "# Time     EV SP" */
    clcd_print("# Time     EV SP", LINE1(0));

    /* Display the current log entry index and the log data */
    clcd_putch(index + '0', LINE2(0));  // Show the current log index
    clcd_putch(' ', LINE2(1));

    // Display the time (hours, minutes, and seconds) from EEPROM for the current log entry
    clcd_putch(read_eeprom((index * 10)), LINE2(2));  // Hour, first part
    clcd_putch(read_eeprom((index * 10) + 1), LINE2(3));  // Hour, second part
    clcd_putch(':', LINE2(4));
    clcd_putch(read_eeprom((index * 10) + 2), LINE2(5));  // Minute, first part
    clcd_putch(read_eeprom((index * 10) + 3), LINE2(6));  // Minute, second part
    clcd_putch(':', LINE2(7));
    clcd_putch(read_eeprom((index * 10) + 4), LINE2(8));  // Second, first part
    clcd_putch(read_eeprom((index * 10) + 5), LINE2(9));  // Second, second part

    clcd_putch(' ', LINE2(10));

    // Display the event (EV) and SP values from EEPROM for the current log entry
    clcd_putch(read_eeprom((index * 10) + 6), LINE2(11));  // Event, first part
    clcd_putch(read_eeprom((index * 10) + 7), LINE2(12));  // Event, second part
    clcd_putch(' ', LINE2(13));
    clcd_putch(read_eeprom((index * 10) + 8), LINE2(14));  // SP, first part
    clcd_putch(read_eeprom((index * 10) + 9), LINE2(15));  // SP, second part
}

