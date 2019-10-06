#include <stdint.h> /* The most important addition to C99! */
#include "stm32f10x.h"
#include "delay.h"

void SysTick_Handler(void);

#define PIN8 (1U << 8)
#define PIN9 (1U << 9)

/******************************************************************************/
void main(void)
/******************************************************************************/
{
    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOF clock.  */
    GPIOC->CRH    = (0x01U << 0) | /* GPIOC8 as PP output. */
                    (0x01U << 4);  /* GPIOC9 as PP output. */

    GPIOC->ODR |=  PIN8;
    GPIOC->ODR &= ~PIN9;

    SysTick->LOAD = (8000000U - 1U);
    SysTick->CTRL = (1U << 2) | (1U << 1) | (1U << 0);

    while (1)
    {
        asm("nop");
    }
}

/******************************************************************************/
void SysTick_Handler(void)
/******************************************************************************/
{
    GPIOC->ODR ^= PIN8;
    GPIOC->ODR ^= PIN9;
}
