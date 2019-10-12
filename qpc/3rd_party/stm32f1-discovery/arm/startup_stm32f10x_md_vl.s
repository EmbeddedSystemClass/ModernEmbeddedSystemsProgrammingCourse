;/***************************************************************************/
; * @file     startup_stm32f10x_md_vl.s for ARM-KEIL ARM assembler
; * @brief    CMSIS Cortex-M3 Core Device Startup File for STM32F100RB
; * @version  CMSIS 4.3.0
; * @date     20 August 2015
; *
; * @description
; * Created from startup file for TM4C123GH6PM from Modern Embedded Systems
; * Programming Course by Miro Samek, Quantum Leaps, www.state-machine.com
; *
; * @note
; * The symbols Stack_Size and Heap_Size should be provided on the command-
; * line options to the assembler, for example as:
; *     --pd "Stack_Size SETA 512" --pd "Heap_Size SETA 0"
; *
; * @note
; * The function assert_failed defined at the end of this file defines
; * the error/assertion handling policy for the application and might
; * need to be customized for each project. This function is defined in
; * assembly to re-set the stack pointer, in case it is corrupted by the
; * time assert_failed is called.
; *
; ***************************************************************************/
;/* Copyright (c) 2012 ARM LIMITED
;
;  All rights reserved.
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions are met:
;  - Redistributions of source code must retain the above copyright
;    notice, this list of conditions and the following disclaimer.
;  - Redistributions in binary form must reproduce the above copyright
;    notice, this list of conditions and the following disclaimer in the
;    documentation and/or other materials provided with the distribution.
;  - Neither the name of ARM nor the names of its contributors may be used
;    to endorse or promote products derived from this software without
;    specific prior written permission.
;
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;  POSSIBILITY OF SUCH DAMAGE.
;---------------------------------------------------------------------------*/

;******************************************************************************
;
; Allocate space for the stack.
;
;******************************************************************************
        AREA    STACK, NOINIT, READWRITE, ALIGN=3
__stack_base
StackMem
        SPACE   Stack_Size    ; provided in command-line option, for example:
                              ; --pd "Stack_Size SETA 512"
__stack_limit
__initial_sp

;******************************************************************************
;
; Allocate space for the heap.
;
;******************************************************************************
        AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
HeapMem
        SPACE   Heap_Size     ; provided in command-line option, for example:
                              ; --pd "Heap_Size SETA 0"
__heap_limit

;******************************************************************************
;
; Indicate that the code in this file preserves 8-byte alignment of the stack.
;
;******************************************************************************
        PRESERVE8

;******************************************************************************
;
; Place code into the reset code section.
;
;******************************************************************************
        AREA   RESET, DATA, READONLY
        EXPORT  __Vectors
        EXPORT  __Vectors_End
        EXPORT  __Vectors_Size

;******************************************************************************
;
; The vector table.
;
;******************************************************************************
__Vectors
        DCD     __initial_sp                ; Top of Stack
        DCD     Reset_Handler               ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
        DCD     MemManage_Handler           ; The MPU fault handler
        DCD     BusFault_Handler            ; The bus fault handler
        DCD     UsageFault_Handler          ; The usage fault handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall handler
        DCD     DebugMon_Handler            ; Debug monitor handler
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; The PendSV handler
        DCD     SysTick_Handler             ; The SysTick handler

        ; IRQ handlers...
        DCD     WWDG_IRQHandler                 ; Window Watchdog
        DCD     PVD_IRQHandler                  ; PVD through EXTI Line detect
        DCD     TAMPER_IRQHandler               ; Tamper
        DCD     RTC_IRQHandler                  ; RTC
        DCD     FLASH_IRQHandler                ; Flash
        DCD     RCC_IRQHandler                  ; RCC
        DCD     EXTI0_IRQHandler                ; EXTI Line 0
        DCD     EXTI1_IRQHandler                ; EXTI Line 1
        DCD     EXTI2_IRQHandler                ; EXTI Line 2
        DCD     EXTI3_IRQHandler                ; EXTI Line 3
        DCD     EXTI4_IRQHandler                ; EXTI Line 4
        DCD     DMA1_Channel1_IRQHandler        ; DMA1 Channel 1
        DCD     DMA1_Channel2_IRQHandler        ; DMA1 Channel 2
        DCD     DMA1_Channel3_IRQHandler        ; DMA1 Channel 3
        DCD     DMA1_Channel4_IRQHandler        ; DMA1 Channel 4
        DCD     DMA1_Channel5_IRQHandler        ; DMA1 Channel 5
        DCD     DMA1_Channel6_IRQHandler        ; DMA1 Channel 6
        DCD     DMA1_Channel7_IRQHandler        ; DMA1 Channel 7
        DCD     ADC1_IRQHandler                 ; ADC1
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     EXTI9_5_IRQHandler              ; EXTI Line 9..5
        DCD     TIM1_BRK_TIM15_IRQHandler       ; TIM1 Break and TIM15
        DCD     TIM1_UP_TIM16_IRQHandler        ; TIM1 Update and TIM16
        DCD     TIM1_TRG_COM_TIM17_IRQHandler   ; TIM1 Trigger and Commutation and TIM17
        DCD     TIM1_CC_IRQHandler              ; TIM1 Capture Compare
        DCD     TIM2_IRQHandler                 ; TIM2
        DCD     TIM3_IRQHandler                 ; TIM3
        DCD     TIM4_IRQHandler                 ; TIM4
        DCD     I2C1_EV_IRQHandler              ; I2C1 Event
        DCD     I2C1_ER_IRQHandler              ; I2C1 Error
        DCD     I2C2_EV_IRQHandler              ; I2C2 Event
        DCD     I2C2_ER_IRQHandler              ; I2C2 Error
        DCD     SPI1_IRQHandler                 ; SPI1
        DCD     SPI2_IRQHandler                 ; SPI2
        DCD     USART1_IRQHandler               ; USART1
        DCD     USART2_IRQHandler               ; USART2
        DCD     USART3_IRQHandler               ; USART3
        DCD     EXTI15_10_IRQHandler            ; EXTI Line 15..10
        DCD     RTCAlarm_IRQHandler             ; RTC Alarm through EXTI Line
        DCD     CEC_IRQHandler                  ; HDMI-CEC
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved 
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved 
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     0                               ; Reserved
        DCD     TIM6_DAC_IRQHandler             ; TIM6 and DAC underrun
        DCD     TIM7_IRQHandler                 ; TIM7
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors



;******************************************************************************
;
; This is the code for exception handlers.
;
;******************************************************************************
        AREA    |.text|, CODE, READONLY

;******************************************************************************
;
; This is the code that gets called when the processor first starts execution
; following a reset event.
;
;******************************************************************************
Reset_Handler   PROC
        EXPORT  Reset_Handler  [WEAK]
        IMPORT  SystemInit
        IMPORT  __main

        LDR     r0, =SystemInit ; CMSIS system initialization
        BLX     r0

        ; Call the C library enty point that handles startup. This will copy
        ; the .data section initializers from flash to SRAM and zero fill the
        ; .bss section.
        LDR     r0, =__main
        BX      r0

        ; __main calls the main() function, which should not return,
        ; but just in case jump to assert_failed() if main returns.
        MOVS    r0,#0
        MOVS    r1,#0       ; error number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The NMI handler
;
;******************************************************************************
NMI_Handler     PROC
        EXPORT  NMI_Handler     [WEAK]
        MOVS    r0,#0
        MOVS    r1,#2       ; NMI exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The Hard Fault handler
;
;******************************************************************************
HardFault_Handler PROC
        EXPORT  HardFault_Handler [WEAK]
        MOVS    r0,#0
        MOVS    r1,#3       ; HardFault exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The MPU fault handler
;
;******************************************************************************
MemManage_Handler PROC
        EXPORT  MemManage_Handler     [WEAK]
        MOVS    r0,#0
        MOVS    r1,#4       ; MemManage exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The Bus Fault handler
;
;******************************************************************************
BusFault_Handler PROC
        EXPORT  BusFault_Handler     [WEAK]
        MOVS    r0,#0
        MOVS    r1,#5       ; BusFault exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The Usage Fault handler
;
;******************************************************************************
UsageFault_Handler PROC
        EXPORT  UsageFault_Handler   [WEAK]
        MOVS    r0,#0
        MOVS    r1,#6       ; UsageFault exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The SVC handler
;
;******************************************************************************
SVC_Handler PROC
        EXPORT  SVC_Handler   [WEAK]
        MOVS    r0,#0
        MOVS    r1,#11      ; SVCall exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The Debug Monitor handler
;
;******************************************************************************
DebugMon_Handler PROC
        EXPORT  DebugMon_Handler     [WEAK]
        MOVS    r0,#0
        MOVS    r1,#12      ; DebugMon exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The PendSV handler
;
;******************************************************************************
PendSV_Handler PROC
        EXPORT  PendSV_Handler       [WEAK]
        MOVS    r0,#0
        MOVS    r1,#14      ; PendSV exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; The SysTick handler
;
;******************************************************************************
SysTick_Handler PROC
        EXPORT  SysTick_Handler     [WEAK]
        MOVS    r0,#0
        MOVS    r1,#15      ; SysTick exception number
        B       assert_failed
        ENDP

;******************************************************************************
;
; Define Default_Handledr as dummy for all IRQ handlers
;
;******************************************************************************
Default_Handler PROC
        EXPORT  WWDG_IRQHandler                  [WEAK]
        EXPORT  PVD_IRQHandler                   [WEAK]
        EXPORT  TAMPER_IRQHandler                [WEAK]
        EXPORT  RTC_IRQHandler                   [WEAK]
        EXPORT  FLASH_IRQHandler                 [WEAK]
        EXPORT  RCC_IRQHandler                   [WEAK]
        EXPORT  EXTI0_IRQHandler                 [WEAK]
        EXPORT  EXTI1_IRQHandler                 [WEAK]
        EXPORT  EXTI2_IRQHandler                 [WEAK]
        EXPORT  EXTI3_IRQHandler                 [WEAK]
        EXPORT  EXTI4_IRQHandler                 [WEAK]
        EXPORT  DMA1_Channel1_IRQHandler         [WEAK]
        EXPORT  DMA1_Channel2_IRQHandler         [WEAK]
        EXPORT  DMA1_Channel3_IRQHandler         [WEAK]
        EXPORT  DMA1_Channel4_IRQHandler         [WEAK]
        EXPORT  DMA1_Channel5_IRQHandler         [WEAK]
        EXPORT  DMA1_Channel6_IRQHandler         [WEAK]
        EXPORT  DMA1_Channel7_IRQHandler         [WEAK]
        EXPORT  ADC1_IRQHandler                  [WEAK]
        EXPORT  EXTI9_5_IRQHandler               [WEAK]
        EXPORT  TIM1_BRK_TIM15_IRQHandler        [WEAK]
        EXPORT  TIM1_UP_TIM16_IRQHandler         [WEAK]
        EXPORT  TIM1_TRG_COM_TIM17_IRQHandler    [WEAK]
        EXPORT  TIM1_CC_IRQHandler               [WEAK]
        EXPORT  TIM2_IRQHandler                  [WEAK]
        EXPORT  TIM3_IRQHandler                  [WEAK]
        EXPORT  TIM4_IRQHandler                  [WEAK]
        EXPORT  I2C1_EV_IRQHandler               [WEAK]
        EXPORT  I2C1_ER_IRQHandler               [WEAK]
        EXPORT  I2C2_EV_IRQHandler               [WEAK]
        EXPORT  I2C2_ER_IRQHandler               [WEAK]
        EXPORT  SPI1_IRQHandler                  [WEAK]
        EXPORT  SPI2_IRQHandler                  [WEAK]
        EXPORT  USART1_IRQHandler                [WEAK]
        EXPORT  USART2_IRQHandler                [WEAK]
        EXPORT  USART3_IRQHandler                [WEAK]
        EXPORT  EXTI15_10_IRQHandler             [WEAK]
        EXPORT  RTCAlarm_IRQHandler              [WEAK]
        EXPORT  CEC_IRQHandler                   [WEAK]
        EXPORT  TIM6_DAC_IRQHandler              [WEAK]
        EXPORT  TIM7_IRQHandler                  [WEAK]

WWDG_IRQHandler
PVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FLASH_IRQHandler
RCC_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
ADC1_IRQHandler
EXTI9_5_IRQHandler
TIM1_BRK_TIM15_IRQHandler
TIM1_UP_TIM16_IRQHandler
TIM1_TRG_COM_TIM17_IRQHandler
TIM1_CC_IRQHandler
TIM2_IRQHandler
TIM3_IRQHandler
TIM4_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
USART3_IRQHandler
EXTI15_10_IRQHandler
RTCAlarm_IRQHandler
CEC_IRQHandler
TIM6_DAC_IRQHandler
TIM7_IRQHandler
        MOVS    r0,#0
        MOVS    r1,#-1      ; 0xFFFFFFF
        B       assert_failed
        ENDP

        ALIGN               ; make sure the end of this section is aligned


;******************************************************************************
;
; The function expected of the C library startup code for defining the stack
; and heap memory locations.  For the C library version of the startup code,
; provide this function so that the C library initialization code can find out
; the location of the stack and heap.
;
;******************************************************************************
    IF :DEF: __MICROLIB
        EXPORT  __initial_sp
        EXPORT  __stack_limit
        EXPORT  __heap_base
        EXPORT  __heap_limit
    ELSE
        IMPORT  __use_two_region_memory
        EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
        LDR     R0, =__heap_base
        LDR     R1, =__stack_limit
        LDR     R2, =__heap_limit
        LDR     R3, =__stack_base
        BX      LR
        ENDP
    ENDIF

;******************************************************************************
;
; The function assert_failed defines the error/assertion handling policy
; for the application. After making sure that the stack is OK, this function
; calls Q_onAssert, which should NOT return (typically reset the CPU).
;
; NOTE: the function Q_onAssert should NOT return.
;
; The C proptotype of the assert_failed() and Q_onAssert() functions are:
; void assert_failed(char const *file, int line);
; void Q_onAssert   (char const *file, int line);
;******************************************************************************
        EXPORT  assert_failed
        IMPORT  Q_onAssert
assert_failed PROC

        LDR    sp,=__initial_sp  ; re-set the SP in case of stack overflow
        BL     Q_onAssert        ; call the application-specific handler

        B      .                 ; should not be reached, but just in case...

        ENDP

        ALIGN                    ; make sure the end of this section is aligned

        END                      ; end of module
