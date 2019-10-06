/* Startup code for STM32F100. */

int const __vector_table[] @ ".intvec" = {
    0x20004000,
    0x08000009
};
