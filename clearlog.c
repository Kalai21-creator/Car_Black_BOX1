/* 
 * File:   clearlog.c
 * Author: kalaivanan D
 * Description : function of clearlog  */
#include "main.h"

/* External declarations for variables used in the function */
extern unsigned char address;  // Address pointer for log storage or retrieval
extern char index;             // Index pointer for log entries

/* Function to clear the log and update the state */
void clearlog(State *current_state)
{
    // Display a success message on the CLCD
    clcd_print("clear success   ", LINE1(0));  // Print message on line 1
    clcd_print("                ", LINE2(0));  // Clear line 2 for a clean display

    // Delay for a brief moment to allow the user to read the message
    for (unsigned long wait = 500000; wait--;);

    // Reset the log address and index to the initial values
    address = 0;
    index = 0;

    // Update the current state to the menu state
    *current_state = e_menu;

    // Return from the function
    return;
}
