/*******************************************************************************
*   touch.h
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
/*  This is an automatically generated file. Do not modify the contents manually.
    Instead, use the Project Builder Wizard to make changes to the design.
*/
/**
  * Acquisition Technology Name.
  *
  * Possible values: _QMATRIX_, _QTOUCH_ .
  */
#define _QMATRIX_

/**
  * Device Name.
  *
  */
#define __ATtiny44A__


/**
  * Delay cycles that determine the capacitance charge pulse width. Value of 0
  * will enable charge pulse width of 1 clock cycle, 1 will enable a width of 2
  * clock cycles and so on...
  *
  * Possible values: 1,2,3,4,5,10,25,50
  */
#ifndef QT_DELAY_CYCLES
#define QT_DELAY_CYCLES 1
#endif


/**
  * Define the Number of ROTORS/SLIDERS used.
  * Possible values: 0             ( if _ROTOR_SLIDER_ is not defined)
  *                  1, 2, 4 and 8 ( if _ROTOR_SLIDER_ is defined)
  * Depending on the library used..
  */
#define QT_MAX_NUM_ROTORS_SLIDERS 0
//#define _ROTOR_SLIDER_ 



/**
  * Number of Channels(dependent on the library used and application requirement).
  * The least possible number more that the application needs.
  * Please refer to the QTouch library user guide.pdf and library selection 
  * guide.xls more information on selecting the number of channels.
  *
  * Possible values: 4, 8, 12, 16, 32. in case of QTouch
  * Possible values: 4, 8, 16, 32, 56, 64. in case of QMatrix. 
  */
  #define QT_NUM_CHANNELS   4
/** 
  * Define the Number X lines to be used.
  * Possible values: 4 and 8
  * Depending on the library used.Please refer to the QTouch library user guide.pdf 
  * and library selection guide.xls more information on selecting the number of channels.
  *
  */
#define NUM_X_LINES	4
/**
  * Specify the number of ports on which X-lines that are distributed.
  * Note: Support is provided only for a maximum of 3 ports for X.
  *		 ( Maximum possible value for NUM_X_PORTS is 3)
  * Possible values: 1,2,3
  * Also, note that code memory increases with the number of ports
  * used for X lines.
  */
#define NUM_X_PORTS	1
/**
  * Specify Which ports have X lines on them. These macros are used
  * to conditionally compile in support for ports driving X lines.
  */
#define PORT_X_1	B

/** 
  * Define the Number Y lines to be used.
  *  Possible values: 1, 2, 4 and 8
  * Depending on the library used.Please refer to the QTouch library user guide.pdf 
  * and library selection guide.xls more information on selecting the number of channels.
  */
#define NUM_Y_LINES	1

/**
  * Specify the port for YA, YB, 
  * For rules to specify the port for YA ,YB please go through QTouch library 
  * user guide .pdf
  */
#define PORT_YA 	A
#define PORT_YB 	A

/**
  * SHARED_YA_YB should be 1 if YA and YB lines are on same port else 0
  */
#define SHARED_YAYB 	1
/**
  * Specify the port for SMP. 
  * And Specify the pin for SMP on selected SMP port. 
  * Any GPIO pin not conflicting with the other touch pins used for the application
  */
#define PORT_SMP 	A
#define SMP_PIN 	3

#define PORT_NUM_1	1


/**
  * Measurement Period Time determines the time to measure touch
  *
  * Possible values:
  */
#define QT_MEASUREMENT_PERIOD_MS 50u


/**
  * Total ticks per msec.
  * TICKS_PER_MS = (CLK_FREQ/TIMER_PRESCALER)*(1/1000)
  */
#define TICKS_PER_MS 4u



/******************************************************************************
*   Debug Interface Settings
******************************************************************************/

// #define _DEBUG_INTERFACE_





