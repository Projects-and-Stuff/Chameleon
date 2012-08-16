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
#define __delay_cycles(n)     __builtin_avr_delay_cycles(n)
#define __enable_interrupt()  sei()

#ifndef F_CPU
#define F_CPU 8000000UL	      // Sets up the default speed for delay.h
#endif
#include <util/delay.h>


#include "i2cmaster.h"


#include "touch_api.h"
#include "touch.h"
/*----------------------------------------------------------------------------
                            manifest constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                    macros
----------------------------------------------------------------------------*/

#define GET_SENSOR_STATE(SENSOR_NUMBER) qt_measure_data.qt_touch_status.sensor_states[(SENSOR_NUMBER/8)] & (1 << (SENSOR_NUMBER % 8))
#define GET_ROTOR_SLIDER_POSITION(ROTOR_SLIDER_NUMBER) qt_measure_data.qt_touch_status.rotor_slider_values[ROTOR_SLIDER_NUMBER]

/*----------------------------------------------------------------------------
                            type definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                prototypes
----------------------------------------------------------------------------*/
extern uint16_t touch_measure();
extern void touch_init( void );
extern void init_system( void );
extern void init_timer_isr(void);
extern void set_timer_period(uint16_t);
/*----------------------------------------------------------------------------
                            Structure Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                    macros
----------------------------------------------------------------------------*/

#define PCA9685 170 //0x55

#define Reset 0x01			// Reset the device
#define LEDCOUNT 15			// number of LEDS to light 15 max

#define MODE1 0x00			// 0x00 location for Mode1 register address
#define MODE2 0x01			// 0x01 location for Mode1 register address
#define SUBADR1 0x02
#define SUBADR2 0x03
#define SUBADR3 0x04
#define ALLCALLADR 0x05


#define LED0_ON_L 0x06		// location for start of LED0 registers


#define ALL_LED_ON_L 0xFA
#define ALL_LED_ON_H 0xFB
#define ALL_LED_OFF_L 0xFC
#define ALL_LED_OFF_H 0xFD
#define PRE_SCALE 0xFE
#define TestMode 0xFF

/* MODE1 bits */
#define PCA9685_RESTART 0x80
#define PCA9685_EXTCLK  0x40
#define PCA9685_AI      0x20
#define PCA9685_SLEEP   0x10
#define PCA9685_SUB1    0x08
#define PCA9685_SUB2    0x04
#define PCA9685_SUB3    0x02
#define PCA9685_ALLCALL 0x01

/* MODE2 bits */
#define PCA9685_INVRT   0x10
#define PCA9685_OCH     0x08
#define PCA9685_OUTDRV  0x04
#define PCA9685_OUTNE1  0x02
#define PCA9685_OUTNE0  0x01

/* LEDX_ON_H bits */
#define PCA9685_LED_ON 0x10

/* LEDX_OFF_H bits */
#define PCA9685_LED_OFF 0x10

//Highest random number (brightness level)
//#define RAND_MAX 100


/*----------------------------------------------------------------------------
                                global variables
----------------------------------------------------------------------------*/
/* Timer period in msec. */
uint16_t qt_measurement_period_msec = QT_MEASUREMENT_PERIOD_MS;
uint16_t time_ms_inc=0;
/*----------------------------------------------------------------------------
                                extern variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
                                static variables
----------------------------------------------------------------------------*/

/* flag set by timer ISR when it's time to measure touch */
volatile uint8_t time_to_measure_touch = 0u;

/* current time, set by timer ISR */
volatile uint16_t current_time_ms_touch = 0u;




/* PWM data variables, 16-bit wide, 12-bit used*/
long PWMData[16]= {
	//MSB        LSB
	0b000000001000,    // Channel 0
	0b000000010000,    // Channel 1
	0b000000100000,    // Channel 2
	0b000001000000,    // Channel 3
	0b000010000000,    // Channel 4
	0b000100000000,    // Channel 5
	0b001000000000,    // Channel 6
	0b010000000000,    // Channel 7
	0b100000000000,    // Channel 8
	0b100000000000,    // Channel 9
	0b010000000000,    // Channel 10
	0b001000000000,    // Channel 11
	0b000100000010,    // Channel 12
	0b000010000100,    // Channel 13
	0b000001001000,    // Channel 14
	0b000000110000     // Channel 15
};


/* PWM data variables, 16-bit wide, 12-bit used*/
long Mode5Table[15]= {
	//MSB        LSB
	0,    // Channel 0
	3,    // Channel 0
	6,    // Channel 0
	12,    // Channel 0
	24,    // Channel 0
	
	6,    // Channel 0
	12,    // Channel 0
	24,    // Channel 0
	0,    // Channel 0
	3,    // Channel 0
	
	24,    // Channel 0
	0,    // Channel 0
	3,    // Channel 0
	6,    // Channel 0
	12,    // Channel 0
};


void pca9685_init2(int address)
{
	/********************************************/
	/* Init code for the PCA9685                */
	/* Input:[address of the pc9685 to init]    */
	/* Output:[void]                            */
	/********************************************/
	i2c_start(address);                // Start
	i2c_write(MODE1);           // Mode 1 address
	i2c_write(PCA9685_RESTART);      // Setting mode to sleep so we can change the default PWM frequency
	i2c_stop();                 // Stop
	
	_delay_ms(10);
	
	i2c_start(address);                // Start
	i2c_write(MODE1);            // PWM frequency PRE_SCALE address
	i2c_write(PCA9685_AI);            // osc_clk/(4096*update_rate) // 25000000/(4096*1500)= 4.069 ~4
	i2c_stop();                 // Stop
	
	_delay_ms(10);
	
	i2c_start(address);                // Start
	i2c_write(MODE2);           // Mode 1 register address
	i2c_write(PCA9685_INVRT);            // Set to our preferred mode[ Reset, INT_CLK, Auto-Increment, Normal Mode]
	i2c_stop();                 // Stop
	
	_delay_ms(10);
	
	
	for(int i = 0; i <= LEDCOUNT; i++)
	{
		i2c_start(address);                // Start
		i2c_write(LED0_ON_L + 4 * i);
		i2c_write(0x00);
		i2c_write(0x00);
		i2c_write(0x10);
		i2c_write(0x50);
		i2c_stop();                 // Stop
		_delay_ms(10);
		
	}
	
}



void pca9685_send_all(int address) 
{ 
/********************************************/ 
/* Update all PWM register of PCA9685       */ 
/* Input:[address of the pc9685 to update]  */ 
/* Output:[void]                            */ 
/********************************************/ 
    int i = 0;                  // temp register for LEDCOUNT 
    int pwm;                    // temp register for PWM 
    for(i=0; i<=LEDCOUNT; i++)  // cycle through all 16 LED 
   
	 {
		 i2c_start(address);            // Start
		 i2c_write(LED0_ON_L + 4 * i);// start from LED0 address, each pwm constructed from
		 i2c_write(0x00);        // 4 12bit register, LED_ON_L
		 i2c_write(0x00);        // LED_ON_H
		 pwm = PWMData[i];       // update selected LED data in the array
		 i2c_write(pwm);         // LED_OFF_L
		 pwm = PWMData[i]>>8;    // update selected LED data in the array
		 i2c_write(pwm);         // LED_OFF_H
		 i2c_stop();             // Stop
		_delay_ms(60);           // delay at least 500 us

	 }
	 
} 

void pca9685_send(int address, long value, int led) 
{ 
/********************************************/ 
/* pca9685_send(long value, int led)        */ 
/* Send the 12 bit PWM data to the register */ 
/* Input[ 0to4095 pwm, 0to15LED channel]    */ 
/* Output[void]                             */ 
/********************************************/ 
    int pwm;                    // temp variable for PWM 
    if(value > 4095)            // if larger than 4095 than full on 
            value = 4095;       // cant be larger than 4095 
    if(led > 15)                // if LED larger than 15 than on other chip 
            led = 15;           //***** need to implement to select next pcs9685 
    i2c_start(address);                // Start 
    i2c_write(LED0_ON_L + 4 * led);  // select selected LED address 
    i2c_write(0x00);            // LED_ON_L 
    i2c_write(0x00);            // LED_ON_H 
    pwm = value;                // PWM value lo byte 
    i2c_write(pwm);             // LED_OFF_L 
    pwm = value>>8;             // pwm 16 bit long, now shift upper 8 to lower 8 
    i2c_write(pwm);             // LED_OFF_H 
    i2c_stop();                 // STop 
} 


void pca9685_brightness(int address, int percent, int led) 
{ 
/********************************************/ 
/* Calculate the register values for a      */ 
/* given percentage and update pca9685     */ 
/* Input:[address of the chip where LED is_ */ 
/* percent of PWM on period 0%to100%      _ */ 
/* LED to set brightness 0to15]             */ 
/* Output:[void]                            */ 
/********************************************/ 
    float off;                          // temp variable 
    const float onePercent = 40.96; 
    if (percent < 1) {                  // if % less than 1 than LED OFF 
    PWMData[led] = PCA9685_LED_OFF>>8;  // update data in array in case we use update all LED next 
    pca9685_send(address,0,led);        // update selected LED 
    return;                             // return from function 
    } 
    if (percent >= 100) {               // if % greater than 100 than LED ON 
    PWMData[led] = PCA9685_LED_ON>>8;   // update data in array 
    pca9685_send(address,4095,led);     // update selected LED 
    return;                             // return from function 
    } 
    off = onePercent * percent;         // different approach with float need to check if code faster than int32 way ? 
//    off = (int32)4096 * percent;        // calculate percent (max*percent)/100 
//    off = off / 100;                    // ex (4096*50%)=204800/100=2048 
//    x = make16(off>>8,off);             // make 16 of 32 ?! why.. dont care at this time 
    PWMData[led] = off;                 // update data array in case we update all LED next 
    pca9685_send(address,off,led);      // send it to pca9685 
} 

void PCA9685AllLedOff(int address) 
{ 
    i2c_start(address);                        // Start 
    i2c_write(ALL_LED_OFF_L);         // AllLED Off register 
    i2c_write(0b00000000);              // data 
    i2c_write(0b00010000);              // data 
    i2c_stop();                         // Stop 
} 









/*============================================================================
Name    :   main
------------------------------------------------------------------------------
Purpose :   main code entry point
Input   :   n/a
Output  :   n/a
Notes   :
============================================================================*/
int main( void )
{
	char modeStatus = 2; // Startup Mode
		

   /* initialize host app, pins, watchdog, etc */
    init_system();

    /* configure timer ISR to fire regularly */
    init_timer_isr();

	/* Initialize Touch sensors */
	touch_init();

	i2c_init();                             // initialize I2C library
	_delay_ms(60);           // delay
		
	pca9685_init2(PCA9685);
	_delay_ms(60);           // delay

	pca9685_brightness(PCA9685,50,15);

	__enable_interrupt();  // Enable interrupts for QMatrix (Per AVR1203)
	
	
    /* loop forever */
    for( ; ; )
    {
		
		_delay_ms(200); //let everything discharge?
		if (touch_measure() == 0x0001) // Check if we have a touch sensed
		{
			pca9685_brightness(PCA9685,0,15);
			_delay_ms(200);
			pca9685_brightness(PCA9685,50,15);
			_delay_ms(200);
		}
		else
		{
			
		
		
		

    /*  Time Non-critical host application code goes here  */
	
	
	
	
	
	
	
	
	
	
	
	
	// Check the current status of modeStatus (the mode button)
	// set port pin PORTA7 as input and leave the others pins
	// in their original state (inputs or outputs, it doesn't matter)
	DDRA &= ~(1 << PA7);
	
	if (PINA & (1<<PA7))
	{
		// If the mode pin is high (we have not pressed the button), do nothing
	}
	else // Otherwise set the mode
	{
		
		switch(modeStatus)
		{
			case 0:
			modeStatus = 1;
			break;
			
			case 1:
			modeStatus = 2;
			break;

			case 2:
			modeStatus = 3;
			break;

			case 3:
			modeStatus = 4;
			break;

			case 4:
			modeStatus = 5;
			break;

			case 5:
			modeStatus = 0;
			break;
			
			default:
			modeStatus = 2;
			break;
			
		}

	}
	
	
	//int mode5State = 0; // Not needed?
	
	
	
	// check what the current mode is, and modify the animation based on that
	
	if (modeStatus == 0) // 
	{
		
		for(int i = 3; i <= 5; i++)
		{
			pca9685_brightness(PCA9685,1,i);
		}
		
		_delay_ms(100);
		
		for(int i = 0; i <= 2; i++)
		{
			pca9685_brightness(PCA9685,1,i);
		}
		
		_delay_ms(100);
		
		for(int i = 6; i <= 8; i++)
		{
			pca9685_brightness(PCA9685,1,i);
		}
		
		_delay_ms(100);

		for(int i = 9; i <= 11; i++)
		{
			pca9685_brightness(PCA9685,1,i);
		}
		
		_delay_ms(100);


		for(int i = 12; i <= 14; i++)
		{
			pca9685_brightness(PCA9685,1,i);
		}
		
		_delay_ms(100);
		
		///////////////////////////////
		
		for(int i = 3; i <= 5; i++)
		{
			pca9685_brightness(PCA9685,25,i);
		}
		
		_delay_ms(100);
		
		for(int i = 0; i <= 2; i++)
		{
			pca9685_brightness(PCA9685,25,i);
		}
		
		_delay_ms(100);
		
		for(int i = 6; i <= 8; i++)
		{
			pca9685_brightness(PCA9685,25,i);
		}
		
		_delay_ms(100);

		for(int i = 9; i <= 11; i++)
		{
			pca9685_brightness(PCA9685,25,i);
		}
		
		_delay_ms(100);

		for(int i = 12; i <= 14; i++)
		{
			pca9685_brightness(PCA9685,25,i);
		}
		
		_delay_ms(100);
		
	}
	
	
	
	else if(modeStatus == 1)
	{
		
		// Blink Red
		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,20,i);
			pca9685_brightness(PCA9685,0,i+1);
			pca9685_brightness(PCA9685,0,i+2);
		}
		
		_delay_ms(250);
		
		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,0,i);
			pca9685_brightness(PCA9685,0,i+1);
			pca9685_brightness(PCA9685,0,i+2);
		}
		
		_delay_ms(250);
		
		// Blink Blue
		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,0,i);
			pca9685_brightness(PCA9685,20,i+1);
			pca9685_brightness(PCA9685,0,i+2);
		}
		
		_delay_ms(250);


		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,0,i);
			pca9685_brightness(PCA9685,0,i+1);
			pca9685_brightness(PCA9685,0,i+2);
		}
		
		_delay_ms(250);

		// Blink Green
		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,0,i);
			pca9685_brightness(PCA9685,0,i+1);
			pca9685_brightness(PCA9685,20,i+2);
		}
		
		_delay_ms(250);


		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,0,i);
			pca9685_brightness(PCA9685,0,i+1);
			pca9685_brightness(PCA9685,0,i+2);
		}
		
		_delay_ms(250);

		
		
		
		
	}
	else if(modeStatus == 2)
	{
		
		// Turn off all LEDs before sequencing
		for(int i = 1; i <= LEDCOUNT - 1; i++)
		{
			pca9685_brightness(PCA9685,0,i);
		}
		
		//Sequence through turning one LED chip on, then off, and proceeding
		pca9685_brightness(PCA9685,1,3);
		pca9685_brightness(PCA9685,1,4);
		pca9685_brightness(PCA9685,1,5);
		_delay_ms(200);
		pca9685_brightness(PCA9685,0,3);
		pca9685_brightness(PCA9685,0,4);
		pca9685_brightness(PCA9685,0,5);
		_delay_ms(200);
		
		pca9685_brightness(PCA9685,1,0);
		pca9685_brightness(PCA9685,1,1);
		pca9685_brightness(PCA9685,1,2);
		_delay_ms(100);
		pca9685_brightness(PCA9685,0,0);
		pca9685_brightness(PCA9685,0,1);
		pca9685_brightness(PCA9685,0,2);
		_delay_ms(300);

		pca9685_brightness(PCA9685,1,6);
		pca9685_brightness(PCA9685,1,7);
		pca9685_brightness(PCA9685,1,8);
		_delay_ms(100);
		pca9685_brightness(PCA9685,0,6);
		pca9685_brightness(PCA9685,0,7);
		pca9685_brightness(PCA9685,0,8);
		_delay_ms(300);

		pca9685_brightness(PCA9685,1,9);
		pca9685_brightness(PCA9685,1,10);
		pca9685_brightness(PCA9685,1,11);
		_delay_ms(100);
		pca9685_brightness(PCA9685,0,9);
		pca9685_brightness(PCA9685,0,10);
		pca9685_brightness(PCA9685,0,11);
		_delay_ms(300);


		pca9685_brightness(PCA9685,1,12);
		pca9685_brightness(PCA9685,1,13);
		pca9685_brightness(PCA9685,1,14);
		_delay_ms(200);
		pca9685_brightness(PCA9685,0,12);
		pca9685_brightness(PCA9685,0,13);
		pca9685_brightness(PCA9685,0,14);
		_delay_ms(200);
		
		
		pca9685_brightness(PCA9685,1,9);
		pca9685_brightness(PCA9685,1,10);
		pca9685_brightness(PCA9685,1,11);
		_delay_ms(100);
		pca9685_brightness(PCA9685,0,9);
		pca9685_brightness(PCA9685,0,10);
		pca9685_brightness(PCA9685,0,11);
		_delay_ms(300);
		
		
		pca9685_brightness(PCA9685,1,6);
		pca9685_brightness(PCA9685,1,7);
		pca9685_brightness(PCA9685,1,8);
		_delay_ms(100);
		pca9685_brightness(PCA9685,0,6);
		pca9685_brightness(PCA9685,0,7);
		pca9685_brightness(PCA9685,0,8);
		_delay_ms(300);			
				
		pca9685_brightness(PCA9685,1,0);
		pca9685_brightness(PCA9685,1,1);
		pca9685_brightness(PCA9685,1,2);
		_delay_ms(100);
		pca9685_brightness(PCA9685,0,0);
		pca9685_brightness(PCA9685,0,1);
		pca9685_brightness(PCA9685,0,2);
		_delay_ms(300);
		
		
		
	}
	else if(modeStatus == 3)
	{
		
		// All LEDs off
		
		
		// Turn off all LEDs
		for(int i = 1; i <= LEDCOUNT - 1; i++)
		{
			pca9685_brightness(PCA9685,0,i);
		}
		
		_delay_ms(500);
	}
	
	
	
	else if(modeStatus == 4)
	{
		
		// Blink all FULL POWER
		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,100,i);
			pca9685_brightness(PCA9685,100,i+1);
			pca9685_brightness(PCA9685,100,i+2);
		}
		
		_delay_ms(300);
				
		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,0,i);
			pca9685_brightness(PCA9685,0,i+1);
			pca9685_brightness(PCA9685,0,i+2);
		}
		
		_delay_ms(500);		
	}
	
	
	
	
	
	
	else if(modeStatus == 5)
	{
		
		// Randomish colors
		
		pca9685_brightness(PCA9685,2,0); // 1
		pca9685_brightness(PCA9685,5,1); // 2
		pca9685_brightness(PCA9685,0,2); // 3
		pca9685_brightness(PCA9685,5,3); // 4
		pca9685_brightness(PCA9685,0,4); // 5
		pca9685_brightness(PCA9685,5,5); // 1
		pca9685_brightness(PCA9685,0,6); // 2
		pca9685_brightness(PCA9685,5,7); // 3
		pca9685_brightness(PCA9685,0,8); // 4
		pca9685_brightness(PCA9685,5,9); // 5
		pca9685_brightness(PCA9685,0,10); // 1
		pca9685_brightness(PCA9685,5,11); // 2
		pca9685_brightness(PCA9685,2,12); // 3
		pca9685_brightness(PCA9685,0,13); // 4
		pca9685_brightness(PCA9685,0,14); // 5
		
		_delay_ms(200);
		
		
		for(int i = 0; i <= LEDCOUNT - 1; i = i+3)
		{
			pca9685_brightness(PCA9685,0,i);
			pca9685_brightness(PCA9685,0,i+1);
			pca9685_brightness(PCA9685,0,i+2);
		}
		
		_delay_ms(400);
	}
	
	
		} // Done with if/else for touch sense		
	
	
    }
}

