/**
 * @file main.c
 * @author Team4 -- Smart Home Controller
 * @brief Application entry point. Initializes every module in dependency
 *        order, registers all periodic work with the Scheduler, enables
 *        global interrupts exactly once, then hands control to the
 *        non-blocking scheduler loop for the rest of the program's life.
 * @version 1.0
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "Mcal/GIE/GIE_Interface.h"
#include "Mcal/ADC/ADC_Interface.h"

#include "App/Scheduler/Scheduler_Interface.h"
#include "App/SystemConfig/SystemConfig_Interface.h"
#include "App/EventLogging/EventLogging_Interface.h"
#include "App/AlarmSystem/AlarmSystem_Interface.h"
#include "App/Authentication/Authentication_Interface.h"
#include "App/OperatingModes/OperatingModes_Interface.h"
#include "App/RealTimeMonitor/RTM_Interface.h"
#include "App/StateMachine/StateMachine_Interface.h"
#include "Hal/LCD/LCD_Interface.h"

int main(void)
{
    ADC_Config_t Local_ADCConfig;

    /* ---- 1. MCAL initialisation ---- */
    Local_ADCConfig.Vref          = ADC_Avcc;
    Local_ADCConfig.Adjust        = ADC_RightAdjust;
    Local_ADCConfig.Prescaler     = ADC_Prescaler64;
    Local_ADCConfig.Mode          = ADC_SingleConversionMode;
    Local_ADCConfig.TriggerSource = ADC_FreeRunning;
    Local_ADCConfig.Interrupt     = ADC_InterruptDisable; /* LM35/LDR read via polling, see LM35/LDR drivers */
    Local_ADCConfig.State         = ADC_Enable;
    ADC_Init(&Local_ADCConfig);


    /* ---- 2. APP initialisation, in dependency order ---- */
    CFG_Init();        /* System Configuration -- loaded first, others read it   */
    LOG_Init();         /* Event Logging -- needed by everything below           */
    ALARM_Init();       /* Alarm System -- needed by Authentication              */
    AUTH_Init();        /* Authentication                                        */
    ModeCtrl_Init();    /* Operating Modes -- Room Light / Fan / Door outputs    */
    KPD_Init();          /* Keypad       @order check                                          */
    
    /* LCD Initialization with error detection */
    if(LCD_Init() != LCD_ERROR_NONE) {
        /* Log LCD initialization error */
        LOG_Event(EVENT_SYSTEM_BOOT); /* Use existing event system or add LCD_INIT_ERROR event */
    }
    
    RTM_Init();          /* Real-Time Monitor -- also brings up UART              */
    SM_Init();           /* Main State Machine -- shows the initial Login screen  */

    /* ---- 3. Enable global interrupts exactly once, after every module's
     *         Init() has configured its own interrupt sources (ADC, EXTI,
     *         Timer0, UART all had their individual enables set above --
     *         this is the single point that actually lets them fire).
     */
    GIE_Enable();

    LOG_Event(EVENT_SYSTEM_BOOT);

    /* ---- 4. Register all periodic work with the Scheduler ----
     * Periods are chosen so nothing does more work than it needs to:
     *   - keypad/state machine: fast enough to feel instant to a person
     *   - LCD refresh: fast enough to feel live, cheap since it only
     *     rewrites lines that actually changed
     *   - sensor-driven work (Auto mode, fire check, UART log): slower,
     *     since temperature/light don't change meaningfully every tick
     */
    SCHED_RegisterTask(SM_MainFunction,50UL);
    SCHED_RegisterTask(RTM_LCDStatusUpdate,300UL);
    SCHED_RegisterTask(ModeCtrl_AutoUpdate,750UL);
    SCHED_RegisterTask(ALARM_CheckFireCondition,1000UL);
    SCHED_RegisterTask(RTM_LogSensorReadings,1000UL);

    SCHED_Init(); /* also starts the Timer0 1ms system tick */

    /* ---- 5. Real-time loop -- this is the entire body, per the
     *         project's non-blocking non-functional requirement. No
     *         _delay_ms() anywhere in this file or in any task above.
     */
    while(1)
    {
        SCHED_MainFunction();
    }

    return 0;
}
