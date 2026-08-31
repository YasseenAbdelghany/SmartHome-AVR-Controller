/**
 * @file Scheduler_Private.h
 * @author Team6 (Khaled)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef SCHEDULER_PRIVATE
#define SCHEDULER_PRIVATE

#include <stdint.h>

typedef void (*Sched_TaskFunc_t)(void);

typedef struct
{
    Sched_TaskFunc_t Func;
    uint32_t         PeriodMs;
    uint32_t         LastRunTick;
    uint8_t          IsUsed;
}Sched_Task_t;

#define SCHED_INVALID_TASK_ID 0xFFU

/* 1ms tick via Timer0 CTC, 8MHz/64 prescaler:
 *   8,000,000 / 64 = 125,000 timer ticks/sec -> 125 ticks per 1ms
 *   OCR0 = 125 - 1 = 124
 * If F_CPU (Common/Definition.h) changes, recompute this by hand.
 */
#define SCHED_TickOCR0Value 124U

#endif /* SCHEDULER_PRIVATE */
