/*
 * time.c
 *
 *  Created on: Jun 16, 2013
 *      Author: Nate
 */


#include "time.h"
#include "../DRIVE/rtc.h"


uint8_t count_down_time(time_stamp *present_time)
{
	static uint8_t previous_seconds=0;
	uint8_t return_val=0;
	if((get_system_seconds())!=previous_seconds)
	{
		if(present_time->secs==0)
		{
			if(present_time->minutes==0)
			{
				if(present_time->hours==0)
				{

				}
				else
				{
					present_time->hours--;
					present_time->minutes=59;
					present_time->secs=59;
				}
			}
			else
			{
				present_time->minutes--;
				present_time->secs=59;
			}
		}
		else
		{
			present_time->secs--;
		}
		return_val= 1;
	}
	else
	{
		return_val= 0;
	}
	previous_seconds=get_system_seconds();
	return return_val;
}

uint8_t count_down_time_idle(time_stamp *present_time)
{
	static uint8_t previous_seconds=0;
	uint8_t return_val=0;
	if((get_system_seconds())!=previous_seconds)
	{
		if(present_time->secs==0)
		{
			if(present_time->minutes==0)
			{
				if(present_time->hours==0)
				{
					return_val= 1;
				}
				else
				{
					present_time->hours--;
					present_time->minutes=59;
					present_time->secs=59;
				}
			}
			else
			{
				present_time->minutes--;
				present_time->secs=59;
			}
		}
		else
		{
			present_time->secs--;
		}
	}
	else
	{
		return_val= 0;
	}
	previous_seconds=get_system_seconds();
	return return_val;
}


void get_time_long(char * buffer, time_stamp *present_time) // format hours:mins:secs
{
	unsigned int local_data=present_time->hours;
	buffer[0]= local_data/10 + '0';
	local_data %=10;
	buffer[1]= local_data + '0';
	buffer[2]= ':';
	local_data =present_time->minutes;
	buffer[3]= local_data/10 +'0';
	local_data %=10;
	buffer[4]= local_data +'0';
	buffer[5]= ':';
	local_data = present_time->secs;
	buffer[6] = local_data/10 + '0';
	local_data %= 10;
	buffer[7]= local_data +'0';
	buffer[8]=0;
}

void get_time_short(char * buffer, time_stamp *present_time) // format hours:mins:secs
{
	buffer[0]= present_time->minutes + '0';
	buffer[1]= ':';
	buffer[2]= (present_time->secs)/10 + '0';
	buffer[3]= (present_time->secs)%10 + '0';
	buffer[4]=0;
}
