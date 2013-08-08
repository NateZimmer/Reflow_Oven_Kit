/*
 * calibration.c
 *
 *  Created on: Jul 20, 2013
 *      Author: Nate
 */


#include "calibration.h"
#include "../DRIVE/adc.h"


static unsigned int * const cal_vals = (unsigned int *)(0x1000); //set pointer to address of segment D
static uint16_t temp_offset=0;
static uint16_t adc_offset=0;

void init_cal()
{
	if(*cal_vals==0xFFFF)
	{
		adc_offset=300;
	}
	else
	{
	    adc_offset = *cal_vals;
	}

	if(*(cal_vals+1)==0xFFFF)
	{
		temp_offset=4;
	}
	else
	{
		temp_offset = *(cal_vals+1);
	}
}

void set_cal(uint8_t cal_val)
{
	volatile unsigned int i=0;
	volatile uint16_t adc_val=0;
	volatile uint16_t temp_val=0;
	adc_val = get_adc_val();
	temp_val = get_temp_raw() -cal_val;
	WDTCTL = WDTPW + WDTHOLD;
	_disable_interrupts();
	FCTL2 = FWKEY + FSSEL1 + FN5+FN3;
	_delay_cycles(10000);
	FCTL1 = FWKEY + ERASE;                    // Set Erase bit
	FCTL3 = FWKEY;                            // Clear Lock bit
	 for (i=0; i<32; i++)
	  {
	    *(cal_vals+i)= 0;                   // Write value to flash
	  }
    FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation
    *cal_vals =adc_val;
    *(cal_vals+1) = temp_val;
    FCTL1 = FWKEY;                            // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
    _delay_cycles(10000);
	WDTCTL = WDT_MDLY_0_5;	// WDT 0.015625ms or 64 Hz
	IE1 |= WDTIE;         	// Enable WDT interrupt
    _enable_interrupts();
    adc_offset = *cal_vals;
    temp_offset = *(cal_vals+1);
}

uint16_t get_cal_adc_offset()
{
	return adc_offset;
}

int16_t get_cal_temp_offset()
{
	return temp_offset;
}
