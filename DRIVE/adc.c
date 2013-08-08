/*
 * adc.c
 *
 *  Created on: Jul 20, 2013
 *      Author: Nate
 */


#include "adc.h"


int16_t get_temp_raw()
{
	unsigned int temp =0;
	unsigned int IntDegC =0;
	int i=0;

	ADC10CTL0 = 0;
	ADC10CTL1 = INCH_10 + ADC10DIV_3;         // Temp Sensor ADC10CLK/48
	ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON;
    while (ADC10CTL1 & BUSY);
	   for(i=0;i<32;i++)
	   {
	    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	    while (ADC10CTL1 & BUSY);
	   temp = ADC10MEM;
	    //IntDegC += ((temp - 673) * 423)>>10;

	   IntDegC += (((27069L * temp) - 18169625L) >> 16);

	   }
	   IntDegC>>=5;
	   return IntDegC;
}

uint16_t get_adc_val()
{
	uint16_t tval =0;
	uint16_t adc_current=0;
	uint8_t i=0;

	ADC10CTL0 = 0;
	while (ADC10CTL1 & BUSY);
	ADC10CTL0 = ADC10ON + SREF_0 + ADC10SHT_3; // ADC10ON, interrupt enabled
	ADC10CTL1 = INCH_3+ ADC10DIV_2 +SHS_0;                       // input A1
	ADC10AE0 |= BIT3;                         // PA.1 ADC option select
	while (ADC10CTL1 & BUSY);
	   for(i=0;i<8;i++)
	   {
		ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	   while (ADC10CTL1 & BUSY);
	   adc_current = ADC10MEM;
	   //adc_val += (adc_current*3) + (adc_current>>1) + (adc_current>>6) ;
	   tval += adc_current; // 3600/1024
	   }
	   tval*=3.2227; // convert to mv
	   tval>>=3; // offset average
	   _delay_cycles(1);
	   return tval;
}
