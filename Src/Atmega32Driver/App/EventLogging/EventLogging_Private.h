/**
 * @file EventLogging_Private.h
 * @author Team5 (Maryam)
 * @brief
 * @version 0.1
 * @date 2026-08-28
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef EVENTLOGGING_PRIVATE
#define EVENTLOGGING_PRIVATE

#include <stdint.h>

/* One log record = 2 bytes: [EventType][SequenceNumber].
 * A real timestamp isn't available (no RTC in the hardware table), so a
 * wrapping sequence number is stored instead -- it still gives a
 * meaningful ordering of events for the UART dump / audit trail.
 */
#define EventLogging_RecordSize 2U

/* 64-byte region (0x50-0x8F per SystemMap.h) / 2 bytes per record */
#define EventLogging_MaxRecords ((SystemMap_EE_LogRegionEnd - SystemMap_EE_LogRegionStart) / EventLogging_RecordSize)

/* EEPROM address just past the log region, used to persist the circular
 * write-index across power cycles (1 byte).
 * NOTE: this uses 1 byte at address 0x90, just past the README's
 * documented 0x50-0x90 log region. If the team has already reserved 0x90
 * onward for something else, move this constant and flag it in the
 * team doc -- it's the only address this module uses outside 0x50-0x8F.
 */
#define EventLogging_EE_IndexAddr SystemMap_EE_LogRegionEnd

#endif /* EVENTLOGGING_PRIVATE */
