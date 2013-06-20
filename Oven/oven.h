/*
 * oven.h
 *
 *  Created on: Apr 12, 2013
 *      Author: Nate
 */

#ifndef OVEN_H_
#define OVEN_H_


#include "stdint.h"
#include "../DRIVE/gpio.h"

#define COMP_CS				P3_2
#define COMP_CS_SETUP		P3DIR |=COMP_CS;P3OUT |=COMP_CS
#define COMP_CS_SELECT		P3OUT &=~COMP_CS
#define COMP_CS_DESELECT	P3OUT |=COMP_CS

#define OVEN_HEAT			P2_5
#define OVEN_PORT_SETUP		P2DIR
#define OVEN_PORT_OUTPUT	P2OUT

#define OVEN_SETUP			OVEN_PORT_SETUP |=OVEN_HEAT
#define OVEN_ON				OVEN_PORT_OUTPUT |=OVEN_HEAT
#define OVEN_OFF			OVEN_PORT_OUTPUT &=~OVEN_HEAT

void Setup_Tcouple();
void get_temp_str(uint16_t heatdata, char *display_temp);
void update_temp();
uint16_t get_temp();
uint16_t get_Tcouple_value();

#endif /* OVEN_H_ */
