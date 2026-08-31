#ifndef KEYPAD_INTERFACE
#define KEYPAD_INTERFACE

#include <stdint.h>
#include "../../Common/BitMath.h"
#include "../../Common/Definition.h"
#include "../../Mcal/DIO/DIO_Interface.h"

#include "KeyPad_Private.h"
#include "KeyPad_Config.h"

/** @brief Configure row pins as outputs (idle High) and column pins as inputs with internal pull-ups. */
void KPD_Init();

/**
 * @brief Scan the keypad once and return whichever key is currently held
 *        down, or KPD_NotPressed if none is. Non-blocking -- does not
 *        debounce or wait for release; call this periodically from the
 *        APP layer's scheduler tick and do edge-detection/debounce there
 *        (compare this tick's result to the previous tick's), consistent
 *        with the rest of this project's non-blocking real-time design.
 * @return uint8_t The character for the pressed key (per KPD_ButtonValue
 *                 in KeyPad_Config.h), or KPD_NotPressed (0xFF).
 */
uint8_t KPD_GetPressedKey(void);
#endif /* KEYPAD_INTERFACE */
