/*
 * timer.h
 *
 *  Created on: Apr 13, 2013
 *      Author: Nate
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stdint.h"

void Setup_PWM_Timers();
uint8_t Get_LED_Timer_Status();
void LED_ANI_OFF();
void LED_ANI_ON();

void BUZZER_ON();
void BUZZER_OFF();

void CHARGE_ON();
void CHARGE_OFF();

void GLED_Sequence();
void RLED_Sequence();
void BLED_Sequence();




#endif /* TIMER_H_ */
