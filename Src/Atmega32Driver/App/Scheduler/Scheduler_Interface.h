/**
 * @file Scheduler_Interface.h
 * @author Team6 (Khaled)
 * @brief Non-blocking cooperative task scheduler on top of Timer0's 1ms
 *        tick. This is the entire body of main()'s while(1) loop -- the
 *        real-time, no-blocking-delays backbone the whole project's
 *        non-functional requirements are built around.
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef SCHEDULER_INTERFACE
#define SCHEDULER_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/Timer0/T0_Interface.h"
#include "Scheduler_Private.h"
#include "Scheduler_Config.h"

/** @brief Start Timer0's 1ms tick. Call once from main(), before registering tasks. */
void SCHED_Init(void);

/**
 * @brief Get the current tick count in milliseconds since SCHED_Init().
 */
uint32_t SCHED_GetTickCount(void);

/**
 * @brief Non-blocking replacement for a delay: true once at least
 *        DurationMs milliseconds have passed since StartTick. Use this
 *        instead of _delay_ms() anywhere in the real-time loop.
 */
uint8_t SCHED_CheckElapsed(uint32_t StartTick, uint32_t DurationMs);

/**
 * @brief Register a function to be called every PeriodMs milliseconds.
 * @return uint8_t Task ID, or SCHED_INVALID_TASK_ID if the task table is full.
 */
uint8_t SCHED_RegisterTask(Sched_TaskFunc_t TaskFunc, uint32_t PeriodMs);

/**
 * @brief Run one pass over the task table, calling any task whose period
 *        has elapsed. This is the entire body of main()'s while(1) loop.
 */
void SCHED_MainFunction(void);

#endif /* SCHEDULER_INTERFACE */
