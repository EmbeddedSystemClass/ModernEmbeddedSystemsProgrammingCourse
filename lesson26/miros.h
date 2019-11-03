/****************************************************************************
* MInimal Real-time Operating System (MIROS)
* version 0.26 (matching lesson 26)
*
* This software is a teaching aid to illustrate the concepts underlying
* a Real-Time Operating System (RTOS). The main goal of the software is
* simplicity and clear presentation of the concepts, but without dealing
* with various corner cases, portability, or error handling. For these
* reasons, the software is generally NOT intended or recommended for use
* in commercial applications.
*
* Copyright (C) 2018 Miro Samek. All Rights Reserved.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <https://www.gnu.org/licenses/>.
*
* Contact Information:
* https://www.state-machine.com
****************************************************************************/

#ifndef __MIROS_H__
#define __MIROS_H__

#include <stdint.h>

/* Thread Control Block (TCB). */
typedef struct {
    void * sp;        /* Stack pointer. */
    uint32_t timeout; /* Timeout delay down-counter. */
    uint8_t prio;     /* Thread priority. */
} OSThread;

typedef void (* OSThreadHandler)(void);

void OS_init(void * stkSto, uint32_t stkSize);

/* Callback to handle the idle condition. */
void OS_onIdle(void);

/* This function must be called with interrupts DISABLED. */
void OS_sched(void);

/* Transfer control to the RTOS to run the threads. */
void OS_run(void);

/* Blocking delay. */
void OS_delay(uint32_t ticks);

/* Process all timeouts. */
void OS_tick(void);

/* Callback to configure and start interrupts. */
void OS_onStartup(void);

void OSThread_start(OSThread * me,
    uint8_t prio,
    OSThreadHandler threadHandler,
    void * stkSto,
    uint32_t stkSize);

#endif /* __MIROS_H__ */
