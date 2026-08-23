#ifndef _SYSTEMCONFIG_PRIVATE_H
#define _SYSTEMCONFIG_PRIVATE_H

typedef enum
{
    CFG_MODE_MANUAL = 0,
    CFG_MODE_AUTO   = 1
} CFG_SystemMode_t;

typedef enum
{
    CFG_ALARM_DISABLED = 0,
    CFG_ALARM_ENABLED  = 1
} CFG_AlarmState_t;

typedef enum
{
    CFG_MENU_ROOT,
    CFG_MENU_PASSWORD,
    CFG_MENU_TEMP,
    CFG_MENU_LIGHT,
    CFG_MENU_ALARM,
    CFG_MENU_MODE
} CFG_MenuState_t;

#endif /*_SYSTEMCONFIG_PRIVATE_H*/
