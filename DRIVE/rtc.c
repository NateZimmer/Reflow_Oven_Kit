/*
 * rtc.c
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */


#include "msp430g2553.h"
#include "rtc.h"
#include "timer.h"



//static int gseq = 33;
//static int rseq = 0;
//static int bseq = 66;

uint16_t counts=0;
static time_stamp system_time={0,0,0};

uint16_t reflow_timer=0;
uint8_t task_flags=0;

void rtc_setup()
{
	WDTCTL = WDT_MDLY_0_5;	// WDT 0.015625ms or 64 Hz
	IE1 |= WDTIE;         	// Enable WDT interrupt
	__enable_interrupt();
}

void check_scheduler()
{
	static uint16_t counts_prev=0;

	if(counts_prev != counts)
	{
		if(task_500ms)
			task_flags |=task_500ms_flag;

		if(task_250ms)
			task_flags |=task_250ms_flag;

		if(task_125ms)
			task_flags |=task_125ms_flag;

		if(task_62ms)
		{
			task_flags |=task_62ms_flag;
		}

		if(task_32ms)
		{
			task_flags |=task_32ms_flag;
		}

		if(task_15ms)
			task_flags |=task_15ms_flag;

		if(task_graph_ud)
			task_flags |=graph_update;
	}

	counts_prev = counts;


}


// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
	counts++; // Interrupts every 1/64s

	reflow_timer++;
	if(counts>31250)
	{
		counts=0;
		system_time.secs++;
		if(system_time.secs>59)
			{
				system_time.minutes++;
				system_time.secs=0;
			}
			if(system_time.minutes>59)
			{
				system_time.hours++;
				system_time.hours %=12;
				system_time.minutes=0;
			}
	}

	if((counts % 500)==0)
	{
		check_scheduler();
	}

}

uint8_t get_system_seconds()
{
	return system_time.secs;
}

void get_system_time_string(char * buffer)
{
	get_time_long(buffer,&system_time); // format hours:mins:secs
}



