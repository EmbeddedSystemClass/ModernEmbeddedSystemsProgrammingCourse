#include "stm32f10x.h"

#define PIN8 (1U << 8)
#define PIN9 (1U << 9)

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    int volatile counter;

    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOF clock.  */
    GPIOC->CRH    = (0x01U << 0) | /* GPIOC8 as PP output. */
                    (0x01U << 4);  /* GPIOC9 as PP output. */

    while (1)
    {
        GPIOC->BSRR = PIN8;
        GPIOC->BSR  = PIN9;
        counter = 0;
        while (counter < 240000)
        {
            ++counter;
        }

        GPIOC->BSR  = PIN8;
        GPIOC->BSRR = PIN9;
        counter = 0;
        while (counter < 240000)
        {
            ++counter;
        }
    }

    return 0;
}
