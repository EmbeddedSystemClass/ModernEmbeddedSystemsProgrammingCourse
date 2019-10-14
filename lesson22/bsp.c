/* Board Support Package (BSP) for the STM32VLDISCOVERY board */
#include <stdint.h>  /* Standard integers. WG14/N843 C99 Standard */

#include "bsp.h"
#include "stm32f10x.h" /* Device Peripheral Access Layer. */
#include "system_stm32f10x.h"

/* On-board LEDs. */
#define LED_BLUE  8
#define LED_GREEN 9

static uint32_t volatile l_tickCtr;

/******************************************************************************/
void SysTick_Handler(void)
/******************************************************************************/
{
   ++l_tickCtr;
}

/******************************************************************************/
void BSP_init(void)
/******************************************************************************/
{
    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOC clock.  */
    GPIOC->CRH    = (0x01U << 0) | /* GPIOC8 as PP output. */
                    (0x01U << 4);  /* GPIOC9 as PP output. */

    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

    __enable_irq();
}

/******************************************************************************/
uint32_t BSP_tickCtr(void)
/******************************************************************************/
{
    uint32_t tickCtr;

    __disable_irq();
    tickCtr = l_tickCtr;
    __enable_irq();

    return tickCtr;
}

/******************************************************************************/
void BSP_delay(uint32_t ticks)
/******************************************************************************/
{
    uint32_t start = BSP_tickCtr();

    while ((BSP_tickCtr() - start) < ticks)
    {
    }
}

/******************************************************************************/
void BSP_ledBlueOn(void)
/******************************************************************************/
{
    GPIOC->BSRR = 1U << LED_BLUE;
}

/******************************************************************************/
void BSP_ledBlueOff(void)
/******************************************************************************/
{
    GPIOC->BRR = 1U << LED_BLUE;
}

/******************************************************************************/
void BSP_ledGreenOn(void)
/******************************************************************************/
{
    GPIOC->BSRR = 1U << LED_GREEN;
}

/******************************************************************************/
void BSP_ledGreenOff(void)
/******************************************************************************/
{
    GPIOC->BRR = 1U << LED_GREEN;
}

/******************************************************************************/
void Q_onAssert(char const *module, int loc)
/******************************************************************************/
{
    /* TBD: damage control. */
    (void)module; /* Avoid the "unused parameter" compiler warning. */
    (void)loc;    /* Avoid the "unused parameter" compiler warning. */
    NVIC_SystemReset();
}
