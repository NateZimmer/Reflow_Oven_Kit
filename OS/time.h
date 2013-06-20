/*
 * time.h
 *
 *  Created on: Jun 16, 2013
 *      Author: Nate
 */

#ifndef TIME_H_
#define TIME_H_

#include "stdint.h"

typedef struct {
	uint8_t secs;
	uint8_t minutes;
	uint8_t hours;
}time_stamp;

uint8_t count_down_time(time_stamp *present_time);
uint8_t count_down_time_idle(time_stamp *present_time);
void get_time_long(char * buffer, time_stamp *present_time); // format hours:mins:secs
void get_time_short(char * buffer, time_stamp *present_time); // format hours:mins:secs


#endif /* TIME_H_ */
