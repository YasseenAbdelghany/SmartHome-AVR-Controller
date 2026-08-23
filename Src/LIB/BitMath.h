/**
 * @file BitMath.h
 * @author Hesham Ahmed (Hisham4Ahmed@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-08-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef _COMMON_BITMATH_H
#define _COMMON_BITMATH_H

#define SetBit(Reg,BitNo)       Reg|=(1<<BitNo)
#define ClearBit(Reg,BitNo)     Reg&=~(1<<BitNo)
#define ToggleBit(Reg,BitNo)    Reg^=(1<<BitNo)
#define ReadBit(Reg,BitNo)      (Reg>>BitNo)&0x01

#endif /**/