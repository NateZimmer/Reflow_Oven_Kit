/*
 * adc.h
 *
 *  Created on: Jul 20, 2013
 *      Author: Nate
 */

#ifndef ADC_H_
#define ADC_H_

#include <msp430g2553.h>
#include "stdint.h"

uint16_t get_adc_val();
int16_t get_temp_raw();

#endif /* ADC_H_ */
