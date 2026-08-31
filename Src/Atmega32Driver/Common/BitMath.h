/**
 * @file BitMath.h
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief 
 * @version 0.2
 * @date 2026-08-28
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _COMMON_BITMATH_H
#define _COMMON_BITMATH_H

/* BUG FIX: the previous version of ReadBit had no parentheses around its
 * expansion:
 *     #define ReadBit(Reg,BitNo)  (Reg>>BitNo)&0x01
 * In C, "==" binds TIGHTER than "&". So any use like
 *     if (ReadBit(ADCSRA_Reg, Bit_ADIF) == 0)
 * expanded to:
 *     if ((ADCSRA_Reg >> Bit_ADIF) & 0x01 == 0)
 * which the compiler parses as:
 *     if ((ADCSRA_Reg >> Bit_ADIF) & (0x01 == 0))   // == (...) & 0
 * That is ALWAYS false, no matter what the actual bit value is -- the
 * comparison silently never triggers. Every "wait until bit clears"
 * style loop built on this macro was broken (e.g. the ADC polling wait).
 * Comparisons against 1 happened to still work by coincidence (0x01==1
 * evaluates to the constant 1, which masks correctly by accident), which
 * is exactly why this went unnoticed.
 *
 * Fix: wrap the whole macro body, and every argument, in parentheses.
 * This is standard, mandatory macro-safety practice (and a MISRA rule)
 * for exactly this reason -- it prevents operator-precedence surprises
 * no matter how the macro result gets used by the caller.
 */
#define SetBit(Reg,BitNo)       ((Reg) |= (uint8_t)(1U << (BitNo)))
#define ClearBit(Reg,BitNo)     ((Reg) &= (uint8_t)(~(1U << (BitNo))))
#define ToggleBit(Reg,BitNo)    ((Reg) ^= (uint8_t)(1U << (BitNo)))
#define ReadBit(Reg,BitNo)      (uint8_t)(((Reg) >> (BitNo)) & 0x01U)

#endif /* _COMMON_BITMATH_H */
