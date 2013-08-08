/*
 * led.c
 *
 *  Created on: Jun 16, 2013
 *      Author: Nate
 */


#include "stdint.h"
#include "led.h"
#include "timer.h"
#include "../Oven/oven_control.h"
#include "../OS/time.h"
#include "../LCD/touch.h"
#include "../LCD/colorLCD.h"

static time_stamp idle_timer={0,5,0};

void reset_idle_timer()
{
	idle_timer.minutes=5;
	idle_timer.secs=0;
	LCD_BLIGHT_OUTPUT |= LCD_BLIGHT;
	LED_ANI_OFF();
	CHARGE_ON();
}


void led_state_machine()
{
	uint16_t xval =0;
	uint16_t yval =0;
	TOUCH_VAL(&xval, &yval);

	if(oven_status==Oven_Idle)
	{
		if(!((xval + yval)==0)) // Timeout for touch
		{
			reset_idle_timer();
		}
		else
		{
			if(count_down_time_idle(&idle_timer))
			{
				LCD_BLIGHT_OUTPUT &= ~LCD_BLIGHT;
				LED_ANI_ON();
				CHARGE_OFF();
			}
		}
	}
	if(oven_status==Oven_Alarm)
	{
		if(check_for_lead_profile())
		{
			if((get_reflow_time_minutes()*60 + get_reflow_time_seconds())>90)
					{
						BUZZER_ON();
					}
			else
				BUZZER_OFF();
		}
		else
		{
			if((get_reflow_time_minutes()*60 + get_reflow_time_seconds())>80)
								{
									BUZZER_ON();
								}
			else
				BUZZER_OFF();
		}


	}

}

