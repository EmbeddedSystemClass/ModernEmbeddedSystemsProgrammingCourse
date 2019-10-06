/* Startup code for STM32F100. */

#include "bsp.h"

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
int const __vector_table[] @ ".intvec" = {
/******************************************************************************/
    (int) &CSTACK$$Limit,
    (int) &__iar_program_start,
    (int) &NMI_Handler,
    (int) &HardFault_Handler,
    (int) &MemManage_Handler,
    (int) &BusFault_Handler,
    (int) &UsageFault_Handler,
          0, /* Reserved. */
          0, /* Reserved. */
          0, /* Reserved. */
          0, /* Reserved. */
    (int) &SVC_Handler,
    (int) &DebugMon_Handler,
          0, /* Reserved. */
    (int) &PendSV_Handler,
    (int) &SysTick_Handler
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
