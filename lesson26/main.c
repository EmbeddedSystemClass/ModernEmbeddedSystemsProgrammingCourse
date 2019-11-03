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
void spin_loop(unsigned int loop_count);

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    __disable_irq();

    BSP_init();
    OS_init(stack_idleThread, sizeof(stack_idleThread));

#if 1
    OSThread_start(&blinky1,
        5U,
        main_blinky1,
        stack_blinky1,
        sizeof(stack_blinky1));
#endif

#if 1
    OSThread_start(&blinky2,
        2U,
        main_blinky2,
        stack_blinky2,
        sizeof(stack_blinky2));
#endif

    OS_run();

    //return 0;
}

/******************************************************************************/
void main_blinky1(void)
/******************************************************************************/
{
    while (1)
    {
#if 1
        /* C = ~1.2 ms, T = 2.0 ms. */

        for (int volatile i = 0; i < 59; ++i)
        {
            BSP_ledBlueOn();
            spin_loop(21U);
            BSP_ledBlueOff();
            spin_loop(20U);
        }

        OS_delay(1);
#else
        BSP_ledBlueOn();
        BSP_ledBlueOff();
#endif
    }
}

/******************************************************************************/
void main_blinky2(void)
/******************************************************************************/
{
    while (1)
    {
#if 1
        /* C = ~2.2 ms, T = 40.0 ms. */

        for (int volatile i = 0; i < 108; ++i)
        {
            BSP_ledGreenOn();
            spin_loop(21U);
            BSP_ledGreenOff();
            spin_loop(20U);
        }

        OS_delay(36);
#else
        BSP_ledGreenOn();
        BSP_ledGreenOff();
#endif
    }
}

/******************************************************************************/
void spin_loop(unsigned int loop_count)
/******************************************************************************/
{
    for (unsigned int volatile cnt = 0U; cnt < loop_count; ++cnt)
    {
        /* Intentionally empty. */
    }
}
