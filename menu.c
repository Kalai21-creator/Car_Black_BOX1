/* 
 * File:   menu.c
 * Author: kalaivanan D
 * Description : function of menu */
#include "main.h"
/* Function to handle the menu navigation and state transitions */
void menu(char key, State *current_state)
{
    // Menu options stored in a static 2D array (each option has a length of 16 characters)
    static char menu[][16] = {"View_log    ", "Download_log", "Clear_log", "Set_time"};
    static char m_ind = 0;  // Index to track the current menu option
    static char s_flag = 0;  // Flag to track if the user is in selection mode (s_flag == 1)

    /* If SW1 (Up) button is pressed */
    if (key == SW1)
    {
        // If not at the top of the menu and not in selection mode (s_flag == 0), move up
        if (m_ind > 0 && s_flag == 0)
        {
            m_ind--;  // Move up in the menu
            CLEAR_DISP_SCREEN;  // Clear the screen to refresh the menu display
        }
        // If in selection mode (s_flag == 1), exit selection mode
        if (s_flag == 1)
        {
            s_flag = 0;
        }
    }

    /* If SW2 (Down) button is pressed */
    if (key == SW2)
    {
        // If not at the bottom of the menu and in selection mode (s_flag == 1), move down
        if (m_ind < 2 && s_flag == 1)
        {
            m_ind++;  // Move down in the menu
            CLEAR_DISP_SCREEN;  // Clear the screen to refresh the menu display
        }
        // If not in selection mode, enter selection mode
        if (s_flag == 0)
        {
            s_flag = 1;
        }
    }

    /* If SW4 (Select) button is pressed */
    if (key == SW4)
    {
        // If not in selection mode (s_flag == 0), transition to the selected state based on m_ind
        if (s_flag == 0)
        {
            // Depending on the selected menu option, change the state and clear the screen
            if (m_ind == 0)
            {
                *current_state = e_viewlog;  // Transition to view log state
                CLEAR_DISP_SCREEN;
                return;
            }
            else if (m_ind == 1)
            {
                *current_state = e_downloadlog;  // Transition to download log state
                CLEAR_DISP_SCREEN;
                return;
            }
            else if (m_ind == 2)
            {
                *current_state = e_clearlog;  // Transition to clear log state
                CLEAR_DISP_SCREEN;
                return;
            }
        }
        // If in selection mode (s_flag == 1), transition to the next state based on the menu option
        else
        {
            if (m_ind + 1 == 1)
            {
                *current_state = e_downloadlog;  // Transition to download log state
                CLEAR_DISP_SCREEN;
                return;
            }
            else if (m_ind + 1 == 2)
            {
                *current_state = e_clearlog;  // Transition to clear log state
                CLEAR_DISP_SCREEN;
                return;
            }
            else if (m_ind + 1 == 3)
            {
                *current_state = e_settime;  // Transition to set time state
                CLEAR_DISP_SCREEN;
                return;
            }
        }
    }

    /* If SW5 (Back) button is pressed */
    if (key == SW5)
    {
        // Reset menu and return to the dashboard
        CLEAR_DISP_SCREEN;  // Clear the screen
        m_ind = 0;  // Reset the menu index to the first option
        s_flag = 0;  // Reset the selection mode flag
        *current_state = e_Dashboard;  // Transition to the dashboard state
        return;
    }

    /* Display the current menu option */
    if (s_flag == 0)
    {
        // Display a '*' symbol on the left side of the screen to indicate the current selection
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));
    }
    else
    {
        // Display a '*' symbol on the right side of the screen to indicate the selection in progress
        clcd_putch(' ', LINE1(0));
        clcd_putch('*', LINE2(0));
    }

    // Print the current and next menu options on the LCD
    clcd_print(menu[m_ind], LINE1(1));  // Display the selected menu option on line 1
    clcd_print(menu[m_ind + 1], LINE2(1));  // Display the next menu option on line 2
}
