#ifndef __BSP_H__
#define __BSP_H__

#include <stdint.h>

/* System clock tick [Hz]. */
#define BSP_TICKS_PER_SEC 1000U

void BSP_init(void);

void BSP_ledBlueOn(void);
void BSP_ledBlueOff(void);

void BSP_ledGreenOn(void);
void BSP_ledGreenOff(void);

void BSP_TestPinHigh(void);
void BSP_TestPinLow(void);

#endif // __BSP_H__
