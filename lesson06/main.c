#include "stm32f10x.h"

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    int volatile counter;

    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOF clock.  */
    GPIOC->CRH    = 0x01U;      /* GPIOF8 as PP output. */

    while (1)
    {
        GPIOC->BSRR = 1U << 8; /* GPIOC8 high. */
        counter = 0;
        while (counter < 240000)
        {
            ++counter;
        }

        GPIOC->BRR  = 1U << 8; /* GPIOC8 low. */
        counter = 0;
        while (counter < 240000)
        {
            ++counter;
        }
    }

    return 0;
}
