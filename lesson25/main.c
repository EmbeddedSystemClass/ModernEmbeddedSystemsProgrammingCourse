#include <stdint.h>
#include "miros.h"
#include "bsp.h"

uint32_t stack_blinky1[40];
OSThread blinky1;
uint32_t stack_blinky2[40];
OSThread blinky2;

uint32_t stack_idleThread[40];

void main_blinky1(void);
void main_blinky2(void);

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    __disable_irq();

    BSP_init();
    OS_init(stack_idleThread, sizeof(stack_idleThread));

    OSThread_start(&blinky1,
        main_blinky1,
        stack_blinky1,
        sizeof(stack_blinky1));

    OSThread_start(&blinky2,
        main_blinky2,
        stack_blinky2,
        sizeof(stack_blinky2));

    OS_run();

    //return 0;
}

/******************************************************************************/
void main_blinky1(void)
/******************************************************************************/
{
    while (1)
    {
        BSP_ledGreenOn();
        OS_delay(BSP_TICKS_PER_SEC * 1U / 8U);
        BSP_ledGreenOff();
        OS_delay(BSP_TICKS_PER_SEC * 7U / 8U);
    }
}

/******************************************************************************/
void main_blinky2(void)
/******************************************************************************/
{
    while (1)
    {
        BSP_ledBlueOn();
        OS_delay(BSP_TICKS_PER_SEC * 1U / 4U);
        BSP_ledBlueOff();
        OS_delay(BSP_TICKS_PER_SEC * 3U / 4U);
    }
}
