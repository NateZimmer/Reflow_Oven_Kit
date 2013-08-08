/*
 * oven.c
 *
 *  Created on: Apr 12, 2013
 *      Author: Nate
 */

#include "oven.h"

#include "../DRIVE/GPIO.h"
#include "../DRIVE/spi.h"
#include "../DRIVE/adc.h"
#include "calibration.h"


static uint16_t g_oven_temp=0;
#define adc_offset 350 // offset roughly 70 mv
#define adc_c


#define mV_per_deg_c 0.04
#define gain 220

uint16_t get_Tcouple_value()
{

	uint16_t tval=0;
	uint16_t board_temp=get_temp_raw();
	uint16_t thermocouple_mv=get_adc_val();

	if(thermocouple_mv>get_cal_adc_offset())
	{
		thermocouple_mv = thermocouple_mv - get_cal_adc_offset();
	}
	else
	{
		thermocouple_mv=0;
	}

	if(board_temp>get_cal_temp_offset())
	{
		board_temp=board_temp-get_cal_temp_offset();
	}
	else
	{
		board_temp=0;
	}

	tval=(thermocouple_mv)/(gain*mV_per_deg_c) + board_temp ; // 0.04mV/degC * 220gain = 8.8

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
