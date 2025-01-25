/* 
 * File:   settime.c
 * Author: kalaivanan D
 * Description : function of settime */
#include "main.h"

extern char time[9];
unsigned char hour, min, sec;
unsigned char flag = 0;
unsigned char field = 0;
unsigned long delay;
/* 
 * Function to set the time on the DS1307 RTC using key inputs.
 * This function allows the user to modify the time (HH:MM:SS) by incrementing hours, minutes, or seconds 
 * using the keypad and also select which part of the time to modify (hour, minute, or second).
 */
void settime(char key, State *current_state)
{
    /* Initialize the hour, minute, and second values from the current time string on the display */
    if (flag == 0)
    {
        // Extract hour, minute, and second values from the 'time' array
        hour = time[0] - '0';
        hour = hour * 10 + time[1] - '0';
        min = time[3] - '0';
        min = min * 10 + time[4] - '0';
        sec = time[6] - '0';
        sec = sec * 10 + time[7] - '0';
        flag = 1;  // Set flag to prevent reinitialization
    }

    /* Handle key press for adjusting the time */
    if (key == SW1)
    {
        if (field == 0)  // If the field is hour
        {
            // Increment hour and roll over after 23
            if (hour++ == 23)
            {
                hour = 0;  // Reset hour to 0 if it exceeds 23
            }
        }
        if (field == 1)  // If the field is minute
        {
            // Increment minute and roll over after 59
            if (min++ == 59)
            {
                min = 0;  // Reset minute to 0 if it exceeds 59
            }
        }
        if (field == 2)  // If the field is second
        {
            // Increment second and roll over after 59
            if (sec++ == 59)
            {
                sec = 0;  // Reset second to 0 if it exceeds 59
            }
        }
    }
    
    /* Handle key press for switching between hour, minute, or second field */
    if (key == SW2)
    {
        // Move to the next field (hour -> minute -> second -> hour)
        if (field++ == 2)
        {
            field = 0;  // If at second, reset to hour
        }
    }

    /* Save the modified time to the DS1307 RTC when SW4 is pressed */
    if (key == SW4)
    {
        // Convert hours, minutes, and seconds to BCD format and write to RTC
        hour = ((hour / 10) << 4) | (hour % 10);
        write_ds1307(HOUR_ADDR, hour);

        min = ((min / 10) << 4) | (min % 10);
        write_ds1307(MIN_ADDR, min);

        sec = ((sec / 10) << 4) | (sec % 10);
        write_ds1307(SEC_ADDR, sec);

        *current_state = e_menu;  // Transition to menu state
        flag = 0;  // Reset flag
        return;
    }

    /* If SW5 is pressed, exit to menu */
    if (key == SW5)
    {
        *current_state = e_menu;  // Return to menu state
        flag = 0;  // Reset flag
        return;
    }

    /* Display time in the format HH:MM:SS and highlight the currently selected field */
    clcd_print(" HH:MM:SS ", LINE1(0));

    /* Create a delay effect on the display update */
    if (delay++ < 500)
    {
        // Display time with the selected field highlighted
        clcd_putch(' ', LINE2(0));
        clcd_putch('0' + hour / 10, LINE2(1));
        clcd_putch('0' + hour % 10, LINE2(2));
        clcd_putch(':', LINE2(3));
        clcd_putch('0' + min / 10, LINE2(4));
        clcd_putch('0' + min % 10, LINE2(5));
        clcd_putch(':', LINE2(6));
        clcd_putch('0' + sec / 10, LINE2(7));
        clcd_putch('0' + sec % 10, LINE2(8));
    }
    else
    {
        // Highlight the currently active field (hour, minute, or second)
        if (field == 0)  // If hour field is active
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch(' ', LINE2(1));
            clcd_putch(' ', LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch('0' + min / 10, LINE2(4));
            clcd_putch('0' + min % 10, LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch('0' + sec / 10, LINE2(7));
            clcd_putch('0' + sec % 10, LINE2(8));
        }
        else if (field == 1)  // If minute field is active
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch('0' + hour / 10, LINE2(1));
            clcd_putch('0' + hour % 10, LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch(' ', LINE2(4));
            clcd_putch(' ', LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch('0' + sec / 10, LINE2(7));
            clcd_putch('0' + sec % 10, LINE2(8));
        }
        else if (field == 2)  // If second field is active
        {
            clcd_putch(' ', LINE2(0));
            clcd_putch('0' + hour / 10, LINE2(1));
            clcd_putch('0' + hour % 10, LINE2(2));
            clcd_putch(':', LINE2(3));
            clcd_putch('0' + min / 10, LINE2(4));
            clcd_putch('0' + min % 10, LINE2(5));
            clcd_putch(':', LINE2(6));
            clcd_putch(' ', LINE2(7));
            clcd_putch(' ', LINE2(8));
        }
    }

    /* Reset the delay counter after a certain period */
    if (delay == 1000)
    {
        delay = 0;
    }
}
