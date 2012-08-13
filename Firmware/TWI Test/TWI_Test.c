/*
 * TWI_Test.c
 *
 * Created: 7/4/2012 11:11:36 PM
 *  Author: Jack
 */ 


#include <avr/io.h>
#include <util/delay.h>


#ifndef F_CPU
	#define F_CPU 20000000UL	      // Sets up the default speed for delay.h
#endif

#include "i2cmaster.h"



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
#define LED0_ON_H 0x07
#define LED0_OFF_L 0x08
#define LED0_OFF_H 0x09
#define LED1_ON_L 0x0A
#define LED1_ON_H 0x0B
#define LED1_OFF_L 0x0C
#define LED1_OFF_H 0x0D
#define LED2_ON_L 0x0E
#define LED2_ON_H 0x0F
#define LED2_OFF_L 0x10
#define LED2_OFF_H 0x11
#define LED3_ON_L 0x12
#define LED3_ON_H 0x13
#define LED3_OFF_L 0x14
#define LED3_OFF_H 0x15
#define LED4_ON_L 0x16
#define LED4_ON_H 0x17
#define LED4_OFF_L 0x18
#define LED4_OFF_H 0x19
#define LED5_ON_L 0x1A
#define LED5_ON_H 0x1B
#define LED5_OFF_L 0x1C
#define LED5_OFF_H 0x1D
#define LED6_ON_L 0x1E
#define LED6_ON_H 0x1F
#define LED6_OFF_L 0x20
#define LED6_OFF_H 0x21
#define LED7_ON_L 0x22
#define LED7_ON_H 0x23
#define LED7_OFF_L 0x24
#define LED7_OFF_H 0x25
#define LED8_ON_L 0x26
#define LED8_ON_H 0x27
#define LED8_OFF_L 0x28
#define LED8_OFF_H 0x29
#define LED9_ON_L 0x2A
#define LED9_ON_H 0x2B
#define LED9_OFF_L 0x2C
#define LED9_OFF_H 0x2D
#define LED10_ON_L 0x2E
#define LED10_ON_H 0x2F
#define LED10_OFF_L 0x30
#define LED10_OFF_H 0x31
#define LED11_ON_L 0x32
#define LED11_ON_H 0x33
#define LED11_OFF_L 0x34
#define LED11_OFF_H 0x35
#define LED12_ON_L 0x36
#define LED12_ON_H 0x37
#define LED12_OFF_L 0x38
#define LED12_OFF_H 0x39
#define LED13_ON_L 0x3A
#define LED13_ON_H 0x3B
#define LED13_OFF_L 0x3C
#define LED13_OFF_H 0x3D
#define LED14_ON_L 0x3E
#define LED14_ON_H 0x3F
#define LED14_OFF_L 0x40
#define LED14_OFF_H 0x41
#define LED15_ON_L 0x42
#define LED15_ON_H 0x43
#define LED15_OFF_L 0x44
#define LED15_OFF_H 0x45

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
	
	_delay_loop_2(150);           // Required 50 us delay
	
	i2c_start(address);                // Start
	i2c_write(MODE1);            // PWM frequency PRE_SCALE address
	i2c_write(PCA9685_AI);            // osc_clk/(4096*update_rate) // 25000000/(4096*1500)= 4.069 ~4
	i2c_stop();                 // Stop
	
	_delay_loop_2(150);           // delay at least 500 us
	
	i2c_start(address);                // Start
	i2c_write(MODE2);           // Mode 1 register address
	i2c_write(PCA9685_INVRT);            // Set to our preferred mode[ Reset, INT_CLK, Auto-Increment, Normal Mode]
	i2c_stop();                 // Stop
	
	_delay_loop_2(10000);           // delay at least 500 us
	_delay_loop_2(10000);           // delay at least 500 us
	
	
	for(int i = 0; i <= LEDCOUNT; i++)
	{
		i2c_start(address);                // Start
		i2c_write(LED0_ON_L + 4 * i);
		i2c_write(0x00);
		i2c_write(0x00);
		i2c_write(0x10);
		i2c_write(0x50);
		i2c_stop();                 // Stop
		_delay_loop_2(10000);           // delay at least 500 us
		_delay_loop_2(10000);           // delay at least 500 us
		
	}
	
}



void pca9685_init(int address)
{
	/********************************************/
	/* Init code for the PCA9685                */
	/* Input:[address of the pc9685 to init]    */
	/* Output:[void]                            */
	/********************************************/
	i2c_start(address);                // Start
	i2c_write(MODE1);           // Mode 1 address
	i2c_write(0b00110001);      // Setting mode to sleep so we can change the default PWM frequency
	i2c_stop();                 // Stop
	_delay_loop_2(150);           // Required 50 us delay
	i2c_start(address);                // Start
	i2c_write(0xfe);            // PWM frequency PRE_SCALE address
	i2c_write(0x04);            // osc_clk/(4096*update_rate) // 25000000/(4096*1500)= 4.069 ~4
	i2c_stop();                 // Stop
	_delay_loop_2(150);           // delay at least 500 us
	i2c_start(address);                // Start
	i2c_write(MODE1);           // Mode 1 register address
	i2c_write(0xa1);            // Set to our preferred mode[ Reset, INT_CLK, Auto-Increment, Normal Mode]
	i2c_stop();                 // Stop
	_delay_loop_2(150);           // delay at least 500 us
	i2c_start(address);                // Start
	i2c_write(MODE2);           // Mode2 register address
	i2c_write(0b00000100);      // Set to our preferred mode[Output logic state not inverted, Outputs change on STOP,
	i2c_stop();                 // totem pole structure, When OE = 1 (output drivers not enabled), LEDn = 0]
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
		 _delay_loop_2(150);           // delay at least 500 us

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




int main(void)
{
	
	char modeStatus = 2;
	
	
	i2c_init();                             // initialize I2C library
	_delay_loop_2(100);           // delay
	
	pca9685_init2(PCA9685);
	_delay_loop_2(10000);           // delay

	pca9685_brightness(PCA9685,50,15);

	while(1)
	{
		
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
				modeStatus = 0;
				break;
				
				default:
				modeStatus = 2;
				break;
				
			}			

		}
		
		
		
		
		if (modeStatus == 0) // check what the current mode is, and modify the animation based on that
		{			
		
			for(int i = 3; i <= 5; i++)
			{
				pca9685_brightness(PCA9685,1,i);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}
		
			for(int i = 0; i <= 2; i++)
			{
				pca9685_brightness(PCA9685,1,i);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}
		
			for(int i = 6; i <= LEDCOUNT - 1; i++)
			{
				pca9685_brightness(PCA9685,1,i);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}
		
			///////////////////////////////
		
			for(int i = 3; i <= 5; i++)
			{
				pca9685_brightness(PCA9685,25,i);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}
		
			for(int i = 0; i <= 2; i++)
			{
				pca9685_brightness(PCA9685,25,i);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}
		
			for(int i = 6; i <= LEDCOUNT - 1; i++)
			{
				pca9685_brightness(PCA9685,25,i);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(1000);           // delay

			}
			
			
		}
		else if(modeStatus == 1)
		{
			
			// Blink Red
			for(int i = 1; i <= LEDCOUNT - 1; i = i+3)
			{
				pca9685_brightness(PCA9685,25,i);
				pca9685_brightness(PCA9685,0,i+1);
				pca9685_brightness(PCA9685,0,i+2);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}
			
			
			for(int i = 1; i <= LEDCOUNT - 1; i = i+3)
			{
				pca9685_brightness(PCA9685,0,i);
				pca9685_brightness(PCA9685,0,i+1);
				pca9685_brightness(PCA9685,0,i+2);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}
			
			// Blink Blue
			for(int i = 1; i <= LEDCOUNT - 1; i = i+3)
			{
				pca9685_brightness(PCA9685,0,i);
				pca9685_brightness(PCA9685,25,i+1);
				pca9685_brightness(PCA9685,0,i+2);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}


			for(int i = 1; i <= LEDCOUNT - 1; i = i+3)
			{
				pca9685_brightness(PCA9685,0,i);
				pca9685_brightness(PCA9685,0,i+1);
				pca9685_brightness(PCA9685,0,i+2);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}

			// Blink Green
			for(int i = 1; i <= LEDCOUNT - 1; i = i+3)
			{
				pca9685_brightness(PCA9685,0,i);
				pca9685_brightness(PCA9685,0,i+1);
				pca9685_brightness(PCA9685,25,i-1);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}


			for(int i = 1; i <= LEDCOUNT - 1; i = i+3)
			{
				pca9685_brightness(PCA9685,0,i);
				pca9685_brightness(PCA9685,0,i+1);
				pca9685_brightness(PCA9685,0,i-1);
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay
				_delay_loop_2(10000);           // delay

			}

			
			
			
			
		}		
		else if(modeStatus == 2)
		{
			
			// Blink Low Power
			
			
			// Turn off all LEDs
			for(int i = 1; i <= LEDCOUNT - 1; i++)
			{
				pca9685_brightness(PCA9685,0,i);
			}
			
			//Sequence through turning one LED chip on, then off, and proceeding
			pca9685_brightness(PCA9685,1,3);
			pca9685_brightness(PCA9685,1,4);
			pca9685_brightness(PCA9685,1,5);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,3);
			pca9685_brightness(PCA9685,0,4);
			pca9685_brightness(PCA9685,0,5);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			
			pca9685_brightness(PCA9685,1,0);
			pca9685_brightness(PCA9685,1,1);
			pca9685_brightness(PCA9685,1,2);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,0);
			pca9685_brightness(PCA9685,0,1);
			pca9685_brightness(PCA9685,0,2);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay

			pca9685_brightness(PCA9685,1,6);
			pca9685_brightness(PCA9685,1,7);
			pca9685_brightness(PCA9685,1,8);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,6);
			pca9685_brightness(PCA9685,0,7);
			pca9685_brightness(PCA9685,0,8);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay


			pca9685_brightness(PCA9685,1,9);
			pca9685_brightness(PCA9685,1,10);
			pca9685_brightness(PCA9685,1,11);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,9);
			pca9685_brightness(PCA9685,0,10);
			pca9685_brightness(PCA9685,0,11);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay


			pca9685_brightness(PCA9685,1,12);
			pca9685_brightness(PCA9685,1,13);
			pca9685_brightness(PCA9685,1,14);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,12);
			pca9685_brightness(PCA9685,0,13);
			pca9685_brightness(PCA9685,0,14);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
		
			
			pca9685_brightness(PCA9685,1,9);
			pca9685_brightness(PCA9685,1,10);
			pca9685_brightness(PCA9685,1,11);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,9);
			pca9685_brightness(PCA9685,0,10);
			pca9685_brightness(PCA9685,0,11);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
		
			
			pca9685_brightness(PCA9685,1,6);
			pca9685_brightness(PCA9685,1,7);
			pca9685_brightness(PCA9685,1,8);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,6);
			pca9685_brightness(PCA9685,0,7);
			pca9685_brightness(PCA9685,0,8);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			
			
			pca9685_brightness(PCA9685,1,0);
			pca9685_brightness(PCA9685,1,1);
			pca9685_brightness(PCA9685,1,2);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			pca9685_brightness(PCA9685,0,0);
			pca9685_brightness(PCA9685,0,1);
			pca9685_brightness(PCA9685,0,2);
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			
				
			
		}
		else if(modeStatus == 3)
		{
			
			// All LEDs off
			
			
			// Turn off all LEDs
			for(int i = 1; i <= LEDCOUNT - 1; i++)
			{
				pca9685_brightness(PCA9685,0,i);
			}		
			
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			_delay_loop_2(10000);           // delay
			}		
			
	}
	
	

}