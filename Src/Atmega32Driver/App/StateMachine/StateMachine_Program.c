/**
 * @file StateMachine_Program.c
 * @author Team1 -- Smart Home Controller
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "StateMachine_Interface.h"

static SM_State_t SM_CurrentState        = SM_StateLogin;
static uint8_t    SM_u8PreviousKey       = KPD_NotPressed;
static uint8_t    SM_au8PasswordEntry[SystemMap_EE_PasswordLength];
static uint8_t    SM_u8PasswordEntryIdx  = 0U;

static void SM_vidShowLoginScreen(void)
{
    LCD_MoveTo(0U,0U);
    LCD_WriteString((uint8_t*)"Enter Password: ");
    LCD_MoveTo(1U,0U);
    LCD_WriteString((uint8_t*)"                ");
    SM_u8PasswordEntryIdx = 0U;
}

static void SM_vidShowMainMenu(void)
{
    LCD_MoveTo(0U,0U);
    if(CFG_GetSystemMode()==CFG_ModeAuto)
    {
        LCD_WriteString((uint8_t*)"Mode: AUTO      ");
    }
    else
    {
        LCD_WriteString((uint8_t*)"Mode: MANUAL    ");
    }
    LCD_MoveTo(1U,0U);
    LCD_WriteString((uint8_t*)"*Mode /Ctrl C:Out");
}

static void SM_vidShowManualControl(void)
{
    LCD_MoveTo(0U,0U);
    LCD_WriteString((uint8_t*)"1Lt 2Fan 3Door 4Al");
    LCD_MoveTo(1U,0U);
    LCD_WriteString((uint8_t*)"C:Back          ");
}

void SM_Init(void)
{
    SM_CurrentState = SM_StateLogin;
    SM_vidShowLoginScreen();
}

void SM_MainFunction(void)
{
    uint8_t Local_u8Key = KPD_GetPressedKey();

    /* Simple edge detection: only act the moment a key transitions from
     * "not this key" to "this key" -- holding it down does not repeat.
     */
    if((Local_u8Key!=KPD_NotPressed) && (Local_u8Key!=SM_u8PreviousKey))
    {
        if(SM_CurrentState==SM_StateLogin)
        {
            if(Local_u8Key==(uint8_t)'C')
            {
                SM_u8PasswordEntryIdx = 0U;
            }
            else if((Local_u8Key>=(uint8_t)'0') && (Local_u8Key<=(uint8_t)'9')
                    && (SM_u8PasswordEntryIdx<SystemMap_EE_PasswordLength))
            {
                SM_au8PasswordEntry[SM_u8PasswordEntryIdx] = Local_u8Key;
                SM_u8PasswordEntryIdx++;

                if(SM_u8PasswordEntryIdx>=SystemMap_EE_PasswordLength)
                {
                    AUTH_Result_t Local_Result = AUTH_VerifyPassword(SM_au8PasswordEntry);

                    if(Local_Result==AUTH_Success)
                    {
                        SM_CurrentState = SM_StateMainMenu;
                        SM_vidShowMainMenu();
                    }
                    else if(Local_Result==AUTH_LockedOut)
                    {
                        LCD_MoveTo(1U,0U);
                        LCD_WriteString((uint8_t*)"LOCKED OUT!     ");
                        SM_u8PasswordEntryIdx = 0U;
                    }
                    else
                    {
                        LCD_MoveTo(1U,0U);
                        LCD_WriteString((uint8_t*)"WRONG, RETRY    ");
                        SM_u8PasswordEntryIdx = 0U;
                    }
                }
                else
                {
                    // still collecting digits
                }
            }
            else
            {
                // key not relevant on the Login screen
            }
        }
        else if(SM_CurrentState==SM_StateMainMenu)
        {
            if(Local_u8Key==(uint8_t)'*')
            {
                if(CFG_GetSystemMode()==CFG_ModeManual)
                {
                    CFG_SetSystemMode(CFG_ModeAuto);
                }
                else
                {
                    CFG_SetSystemMode(CFG_ModeManual);
                }
                LOG_Event(EVENT_MODE_CHANGED);
                SM_vidShowMainMenu();
            }
            else if(Local_u8Key==(uint8_t)'/')
            {
                SM_CurrentState = SM_StateManualControl;
                SM_vidShowManualControl();
            }
            else if(Local_u8Key==(uint8_t)'C')
            {
                SM_CurrentState = SM_StateLogin;
                SM_vidShowLoginScreen();
            }
            else
            {
                // key not relevant on the Main Menu
            }
        }
        else if(SM_CurrentState==SM_StateManualControl)
        {
            if(Local_u8Key==(uint8_t)'1')
            {
                ModeCtrl_ManualToggleDevice(MODE_DeviceRoomLight);
            }
            else if(Local_u8Key==(uint8_t)'2')
            {
                ModeCtrl_ManualToggleDevice(MODE_DeviceFan);
            }
            else if(Local_u8Key==(uint8_t)'3')
            {
                ModeCtrl_ManualToggleDevice(MODE_DeviceDoorLock);
            }
            else if(Local_u8Key==(uint8_t)'4')
            {
                ModeCtrl_ManualToggleDevice(MODE_DeviceAlarmToggle);
            }
            else if(Local_u8Key==(uint8_t)'C')
            {
                SM_CurrentState = SM_StateMainMenu;
                SM_vidShowMainMenu();
            }
            else
            {
                // key not relevant in Manual Control
            }
        }
        else
        {
            // Unknown state: no action
        }
    }
    else
    {
        // no new key press this tick
    }

    SM_u8PreviousKey = Local_u8Key;
}
