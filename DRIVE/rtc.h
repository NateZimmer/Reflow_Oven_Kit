/*
 * rtc.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */

#ifndef RTC_H_
#define RTC_H_

#include "stdint.h"

#include "../Oven/oven_control.h"
#include "../Oven/oven.h"
#include "../Oven/profile_lead.h"
#include "../Oven/profile_pb_free.h"
#include "../OS/time.h"


#define task_15ms		(counts%500)==0
#define task_32ms		(counts%1000)==0
#define task_62ms		(counts%2000)==0 // task_64ms
#define	task_125ms		(counts%5000)==0 // task 160ms
#define task_250ms		(counts%8000)==0 // task 256ms
#define task_500ms		(counts%1600)==0
#define task_graph_ud	((reflow_timer %128) == 0)


#define task_500ms_flag		(0x1<<0)
#define task_250ms_flag		(0x1<<1)
#define task_125ms_flag		(0x1<<2)
#define task_62ms_flag		(0x1<<3)
#define task_32ms_flag		(0x1<<4)
#define task_15ms_flag		(0x1<<5)
#define graph_update		(0x1<<6)

// System count time

// 1  count  =  15.6ms
// 2  counts =  31.6ms
// 4  counts =  62.5ms
// 8  counts = 125.0ms
// 16 counts = 250.0ms
// 32 counts = 500.0ms

extern uint16_t counts;
extern uint8_t task_flags;
extern uint16_t reflow_timer;

uint8_t get_system_seconds();
uint8_t get_system_minutes();
uint8_t get_system_hours();

void set_system_seconds(uint8_t secs);
void set_system_minutes(uint8_t minutes);
void set_system_hours(uint8_t hours);

void get_system_time_string(char * buffer);
void rtc_setup();


#endif /* RTC_H_ */
