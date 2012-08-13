/*******************************************************************************
*   $FILE:  main.c
*   Atmel Corporation:  http://www.atmel.com \n
*   Support email:  touch@atmel.com
******************************************************************************/

/*  License
*   Copyright (c) 2010, Atmel Corporation All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions are met:
*
*   1. Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
*   2. Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
*   3. The name of ATMEL may not be used to endorse or promote products derived
*   from this software without specific prior written permission.
*
*   THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
*   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
*   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
*   SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
*   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*   ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
*   THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*----------------------------------------------------------------------------
                            compiler information
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                include files
----------------------------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "touch.h"
/*----------------------------------------------------------------------------
                            manifest constants
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
                            type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                prototypes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                            Structure Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                    macros
----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
                                global variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                extern variables
----------------------------------------------------------------------------*/
/* Timer period in msec. */
extern uint16_t qt_measurement_period_msec;
extern uint16_t time_ms_inc;
/*----------------------------------------------------------------------------
                                static variables
----------------------------------------------------------------------------*/

/* flag set by timer ISR when it's time to measure touch */
extern volatile uint8_t time_to_measure_touch;

/* current time, set by timer ISR */
extern volatile uint16_t current_time_ms_touch;

#if defined(__ATtiny84__)
#if defined(_QTOUCH_)

/*============================================================================
Name    :   init_timer_isr
------------------------------------------------------------------------------
Purpose :   configure timer ISR to fire regularly
============================================================================*/

void init_timer_isr( void )
{
   /*  set timer compare value (how often timer ISR will fire) */
    OCR1A = ( TICKS_PER_MS * qt_measurement_period_msec);

    /*  enable timer ISR */
    TIMSK1 |= (1u << OCIE1A);

    /*  timer prescaler = system clock / 8  */
    TCCR1B |= (1u << CS11);

    /*  timer mode = CTC (count up to compare value, then reset)    */
    TCCR1B |= (1u << WGM12);
}
/*============================================================================
Name    :   set_timer_period
------------------------------------------------------------------------------
Purpose :   changed the timer period runtime
Input   :   qt_measurement_period_msec
Output  :   n/a
Notes   :
============================================================================*/
void set_timer_period(uint16_t qt_measurement_period_msec)
{
	/*  set timer compare value (how often timer ISR will fire,set to 1 ms interrupt) */
  OCR1A = TICKS_PER_MS * qt_measurement_period_msec;
}


ISR(TIM1_COMPA_vect)
{

    /*  set flag: it's time to measure touch    */
    time_to_measure_touch = 1u;

    /*  update the current time */
    current_time_ms_touch += qt_measurement_period_msec;
}

#elif defined(_QMATRIX_)

/*============================================================================
Name    :   init_timer_isr
------------------------------------------------------------------------------
Purpose :   configure timer ISR to fire regularly

============================================================================*/
void init_timer_isr( void )
{
   /*  set timer compare value (how often timer ISR will fire set to 1 ms timer interrupt) */

   OCR0A = ( TICKS_PER_MS * 1);

   /*  enable timer ISR on compare A */
   TIMSK0 |= 0x02u; // Caution
   /*  timer prescaler = system clock / 1024  */
   TCCR0B |= 0x05u; // Caution
   /*  timer mode = CTC (count up to compare value, then reset)    */
   TCCR0A |= 0x02u; // Caution
}

ISR(TIM0_COMPA_vect)
{
  time_ms_inc++;

  if(time_ms_inc >= qt_measurement_period_msec)
  {
    time_ms_inc =0;
   /*  set flag: it's time to measure touch    */
   time_to_measure_touch = 1u;
  }
  else
  {

  }
  /*  update the current time */
   current_time_ms_touch++;;
}
/*============================================================================
Name    :   set_timer_period
------------------------------------------------------------------------------
Purpose :   set the timer period
============================================================================*/
void set_timer_period(uint16_t qt_measurement_period_msec)
{
	OCR0A = ( TICKS_PER_MS * 1);
}
#endif /* TECHNOLOGY */

/*============================================================================
Name    :   init_system
------------------------------------------------------------------------------
Purpose :   initialise host app, pins, watchdog, etc
============================================================================*/
void init_system( void )
{
    /*  run at 4MHz (assuming internal clock is set to 8MHz)*/
    CLKPR = 0x80u;
    CLKPR = 0x01u;

    /*  disable pull-ups    */
    MCUCR |= (1u << PUD);

}
#endif





