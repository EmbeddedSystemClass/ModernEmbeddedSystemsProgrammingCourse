/******************************************************************************/
/* Startup code for STM32F100.                                                */
/******************************************************************************/

#include "bsp.h"

typedef void (* Handler_Func_t)(void);

extern void CSTACK$$Limit;
void __iar_program_start(void);

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void Unused_Handler(void);

/******************************************************************************/
Handler_Func_t const __vector_table[] @ ".intvec" = {
/******************************************************************************/
    (Handler_Func_t) &CSTACK$$Limit,
    &__iar_program_start,
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
__stackless void NMI_Handler(void)
/******************************************************************************/
{
    assert_failed("NMI", __LINE__);
}

/******************************************************************************/
__stackless void HardFault_Handler(void)
/******************************************************************************/
{
    assert_failed("HardFault", __LINE__);
}

/******************************************************************************/
__stackless void MemManage_Handler(void)
/******************************************************************************/
{
    assert_failed("MemManage", __LINE__);
}

/******************************************************************************/
__stackless void BusFault_Handler(void)
/******************************************************************************/
{
    assert_failed("BusFault", __LINE__);
}

/******************************************************************************/
__stackless void UsageFault_Handler(void)
/******************************************************************************/
{
    assert_failed("UsageFault", __LINE__);
}

/******************************************************************************/
__stackless void Unused_Handler(void)
/******************************************************************************/
{
    assert_failed("Unused", __LINE__);
}

#pragma weak SVC_Handler = Unused_Handler
#pragma weak DebugMon_Handler = Unused_Handler
#pragma weak PendSV_Handler = Unused_Handler
#pragma weak SysTick_Handler = Unused_Handler
