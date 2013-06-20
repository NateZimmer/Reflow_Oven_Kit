/*
 * touch.h
 *
 *  Created on: Feb 17, 2013
 *      Author: Nate
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include "msp430g2553.h"
#include "stdint.h"
#include "../DRIVE/gpio.h"


#define TOUCH_CS 	P1_4
#define TOUCH_CS_PORT P1OUT
#define TOUCH_CS_SETUP P1DIR

//#define TOUCH_IRQ	BIT0

#define GET_X		0xD0
#define GET_Y		0x90

void TOUCH_SETUP();
uint16_t TOUCH_X();
uint16_t TOUCH_Y();
void TOUCH_VAL(uint16_t * xval, uint16_t * yval);


#endif /* TOUCH_H_ */
