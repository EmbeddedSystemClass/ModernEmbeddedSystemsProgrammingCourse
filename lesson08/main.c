#include "stm32f10x.h"

#define PIN8 (1U << 8)
#define PIN9 (1U << 9)

#define STM32_GPIOC8 (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 8U * 4U)
#define STM32_GPIOC9 (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 9U * 4U)

void gpio_high(unsigned int volatile * gpio)
{
    *gpio = 1U;
}

void gpio_low(unsigned int volatile * gpio)
{
    *gpio = 0U;
}

unsigned int volatile * const output[2] = {
    (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 8U * 4U),
    (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 9U * 4U)
};

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
        gpio_high(STM32_GPIOC8);
        *(output[1]) = 0;

        counter = 0;
        while (counter < 240000)
        {
            ++counter;
        }

        gpio_low(STM32_GPIOC8);
        *(output[1]) = 1;

        counter = 0;
        while (counter < 240000)
        {
            ++counter;
        }
    }

    /* return 0; */
}
