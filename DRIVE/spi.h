/*
 * spi.h
 *
 *  Created on: Feb 16, 2013
 *      Author: Nate
 */

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include "msp430g2553.h"

#define		SLOW_SPI		UCB0BR0 = 0x5 // Down Clock
#define		SLOW2_SPI		UCB0BR0 = 0x1A // Down Clock
#define		FAST_SPI		UCB0BR0 = 0x0 //Max

void SPI_B_INIT();
uint8_t SPI_B_SEND(uint8_t data);

#endif /* SPI_H_ */
