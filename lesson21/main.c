#include <stdint.h> /* The most important addition to C99! */
#include "stm32f10x.h"
#include "bsp.h"

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOC clock.  */
    GPIOC->CRH    = (0x01U << 0) | /* GPIOC8 as PP output. */
                    (0x01U << 4);  /* GPIOC9 as PP output. */

    GPIOC->ODR |=  PIN8;
    GPIOC->ODR &= ~PIN9;

    SysTick->LOAD = (8000000U - 1U);
    SysTick->CTRL = (1U << 2) | (1U << 1) | (1U << 0);

    SysTick_Handler();

    while (1)
    {
        GPIOC->BSRR = PIN9;
        GPIOC->BRR  = PIN9;

        //__disable_irq();
        //GPIOC->ODR = GPIOC->ODR |  PIN9;
        //__enable_irq();

        //__disable_irq();
        //GPIOC->ODR = GPIOC->ODR & ~PIN9;
        //__enable_irq();
    }

    return 0;
}
