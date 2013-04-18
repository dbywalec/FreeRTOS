/*
    FreeRTOS V7.4.1 - Copyright (C) 2013 Real Time Engineers Ltd.

    FEATURES AND PORTS ARE ADDED TO FREERTOS ALL THE TIME.  PLEASE VISIT
    http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.

    >>>>>>NOTE<<<<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
    details. You should have received a copy of the GNU General Public License
    and the FreeRTOS license exception along with FreeRTOS; if not it can be
    viewed here: http://www.freertos.org/a00114.html and also obtained by
    writing to Real Time Engineers Ltd., contact details for whom are available
    on the FreeRTOS WEB site.

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************


    http://www.FreeRTOS.org - Documentation, books, training, latest versions, 
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, and our new
    fully thread aware and reentrant UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High 
    Integrity Systems, who sell the code with commercial support, 
    indemnification and middleware, under the OpenRTOS brand.
    
    http://www.SafeRTOS.com - High Integrity Systems also provide a safety 
    engineered and independently SIL3 certified version for use in safety and 
    mission critical applications that require provable dependability.
*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "IntQueueTimer.h"
#include "IntQueue.h"

/* Hardware includes. */
#include "lpc11xx.h"

/* The two timer frequencies. */
#define tmrTIMER_2_FREQUENCY	( 2000UL )
#define tmrTIMER_3_FREQUENCY	( 2001UL )

/* The priorities for the two timers.  Note that a priority of 0 is the highest
possible on Cortex-M devices. */
#define tmrMAX_PRIORITY				( 0UL )
#define trmSECOND_HIGHEST_PRIORITY ( tmrMAX_PRIORITY + 1 )

void vInitialiseTimerForIntQueueTest( void )
{
	/* Enable AHB clock for GPIO and 16-bit timers. */
	LPC_SYSCON->SYSAHBCLKCTRL |= ( 7 << 6 );

	/* Interrupt and reset on MR0 match. */
	LPC_TMR16B0->MCR = 0x03;
	LPC_TMR16B1->MCR = 0x03;

	/* Configure the frequency of the interrupt generated by MR0 matches. */
	LPC_TMR16B0->MR0 = SystemCoreClock / tmrTIMER_2_FREQUENCY;
	LPC_TMR16B1->MR0 = SystemCoreClock / tmrTIMER_3_FREQUENCY;

	/* Don't generate interrupts until the scheduler has been started.
	Interrupts will be automatically enabled when the first task starts
	running. */
	taskDISABLE_INTERRUPTS();

	/* Set the timer interrupts to be above the kernel.  The interrupts are
	assigned different priorities so they nest with each other. */
	NVIC_SetPriority( TIMER_16_0_IRQn, trmSECOND_HIGHEST_PRIORITY );
	NVIC_SetPriority( TIMER_16_1_IRQn, tmrMAX_PRIORITY );

	/* Enable the timer interrupts. */
	NVIC_EnableIRQ( TIMER_16_0_IRQn );
	NVIC_EnableIRQ( TIMER_16_1_IRQn );

	/* Start the timers. */
	LPC_TMR16B0->TCR = 0x01;
	LPC_TMR16B1->TCR = 0x01;
}
/*-----------------------------------------------------------*/

void TIMER16_0_IRQHandler(void)
{
	/* Clear the interrupt. */
	LPC_TMR16B0->IR = LPC_TMR16B0->IR;

	/* Call the  standard demo int queue timer function for this first timer. */
	portEND_SWITCHING_ISR( xFirstTimerHandler() );
}
/*-----------------------------------------------------------*/

void TIMER16_1_IRQHandler(void)
{
	/* Clear the interrupt. */
	LPC_TMR16B1->IR = LPC_TMR16B1->IR;

	/* Call the standard demo int queue timer function for this second timer. */
	portEND_SWITCHING_ISR( xSecondTimerHandler() );
}
/*-----------------------------------------------------------*/
