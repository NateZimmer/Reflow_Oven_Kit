/*
 * GPIO.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */

#ifndef GPIO_H_
#define GPIO_H_

#define P1_0	BIT0
#define P1_1	BIT1
#define P1_2	BIT2
#define P1_3	BIT3
#define P1_4	BIT4
#define P1_5	BIT5
#define P1_6	BIT6
#define P1_7	BIT7

#define P2_0	BIT0
#define P2_1	BIT1
#define P2_2	BIT2
#define P2_3	BIT3
#define P2_4	BIT4
#define P2_5	BIT5
#define P2_6	BIT6
#define P2_7	BIT7

#define P3_0	BIT0
#define P3_1	BIT1
#define P3_2	BIT2
#define P3_3	BIT3
#define P3_4	BIT4
#define P3_5	BIT5
#define P3_6	BIT6
#define P3_7	BIT7

#define GLED	P2_4
#define BLED	P2_6
#define RLED	P2_2


#define XTAL_TO_GPIO	P2SEL &=~(P2_6+P2_7); P2SEL2 &=~(P2_6+P2_7)

#define GLED_SETUP	P2DIR |=GLED
#define GLED_DSETUP	P2DIR &=~GLED;
#define GLED_OUT	P2OUT
#define GLED_ON		P2OUT &=~GLED
#define GLED_OFF	P2OUT |=GLED
#define GLED_A_OFF	GLED_SETUP; GLED_OFF; P2SEL &=~GLED
#define GLED_A_ON	GLED_SETUP; GLED_ON; P2SEL |=GLED

#define BLED_SETUP	P2DIR |=BLED
#define BLED_DSETUP	P2DIR &=~BLED;
#define BLED_ON		P2OUT &=~BLED
#define BLED_OFF	P2OUT |=BLED
#define BLED_A_OFF	BLED_SETUP; BLED_OFF; P2SEL &=~BLED
#define BLED_A_ON	BLED_SETUP; BLED_ON; P2SEL |=BLED

#define	RLED_SETUP	P2DIR |=RLED
#define RLED_DSETUP	P2DIR &=~RLED
#define RLED_OUT	P2OUT
#define RLED_ON		P2OUT &=~RLED
#define RLED_OFF	P2OUT |=RLED
#define RLED_A_OFF	RLED_SETUP; RLED_OFF; P2SEL &=~RLED
#define RLED_A_ON	RLED_SETUP; RLED_ON; P2SEL |=RLED


#define BUZZER		BLED



#endif /* GPIO_H_ */
