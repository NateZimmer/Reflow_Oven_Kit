/*
 * oven.c
 *
 *  Created on: Apr 12, 2013
 *      Author: Nate
 */

#include "oven.h"

#include "../DRIVE/GPIO.h"
#include "../DRIVE/spi.h"


static uint16_t g_oven_temp=0;
#define adc_offset 220 // offset roughly 70 mv



uint8_t get_internal_temp()
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
	   IntDegC-=4;
	   return IntDegC;
}

#define mV_per_deg_c 0.04
#define gain 220

uint16_t get_Tcouple_value()
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
	   tval*=3.2227;
	   tval>>=3;
	   adc_current=get_internal_temp();
	   if(tval>adc_offset)
		   tval=(tval - adc_offset)/(gain*mV_per_deg_c); // 0.04mV/degC * 220gain = 8.8
	   else
		   tval=0;

	   tval+=adc_current;
	   return tval;
}



void update_temp()
{
	 g_oven_temp=get_Tcouple_value();
}



uint16_t get_temp()
{
	return g_oven_temp;
}

void get_temp_str(uint16_t heatdata, char *display_temp)
{

uint16_t temps_dat= heatdata;

if(temps_dat>350)
{
	//display_temp="Error";
	display_temp[0]='E';
	display_temp[1]='r';
	display_temp[2]='r';
	display_temp[3]='o';
	display_temp[4]='r';
	display_temp[5]='\0';
}
else
{
	display_temp[0]= (temps_dat / 100) + '0';
	temps_dat = (temps_dat % 100);
	display_temp[1]= (temps_dat / 10) + '0';
	temps_dat = (temps_dat % 10);
	display_temp[2]= (temps_dat) + '0';
	display_temp[3] = 'C';
	display_temp[4] = '\0';
}

}
