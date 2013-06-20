/*
 * spi.c
 *
 *  Created on: Feb 16, 2013
 *      Author: Nate
 */


#include "spi.h"

void SPI_B_INIT()
{



	P1SEL |= BIT5 + BIT6 + BIT7;
	P1SEL2 |= BIT5 + BIT6 + BIT7;

	UCB0CTL0 |=  UCCKPH +  UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI master

	//UCMSB Most significant bit first
	//UCCKPL The inactive state is high.
	//UCMST Master Mode
	//UCSYNC Synchronous mode

	UCB0CTL1 |= UCSSEL_2; // SMCLK
	UCB0BR0 |= 0x0; // MAX
	UCB0CTL1 &= ~UCSWRST; // **Initialize USCI state machine**

}

uint8_t SPI_B_SEND(uint8_t data)
{


	uint8_t recv=0;
	UCB0TXBUF = data; // write INT to TX buffer
	while (!(IFG2 & UCB0TXIFG));
	while (UCB0STAT & UCBUSY);
	recv = UCB0RXBUF;
	return recv;

}
