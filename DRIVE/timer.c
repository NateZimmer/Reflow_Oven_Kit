/*
 * timer.c
 *
 *  Created on: Apr 13, 2013
 *      Author: Nate
 */

#include "timer.h"
#include "GPIO.h"
#include "msp430g2553.h"
#include "stdbool.h"

static int gseq = 0;
static int rseq = 50;
static int bseq = 25;

static bool ANIMATION_TIMERS_ON = false;

const int led_dutys2[] = { 1002, 1002, 1002, 1002, 1001, 1001, 1000, 998, 997,
		994, 992, 989, 985, 981, 975, 970, 963, 956, 948, 938, 928, 917, 905,
		892, 877, 862, 845, 827, 807, 786, 764, 740, 715, 688, 659, 629, 597,
		564, 528, 490, 451, 410, 366, 321, 273, 224, 172, 118, 61, 2, 2, 61,
		118, 172, 224, 273, 321, 366, 410, 451, 490, 528, 564, 597, 629, 659,
		688, 715, 740, 764, 786, 807, 827, 845, 862, 877, 892, 905, 917, 928,
		938, 948, 956, 963, 970, 975, 981, 985, 989, 992, 994, 997, 998, 1000,
		1001, 1001, 1002, 1002, 1002, 1002,

};

const int blue_dutys[] = { 1002, 1002, 1002, 1002, 1001, 1001, 1000, 998, 997,
		994, 992, 989, 985, 981, 975, 970, 963, 956, 948, 938, 928, 917, 905,
		892, 877, 862, 845, 827, 807, 786, 764, 740, 715, 688, 659, 629, 597,
		564, 528, 490, 451, 410, 366, 321, 321, 321, 321, 321,321, 321, 321, 321,
		321, 321, 321, 321, 321, 366, 410, 451, 490, 528, 564, 597, 629, 659,
		688, 715, 740, 764, 786, 807, 827, 845, 862, 877, 892, 905, 917, 928,
		938, 948, 956, 963, 970, 975, 981, 985, 989, 992, 994, 997, 998, 1000,
		1001, 1001, 1002, 1002, 1002, 1002,

};


void Set_LED_Timers_On()
{
	ANIMATION_TIMERS_ON = true;
}

void Set_LED_Timers_Off()
{
	ANIMATION_TIMERS_ON = false;
}

uint8_t Get_LED_Timer_Status()
{
	return (uint8_t)ANIMATION_TIMERS_ON;
}


void Setup_PWM_Timers()
{

	XTAL_TO_GPIO;
	BLED_A_ON;
	GLED_A_ON;
	RLED_A_ON;

	CCR0 = 1002; // PWM Period
	CCTL1 = OUTMOD_7; // CCR1 reset/set
	CCR1 = 10; // CCR1 PWM duty cycle
	TACTL = TASSEL_2 + MC_1; // SMCLK, up mode

	TA1CCR0 = 1002; // PWM Period
	TA1CCTL2 = OUTMOD_7; // CCR1 reset/set
	TA1CCTL1 = OUTMOD_7;
	TA1CCR2 = 10; // CCR1 PWM duty cycle
	TA1CCR1 = 10; // CCR1 PWM duty cycle
	TA1CTL = TASSEL_2 + MC_1; // SMCLK, up mode

	__enable_interrupt(); //Guess

}

void CHARGE_ON()
{
	CCR0 =1002; //16MHZ/1000= 16khz
	CCR1 =500; // 50% duty cycle
	CHARGE_PUMP_ON;
}

void CHARGE_OFF()
{
	unsigned int CCR0_val =CCR0;
	CHARGE_PUMP_OFF;
	if(!(CCR0_val ==1002)) //16MHZ/1000= 16khz
	{
		CCR0 =1002;
	}
}

void LED_ANI_OFF()
{
	Set_LED_Timers_Off();
	BLED_A_OFF;
	GLED_A_OFF;
	RLED_A_OFF;
}

void LED_ANI_ON()
{
	Set_LED_Timers_On();
	BLED_A_ON;
	GLED_A_ON;
	RLED_A_ON;
}

void BUZZER_ON()
{
	CCR0 =32000;
	CCR1 =16000;
	BLED_A_ON;
}

void BUZZER_OFF()
{
	CCR0 =1002;
	CCR1 =500;
	BLED_A_OFF;
}

void GLED_Sequence()
{

	TA1CCR2 = led_dutys2[gseq]; //change TA0.1 duty cycle
	gseq++;
	if(gseq>99)
		gseq=0;
}

void RLED_Sequence()
{
	TA1CCR1 = led_dutys2[rseq]; //change TA0.1 duty cycle
	rseq++;
	if(rseq>99)
		rseq=0;
}

void BLED_Sequence()
{
	CCR1 = blue_dutys[bseq]; //change TA0.1 duty cycle
	bseq++;
	if(bseq>99)
		bseq=0;
}



