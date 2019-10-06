#include "stm32f10x.h"
#include "delay.h"

#define PIN8 (1U << 8)
#define PIN9 (1U << 9)

#define STM32_GPIOC8 (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 8U * 4U)
#define STM32_GPIOC9 (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 9U * 4U)

unsigned int volatile * const output[2] = {
    (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 8U * 4U),
    (unsigned int volatile *)(0x42000000U + 0x1100CU * 32U + 9U * 4U)
};

void gpio_high(unsigned int volatile * gpio);
void gpio_low(unsigned int volatile * gpio);

unsigned int fact(unsigned int n);

/******************************************************************************/
void gpio_high(unsigned int volatile * gpio)
/******************************************************************************/
{
    *gpio = 1U;
}

/******************************************************************************/
void gpio_low(unsigned int volatile * gpio)
/******************************************************************************/
{
    *gpio = 0U;
}

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    unsigned int volatile x;

    x = fact(0U);
    x = 2U + 3U * fact(1U);
    (void) fact(5U);

    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOF clock.  */
    GPIOC->CRH    = (0x01U << 0) | /* GPIOC8 as PP output. */
                    (0x01U << 4);  /* GPIOC9 as PP output. */

    while (1)
    {
        gpio_high(STM32_GPIOC8);
        *(output[1]) = 0;

        delay(240000);

        gpio_low(STM32_GPIOC8);
        *(output[1]) = 1;

        delay(120000);
    }

    /* return 0; */
}

/******************************************************************************/
unsigned int fact(unsigned int n)
/******************************************************************************/
{
    unsigned int retval;
    /* 0! = 1, for n = 0.
     * n! = n * (n - 1)! for n > 0. */

    if (0U == n)
    {
        retval = 1U;
    }
    else
    {
        retval = n * fact(n - 1U);
    }

    return retval;
}
