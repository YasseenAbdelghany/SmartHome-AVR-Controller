#include "LED_Interface.h"

/* RAM cache: lets LED_GetState() answer instantly without re-reading DIO */
static LED_State_t LED_ChannelState[LED_TOTAL_COUNT];

/*API's*/
void LED_Init(void)
{
    uint8_t Index;

    DIO_DirectionSelectforPin(LED_ROOM_LIGHT_GROUP, LED_ROOM_LIGHT_PIN, DIO_Outputfor1Pin);
    DIO_WritePin(LED_ROOM_LIGHT_GROUP, LED_ROOM_LIGHT_PIN, DIO_Lowfor1Pin);

    for (Index = 0u; Index < (uint8_t)LED_TOTAL_COUNT; Index++)
    {
        LED_ChannelState[Index] = LED_OFF;
    }
}

void LED_SetState(const LED_Channel_t Channel, const LED_State_t State)
{
    if (Channel < LED_TOTAL_COUNT)
    {
        switch (Channel)
        {
        case LED_ROOM_LIGHT:
            DIO_WritePin(LED_ROOM_LIGHT_GROUP, LED_ROOM_LIGHT_PIN,
                         (State == LED_ON) ? DIO_Highfor1Pin : DIO_Lowfor1Pin);
            break;

        default:
            /* Invalid Channel */
            break;
        }

        LED_ChannelState[Channel] = State;
    }
    else
    {
        /* Invalid Channel */
    }
}

LED_State_t LED_GetState(const LED_Channel_t Channel)
{
    LED_State_t LocalState = LED_OFF;

    if (Channel < LED_TOTAL_COUNT)
    {
        LocalState = LED_ChannelState[Channel];
    }
    else
    {
        /* Invalid Channel */
    }

    return LocalState;
}
