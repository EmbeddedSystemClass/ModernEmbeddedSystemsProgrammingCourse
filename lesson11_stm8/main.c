#include <stdint.h>

int main(void)
{
    uint32_t r;
    uint16_t a;
    uint16_t b;
    int32_t s32;

    a = 30000U;
    b = 40000U;

    r = a + (uint32_t)b;

    (void) r;


    /* When mixing signed and unsigned variables, both are promoted to unsigned type. */
    a = 100U;
    s32 = 10 - (int16_t)a;

    for (;;)
    {
    }
}
