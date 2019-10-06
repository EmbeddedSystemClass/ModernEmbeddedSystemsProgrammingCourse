int counter = 0;

/******************************************************************************/
int main(void)
/******************************************************************************/
{
    *((unsigned int volatile *)(0x40021000U + 0x18U)) |= 1U << 4;

    *((unsigned int volatile *)(0x40011000U + 0x04U)) = 0x01U;

    while (1)
    {
        *((unsigned int volatile *)(0x40011000U + 0x10U)) |= 1U << 8;
        for (int i = 0; i < 240000; ++i) asm("nop");
        *((unsigned int volatile *)(0x40011000U + 0x14U)) |= 1U << 8;
        for (int i = 0; i < 240000; ++i) asm("nop");
    }

    return 0;
}
