#include <stdint.h> /* The most important addition to C99! */
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

int * swap(int * x, int * y);

/******************************************************************************/
int * swap(int * x, int * y)
/******************************************************************************/
{
    static int tmp[2];

    tmp[0] = *x;
    tmp[1] = *y;

    *x = tmp[1];
    *y = tmp[0];

    return tmp;
}

uint8_t u8a, u8b;
uint16_t u16c, u16d;
uint32_t u32e, u32f;

int8_t s8;
int16_t s16;
int32_t s32;

/******************************************************************************/
void main(void)
/******************************************************************************/
{
    u8a = sizeof(u8a);
    u16c = sizeof(uint16_t);
    u32e = sizeof(uint32_t);

    u8a = 0xA1U;
    u16c = 0xC1C2U;
    u32e = 0xE1E2E3E4U;

    u8b = u8a;
    u16d = u16c;
    u32f = u32e;

    /* C always promotes smaller sizes to int, so in the case of
     * 32 bit core, u16 will be promoted to uin32_t and the computation
     * will be performed on 32 bits sizes variables, which will yield
     * the correct result.
     * On the other hand, u16d on 16 bit machine will be promoted to 16 bit int,
     * and the computation will be performed on 16 bit variables.
     * This will yield incorrect result, because it will overflow / will be
     * truncated to 16 bit.
     * The size of the computation does not depend on the left hand side assignment,
     * but solely on the types of variables on the right hand side.
     * Actually, the types will be promoted to the biggest type taking place
     * in the computation. */
    u16c = 40000U;
    u16d = 30000U;

    u32e = (uint32_t)u16c + (uint32_t)u16d;

    u16c = 100;
    s32 = 10 - (int16_t)u16c;

    u8a = 0xFFU;

    if ((uint8_t)(~u8a) == 0x00U)
    {
        asm("nop");
    }
    else
    {
        asm("nop");
    }

    RCC->APB2ENR |= 0x01U << 4; /* Enable GPIOF clock.  */
    GPIOC->CRH    = (0x01U << 0) | /* GPIOC8 as PP output. */
                    (0x01U << 4);  /* GPIOC9 as PP output. */


    int x = 2*240000;
    int y = 2*240000 / 2;


    while (1)
    {
        int * p;

        p = swap(&y, &x);

        gpio_high(STM32_GPIOC8);
        *(output[1]) = 0;

        delay(p[0]);

        gpio_low(STM32_GPIOC8);
        *(output[1]) = 1;

        delay(p[1]);
    }
}

/******************************************************************************/
unsigned int fact(unsigned int n)
/******************************************************************************/
{
    /* 0! = 1, for n = 0.
     * n! = n * (n - 1)! for n > 0. */

    unsigned int retval;
    unsigned int foo[6];

    foo[n] = n;


    if (0U == n)
    {
        retval = 1U;
    }
    else
    {
        retval = foo[n] * fact(n - 1U);
    }

    return retval;
}
