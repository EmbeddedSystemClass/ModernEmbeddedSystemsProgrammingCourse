/*******************************************************************************
 * Startup code for STM32F100.
*******************************************************************************/

#include "bsp.h"

typedef void (* Handler_Func_t)(void);

/* Start and end of stack defined in linker script. */
extern int __stack_start__;
extern int __stack_end__;

/* Function prototypes. */
void Default_Handler(void);
void Reset_Handler(void);
void SystemInit(void);

/* Cortex-M processor fault exceptions. */
void NMI_Handler(void)        __attribute__((weak));
void HardFault_Handler(void)  __attribute__((weak));
void MemManage_Handler(void)  __attribute__((weak));
void BusFault_Handler(void)   __attribute__((weak));
void UsageFault_Handler(void) __attribute__((weak));

/* Cortex-M processor non-fault exceptions. */
void SVC_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)   __attribute__((weak, alias("Default_Handler")));;
void SysTick_Handler(void)  __attribute__((weak, alias("Default_Handler")));;

/******************************************************************************/
__attribute__((section(".isr_vector")))
Handler_Func_t const g_pfnVectors[] = {
/******************************************************************************/
    (Handler_Func_t) &__stack_end__,
    &Reset_Handler,
    &NMI_Handler,
    &HardFault_Handler,
    &MemManage_Handler,
    &BusFault_Handler,
    &UsageFault_Handler,
    0, /* Reserved. */
    0, /* Reserved. */
    0, /* Reserved. */
    0, /* Reserved. */
    &SVC_Handler,
    &DebugMon_Handler,
    0, /* Reserved. */
    &PendSV_Handler,
    &SysTick_Handler
};

/******************************************************************************/
void Reset_Handler(void)
/******************************************************************************/
{
    extern int main(void);
    extern int __libc_init_array(void);
    extern unsigned __data_start;  		/* Start of .data in the linker script. */
    extern unsigned __data_end__;       /* End of .data in the linker script.   */
    extern unsigned const __data_load;  /* Initialization values for .data.     */
    extern unsigned __bss_start__;      /* Start of .bss in the linker script.  */
    extern unsigned __bss_end__;        /* End of .bss in the linker script.    */
    extern void software_init_hook(void) __attribute__((weak));

    unsigned const * src;
    unsigned * dst;

    //SystemInit(); /* CMSIS system initialization */

    /* Copy the data segment initializers from flash to RAM. */
    src = &__data_load;
    for (dst = &__data_start; dst < &__data_end__; ++dst, ++src)
    {
        *dst = *src;
    }

    /* Zero fill the .bss segment in RAM. */
    for (dst = &__bss_start__; dst < &__bss_end__; ++dst)
    {
        *dst = 0;
    }

    /* Init hook provided? */
    if (&software_init_hook != (void (*)(void))(0))
    {
        /* Give control to the RTOS. */
        software_init_hook(); /* This will also call __libc_init_array. */
    }
    else
    {
        /* Call all static constructors in C++ (harmless in C programs). */
        __libc_init_array();

        /* Application's entry point; should never return! */
        (void) main();
    }

    /* The previous code should not return, but assert just in case. */
    assert_failed("Reset_Handler", __LINE__);
}

/******************************************************************************/
__attribute__((naked)) void NMI_Handler(void)
/******************************************************************************/
{
    assert_failed("NMI", __LINE__);
}

/******************************************************************************/
__attribute__((naked)) void HardFault_Handler(void)
/******************************************************************************/
{
    __asm volatile (
        "    ldr r0,=str_hrd\n\t"
        "    mov r1,#1\n\t"
        "    b assert_failed\n\t"
        "str_hrd: .asciz \"HardFault\"\n\t"
        "  .align 2\n\t"
    );
}

/******************************************************************************/
__attribute__((naked)) void MemManage_Handler(void)
/******************************************************************************/
{
    __asm volatile (
        "    ldr r0,=str_mem\n\t"
        "    mov r1,#1\n\t"
        "    b assert_failed\n\t"
        "str_mem: .asciz \"MemManage\"\n\t"
        "  .align 2\n\t"
    );
}

/******************************************************************************/
__attribute__((naked)) void BusFault_Handler(void)
/******************************************************************************/
{
    __asm volatile (
        "    ldr r0,=str_bus\n\t"
        "    mov r1,#1\n\t"
        "    b assert_failed\n\t"
        "str_bus: .asciz \"BusFault\"\n\t"
        "  .align 2\n\t"
    );
}

/******************************************************************************/
__attribute__((naked)) void UsageFault_Handler(void)
/******************************************************************************/
{
    __asm volatile (
        "    ldr r0,=str_usage\n\t"
        "    mov r1,#1\n\t"
        "    b assert_failed\n\t"
        "str_usage: .asciz \"UsageFault\"\n\t"
        "  .align 2\n\t"
    );
}

/******************************************************************************/
__attribute__((naked)) void Default_Handler(void)
/******************************************************************************/
{
    __asm volatile (
        "    ldr r0,=str_dflt\n\t"
        "    mov r1,#1\n\t"
        "    b assert_failed\n\t"
        "str_dflt: .asciz \"Default\"\n\t"
        "  .align 2\n\t"
    );
}
