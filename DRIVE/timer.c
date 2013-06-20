/*
 * timer.c
 *
 *  Created on: Apr 13, 2013
 *      Author: Nate
 */

#include "timer.h"
#include "GPIO.h"
#include "msp430g2553.h"

static int gseq = 0;
static int rseq = 50;
static int bseq = 25;

const int led_dutys[] = { 1, 1, 1, 1, 2, 2, 3, 5, 6, 9, 11, 14, 18, 22, 28, 33,
		40, 47, 55, 65, 75, 86, 98, 111, 126, 141, 158, 176, 196, 217, 239, 263,
		288, 315, 344, 374, 406, 439, 475, 513, 552, 593, 637, 682, 730, 779,
		831, 885, 942, 1001, 1001, 942, 885, 831, 779, 730, 682, 637, 593, 552,
		513, 475, 439, 406, 374, 344, 315, 288, 263, 239, 217, 196, 176, 158,
		141, 126, 111, 98, 86, 75, 65, 55, 47, 40, 33, 28, 22, 18, 14, 11, 9, 6,
		5, 3, 2, 2, 1, 1, 1, 1
};

const int led_dutys2[] = { 1002, 1002, 1002, 1002, 1001, 1001, 1000, 998, 997,
		994, 992, 989, 985, 981, 975, 970, 963, 956, 948, 938, 928, 917, 905,
		892, 877, 862, 845, 827, 807, 786, 764, 740, 715, 688, 659, 629, 597,
		564, 528, 490, 451, 410, 366, 321, 273, 224, 172, 118, 61, 2, 2, 61,
		118, 172, 224, 273, 321, 366, 410, 451, 490, 528, 564, 597, 629, 659,
		688, 715, 740, 764, 786, 807, 827, 845, 862, 877, 892, 905, 917, 928,
		938, 948, 956, 963, 970, 975, 981, 985, 989, 992, 994, 997, 998, 1000,
		1001, 1001, 1002, 1002, 1002, 1002,

};


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

void LED_ANI_OFF()
{
	BLED_A_OFF;
	GLED_A_OFF;
	RLED_A_OFF;
}

void LED_ANI_ON()
{
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
	CCR1 = led_dutys2[bseq]; //change TA0.1 duty cycle
	bseq++;
	if(bseq>99)
		bseq=0;
}



