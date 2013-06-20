/*
 * os.c
 *
 *  Created on: Apr 12, 2013
 *      Author: Nate
 */


#include "os.h"
#include "../DRIVE/rtc.h"
#include "../DRIVE/timer.h"
#include "../LCD/colorLCD.h"
#include "../LCD/touch.h"
#include "../LCD/gui.h"
#include "../DRIVE/GPIO.h"
#include "../DRIVE/rtc.h"
#include "../OVEN/oven.h"
#include "../OVEN/oven_control.h"
#include "../DRIVE/led.h"

// System count time

// 1  count  =  15.6ms
// 2  counts =  31.6ms
// 4  counts =  62.5ms
// 8  counts = 125.0ms
// 16 counts = 250.0ms
// 32 counts = 500.0ms

void run_tasks()
{
	if(task_flags & task_15ms_flag)
	{

		Page_Event_Handler();
		led_state_machine();
		run_oven_state_machine();
		task_flags &=~task_15ms_flag;

	}

	if(task_flags & task_32ms_flag)
	{
		task_flags &=~task_32ms_flag;
		update_temp();

	}

	if(task_flags & task_62ms_flag)
	{
		GLED_Sequence();
		RLED_Sequence();
		BLED_Sequence();

		task_flags &=~task_62ms_flag;

	}


	if(task_flags & task_250ms_flag)
	{

		task_flags &=~task_250ms_flag;
	}

	if(task_flags & task_500ms_flag)
	{
		setColor16(COLOR_16_WHITE);
		get_system_time_string(text_buffer);
		drawString(10,160,text_buffer);
		print_oven_data();
		if(task_flags & graph_update)
		{
			update_graph();
			task_flags &= ~graph_update;
		}

		task_flags &=~task_500ms_flag;
		//RLED_OUT ^= RLED;
	}

}

void Start_OS()
{
	while(1)
	{
		run_tasks();
	}

}

