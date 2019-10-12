/*$file${Comp::.::philo.c} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*
* Model: dpp.qm
* File:  ${Comp::.::philo.c}
*
* This code has been generated by QM 4.5.1 (https://www.state-machine.com/qm).
* DO NOT EDIT THIS FILE MANUALLY. All your changes will be lost.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*/
/*$endhead${Comp::.::philo.c} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
#include "qpc.h"
#include "dpp.h"
#include "bsp.h"

//Q_DEFINE_THIS_FILE

/* helper macros to provide a randomized think time for Philos */
#define THINK_TIME  \
    (QTimeEvtCtr)((BSP_random() % BSP_TICKS_PER_SEC) + (BSP_TICKS_PER_SEC/2U))
#define EAT_TIME    \
    (QTimeEvtCtr)((BSP_random() % BSP_TICKS_PER_SEC) + BSP_TICKS_PER_SEC)

/* Philo definition --------------------------------------------------------*/
/*$skip${QP_VERSION} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/* Check for the minimum required QP version */
#if (QP_VERSION < 650U) || (QP_VERSION != ((QP_RELEASE^4294967295U) % 0x3E8U))
#error qpc version 6.5.0 or higher required
#endif
/*$endskip${QP_VERSION} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
/*$define${Comp::Philo} vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv*/
/*${Comp::Philo} ...........................................................*/
/*${Comp::Philo::ctor} .....................................................*/
void Philo_ctor(Philo * const me) {
    QHsm_ctor(&me->super, Q_STATE_CAST(&Philo_initial));
    CompTimeEvt_ctor(&me->timeEvt, AO_Table, &me->super, TIMEOUT_SIG, 0U);
}

/*${Comp::Philo::SM} .......................................................*/
QState Philo_initial(Philo * const me, QEvt const * const e) {
    /*${Comp::Philo::SM::initial} */
    static uint8_t registered = (uint8_t)0; /* starts off with 0, per C-standard */
    (void)e; /* suppress the compiler warning about unused parameter */
    if (registered == (uint8_t)0) {
        registered = (uint8_t)1;
        QS_FUN_DICTIONARY(&Philo_initial);
        QS_FUN_DICTIONARY(&Philo_thinking);
        QS_FUN_DICTIONARY(&Philo_hungry);
        QS_FUN_DICTIONARY(&Philo_eating);
    }
    return Q_TRAN(&Philo_thinking);
}
/*${Comp::Philo::SM::thinking} .............................................*/
QState Philo_thinking(Philo * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${Comp::Philo::SM::thinking} */
        case Q_ENTRY_SIG: {
            QTimeEvt_armX(&me->timeEvt.super, THINK_TIME, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*${Comp::Philo::SM::thinking} */
        case Q_EXIT_SIG: {
            QTimeEvt_disarm(&me->timeEvt.super);
            status_ = Q_HANDLED();
            break;
        }
        /*${Comp::Philo::SM::thinking::TIMEOUT} */
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&Philo_hungry);
            break;
        }
        /*${Comp::Philo::SM::thinking::TEST} */
        case TEST_SIG: {
            status_ = Q_HANDLED();
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${Comp::Philo::SM::hungry} ...............................................*/
QState Philo_hungry(Philo * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${Comp::Philo::SM::hungry} */
        case Q_ENTRY_SIG: {
            /* asynchronously post event to the Container */
            TableEvt *pe = Q_NEW(TableEvt, HUNGRY_SIG);
            pe->philo = me;
            QACTIVE_POST_LIFO(AO_Table, &pe->super);
            status_ = Q_HANDLED();
            break;
        }
        /*${Comp::Philo::SM::hungry::EAT} */
        case EAT_SIG: {
            status_ = Q_TRAN(&Philo_eating);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*${Comp::Philo::SM::eating} ...............................................*/
QState Philo_eating(Philo * const me, QEvt const * const e) {
    QState status_;
    switch (e->sig) {
        /*${Comp::Philo::SM::eating} */
        case Q_ENTRY_SIG: {
            QTimeEvt_armX(&me->timeEvt.super, EAT_TIME, 0U);
            status_ = Q_HANDLED();
            break;
        }
        /*${Comp::Philo::SM::eating} */
        case Q_EXIT_SIG: {
            QTimeEvt_disarm(&me->timeEvt.super);

            /* asynchronously post event to the Container */
            TableEvt *pe = Q_NEW(TableEvt, DONE_SIG);
            pe->philo = me;
            QACTIVE_POST_LIFO(AO_Table, &pe->super);
            status_ = Q_HANDLED();
            break;
        }
        /*${Comp::Philo::SM::eating::TIMEOUT} */
        case TIMEOUT_SIG: {
            status_ = Q_TRAN(&Philo_thinking);
            break;
        }
        default: {
            status_ = Q_SUPER(&QHsm_top);
            break;
        }
    }
    return status_;
}
/*$enddef${Comp::Philo} ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
