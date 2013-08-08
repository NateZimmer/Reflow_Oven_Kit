/*
 * oven_control.c
 *
 *  Created on: Apr 13, 2013
 *      Author: Nate
 */

#include "oven_control.h"
#include "oven.h"
#include "msp430g2553.h"
#include "profile_lead.h"
#include "../OS/time.h"
#include "profile_pb_free.h"
#include "stdbool.h"


static bool leaded=true;
static time_stamp reflow_timer={0,6,0};
static uint16_t profile_count =0;


const uint8_t total_counts = 64; // period
enum oven_state oven_status = Oven_Idle;


void set_profile_leaded()
{
	leaded=true;
}

void set_profile_pb_free()
{
	leaded=false;
}

uint8_t check_for_lead_profile()
{
	 return (uint8_t)leaded;
}

void compensator(int setpoint_temp, int current_temp) {

	static uint8_t current_counts = 0;
	static uint8_t time_on_counts = 10; //time on out of period, initial value set
	uint8_t local_setpoint = setpoint_temp;
	uint8_t local_ctemp = current_temp;
	int set_on_counts = 0;
	uint8_t drive_strength = 1;

	drive_strength = (local_setpoint - local_ctemp);

	if (drive_strength < 3) {
		drive_strength = 3;
	} else if (drive_strength > total_counts) {
		drive_strength = total_counts;
	}

	set_on_counts = drive_strength;

	if (current_counts < 1) {
		current_counts = total_counts;
		time_on_counts = set_on_counts;
	}

	if (time_on_counts) // If time_on_counts = non zero, decrement and turn on output
	{
		OVEN_ON;
		time_on_counts--;
	} else {
		OVEN_OFF;
	}

	current_counts--;

}

#define min_count		0
#define max_count		64
#define gain			4

void new_compensator(uint8_t current_temp, uint8_t set_point)
{
	int16_t error =gain*(set_point-current_temp);
	static unsigned int cycle_counts=max_count;
	static unsigned int time_on=max_count;

	if(error<min_count)
	{
		error=min_count;	// Is error smaller than min counts?
	}
	if(error>max_count)
	{
		error=max_count; 	// Is error larger than max counts?
	}
	//if(error>error_previous)
	//{
	//	time_on+= error - error_previous;	// If error has changed from previous call of function
	//}

	if(time_on>1)
	{
		OVEN_ON;
		time_on--;
		if(time_on<1)
		time_on=1;
	}
	else
		OVEN_OFF;

	if(cycle_counts<1)				// if end of cycle, refresh duty cycle
	{
		cycle_counts+=max_count;
		time_on=error;
	}


	cycle_counts--; // End of cycle

}

uint8_t start_oven()
{
	if(oven_status==Oven_Idle)
	{
		reflow_timer.minutes=6;
		reflow_timer.secs=0;
		oven_status=Oven_Reflowing;
		profile_count=0;
		return 1;
	}
	else
	{
		return 0;
	}
}

void stop_oven()
{
	oven_status=Oven_Cooldown;
	OVEN_OFF;
}

void run_oven_state_machine()
{
	uint16_t oven_temp =0;
	oven_temp= get_temp();

	if((oven_temp>50) & (oven_status==Oven_Idle))
	{
		oven_status=Oven_Cooldown;
	}

	if(oven_temp>350)
	{
		oven_status=Oven_Error;
	}
	else if((oven_status==Oven_Alarm) || (oven_status==Oven_Reflowing))
	{
		if(count_down_time(&reflow_timer))
		{
			profile_count++;
		}
			if(leaded)
			{
				new_compensator(oven_temp,profile[profile_count]);
				if((profile_count)==260)
				{
					oven_status=Oven_Alarm;
				}
			}
			else
			{
				new_compensator(oven_temp,profileb[profile_count]);
				if((profile_count)==270)
				{
					oven_status=Oven_Alarm;
				}
			}
		if(profile_count>358)
		{
			oven_status=Oven_Cooldown;
			OVEN_OFF;
			reflow_timer.secs=0;
		}
	}
	else if((oven_status==Oven_Cooldown) && (oven_temp<50))
	{
		oven_status=Oven_Idle;
	}

}

uint16_t get_profile_temp()
{
	if(leaded)
		return profile[profile_count];
	else
		return profileb[profile_count];
}

void get_reflow_time_string(char * buffer)
{
	get_time_short(buffer,&reflow_timer); // format hours:mins:secs
}

uint8_t get_reflow_time_minutes()
{
	return reflow_timer.minutes;
}

uint8_t get_reflow_time_seconds()
{
	return reflow_timer.secs;
}

