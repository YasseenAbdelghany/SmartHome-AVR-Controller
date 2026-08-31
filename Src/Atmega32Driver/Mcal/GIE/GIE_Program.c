
#include "GIE_Interface.h"

void GIE_Enable()
{
    SetBit(SREG_Reg,GIEPin);
}
void GIE_Disable()
{
    ClearBit(SREG_Reg,GIEPin);
}