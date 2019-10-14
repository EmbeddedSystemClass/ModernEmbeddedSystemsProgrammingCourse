#include <stdint.h>
#include "miros.h"
#include "bsp.h"

uint32_t stack_blinky1[40];
OSThread blinky1;
uint32_t stack_blinky2[40];
OSThread blinky2;

void main_blinky1(void);
void main_blinky2(void);

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    uint32_t volatile run = 0U;
    __disable_irq();

    BSP_init();
    OS_init();

    OSThread_start(&blinky1,
        main_blinky1,
        stack_blinky1,
        sizeof(stack_blinky1));

    OSThread_start(&blinky2,
        main_blinky2,
        stack_blinky2,
        sizeof(stack_blinky2));

    while (1)
    {
        /* Loop forever. */
        ++run;
    }

    //return 0;
}

/******************************************************************************/
void main_blinky1(void)
/******************************************************************************/
{
    while (1)
    {
        BSP_ledGreenOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledGreenOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}

/******************************************************************************/
void main_blinky2(void)
/******************************************************************************/
{
    while (1)
    {
        BSP_ledBlueOn();
        BSP_delay(BSP_TICKS_PER_SEC / 4U);
        BSP_ledBlueOff();
        BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}
