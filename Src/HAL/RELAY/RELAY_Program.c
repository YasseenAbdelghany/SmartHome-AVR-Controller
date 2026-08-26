#include "RELAY_Interface.h"

/* RAM cache: lets RELAY_GetState() answer instantly without re-reading DIO */
static RELAY_State_t RELAY_ChannelState[RELAY_TOTAL_COUNT];

/*API's*/
void RELAY_Init(void)
{
    uint8_t Index;

    DIO_DirectionSelectforPin(RELAY_FAN_GROUP, RELAY_FAN_PIN, DIO_Outputfor1Pin);
    DIO_WritePin(RELAY_FAN_GROUP, RELAY_FAN_PIN, DIO_Lowfor1Pin);

    DIO_DirectionSelectforPin(RELAY_DOORLOCK_GROUP, RELAY_DOORLOCK_PIN, DIO_Outputfor1Pin);
    DIO_WritePin(RELAY_DOORLOCK_GROUP, RELAY_DOORLOCK_PIN, DIO_Lowfor1Pin);

    for (Index = 0u; Index < (uint8_t)RELAY_TOTAL_COUNT; Index++)
    {
        RELAY_ChannelState[Index] = RELAY_OFF;
    }
}

void RELAY_SetState(const RELAY_Channel_t Channel, const RELAY_State_t State)
{
    if (Channel < RELAY_TOTAL_COUNT)
    {
        switch (Channel)
        {
        case RELAY_FAN:
            DIO_WritePin(RELAY_FAN_GROUP, RELAY_FAN_PIN,
                         (State == RELAY_ON) ? DIO_Highfor1Pin : DIO_Lowfor1Pin);
            break;

        case RELAY_DOOR_LOCK:
            DIO_WritePin(RELAY_DOORLOCK_GROUP, RELAY_DOORLOCK_PIN,
                         (State == RELAY_ON) ? DIO_Highfor1Pin : DIO_Lowfor1Pin);
            break;

        default:
            /* Invalid Channel */
            break;
        }

        RELAY_ChannelState[Channel] = State;
    }
    else
    {
        /* Invalid Channel */
    }
}

RELAY_State_t RELAY_GetState(const RELAY_Channel_t Channel)
{
    RELAY_State_t LocalState = RELAY_OFF;

    if (Channel < RELAY_TOTAL_COUNT)
    {
        LocalState = RELAY_ChannelState[Channel];
    }
    else
    {
        /* Invalid Channel */
    }

    return LocalState;
}
