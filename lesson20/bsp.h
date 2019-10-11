#ifndef __BSP_H__
#define __BSP_H__

#define PIN8 (1U << 8)
#define PIN9 (1U << 9)

__attribute__((naked)) void assert_failed(char const * p_name, int const line);
void SysTick_Handler(void);

#endif
