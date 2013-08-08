/*
 * calibration.h
 *
 *  Created on: Jul 20, 2013
 *      Author: Nate
 */

#ifndef CALIBRATION_H_
#define CALIBRATION_H_

#include "stdint.h"

void init_cal();
void set_cal(uint8_t cal_val);
uint16_t get_cal_adc_offset();
int16_t get_cal_temp_offset();
#endif /* CALIBRATION_H_ */
