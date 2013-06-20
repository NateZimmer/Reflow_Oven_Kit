//Nathan Zimmerman

#include "msp430g2553.h"
#include <stdint.h>
#include <stdio.h>
#include "LCD\colorLCD.h"
#include "LCD\touch.h"
#include "LCD\gui.h"
#include "DRIVE\GPIO.h"
#include "DRIVE\rtc.h"
#include "OS\os.h"
#include "Oven\oven.h"
#include "DRIVE/timer.h"
#include "DRIVE/led.h"

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // disable WDT
	BCSCTL1 = CALBC1_16MHZ; // 16MHz clock
	DCOCTL = CALDCO_16MHZ;
	Setup_PWM_Timers();
	TOUCH_SETUP();
	rtc_setup();
	Setup_LCD();
	reset_idle_timer();
	OVEN_SETUP;
	OVEN_OFF;
	Start_OS();

//	while(1);






}

