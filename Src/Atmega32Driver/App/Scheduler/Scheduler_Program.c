/**
 * @file Scheduler_Program.c
 * @author Team6 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "Scheduler_Interface.h"

static volatile uint32_t SCHED_u32TickCounter = 0UL;
static Sched_Task_t       SCHED_aTaskTable[SCHED_MAX_TASKS];

/**
 * @brief Timer0 Compare Match callback -- kept intentionally minimal
 *        (increment only), per the real-time non-functional requirement
 *        that ISR bodies stay short.
 */
static void SCHED_vidTickCallback(void)
{
    SCHED_u32TickCounter++;
}

void SCHED_Init(void)
{
    T0_Config_t Local_Config;
    uint8_t Local_u8Index;

    Local_Config.Prescaler     = T0_Prescaler64;
    Local_Config.Mode          = T0_CTC;
    Local_Config.OC0Mode       = T0_OC0_Disconnected;
    Local_Config.OVFInterrupt  = T0_InterruptDisable;
    Local_Config.CompInterrupt = T0_InterruptEnable;
    Local_Config.CompareValue  = SCHED_TickOCR0Value;

    T0_SetCompareCallBack(SCHED_vidTickCallback);
    T0_Init(&Local_Config);

    for(Local_u8Index=0U; Local_u8Index<SCHED_MAX_TASKS; Local_u8Index++)
    {
        SCHED_aTaskTable[Local_u8Index].Func        = (Sched_TaskFunc_t)0;
        SCHED_aTaskTable[Local_u8Index].PeriodMs    = 0UL;
        SCHED_aTaskTable[Local_u8Index].LastRunTick = 0UL;
        SCHED_aTaskTable[Local_u8Index].IsUsed      = 0U;
    }
}

uint32_t SCHED_GetTickCount(void)
{
    uint32_t Local_u32Snapshot;
    uint8_t  Local_u8SregSave = SREG_Reg;

    ClearBit(SREG_Reg,7); /* disable interrupts for an atomic 32-bit read */
    Local_u32Snapshot = SCHED_u32TickCounter;
    SREG_Reg = Local_u8SregSave; /* restore exactly as it was, not a blind re-enable */

    return Local_u32Snapshot;
}

uint8_t SCHED_CheckElapsed(uint32_t StartTick, uint32_t DurationMs)
{
    uint8_t  Local_u8Result;
    uint32_t Local_u32Elapsed = SCHED_GetTickCount()-StartTick; /* wraps correctly even on rollover */

    if(Local_u32Elapsed>=DurationMs)
    {
        Local_u8Result = 1U;
    }
    else
    {
        Local_u8Result = 0U;
    }

    return Local_u8Result;
}

uint8_t SCHED_RegisterTask(Sched_TaskFunc_t TaskFunc, uint32_t PeriodMs)
{
    uint8_t Local_u8Index;
    uint8_t Local_u8AssignedId = SCHED_INVALID_TASK_ID;
    uint8_t Local_u8Found = 0U;

    for(Local_u8Index=0U; (Local_u8Index<SCHED_MAX_TASKS) && (Local_u8Found==0U); Local_u8Index++)
    {
        if(SCHED_aTaskTable[Local_u8Index].IsUsed==0U)
        {
            SCHED_aTaskTable[Local_u8Index].Func        = TaskFunc;
            SCHED_aTaskTable[Local_u8Index].PeriodMs    = PeriodMs;
            SCHED_aTaskTable[Local_u8Index].LastRunTick = SCHED_GetTickCount();
            SCHED_aTaskTable[Local_u8Index].IsUsed      = 1U;

            Local_u8AssignedId = Local_u8Index;
            Local_u8Found = 1U;
        }
        else
        {
            // slot in use, keep searching
        }
    }

    return Local_u8AssignedId;
}

void SCHED_MainFunction(void)
{
    uint8_t Local_u8Index;

    for(Local_u8Index=0U; Local_u8Index<SCHED_MAX_TASKS; Local_u8Index++)
    {
        if(SCHED_aTaskTable[Local_u8Index].IsUsed==1U)
        {
            if(SCHED_CheckElapsed(SCHED_aTaskTable[Local_u8Index].LastRunTick,
                                   SCHED_aTaskTable[Local_u8Index].PeriodMs)==1U)
            {
                SCHED_aTaskTable[Local_u8Index].LastRunTick = SCHED_GetTickCount();
                SCHED_aTaskTable[Local_u8Index].Func();
            }
            else
            {
                // not due yet
            }
        }
        else
        {
            // empty slot
        }
    }
}
