/*
 * gui.h
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */

#ifndef GUI_H_
#define GUI_H_

#include "stdint.h"

typedef struct
{
	uint8_t		xstart;
	uint8_t		ystart;
	uint8_t		yend;
	uint8_t		xend;
	char	 	text[10];
} Text_Button;

typedef struct
{
	const	uint8_t		xstart;
	const	uint8_t		ystart;
	const	char	 	text[10];
} Small_Text_Button;


void Setup_LCD();

typedef enum
{
	Home_Page,
	Reflow_Page,
	Settings_Page

} Pages;

void Page_Event_Handler();
void update_graph();
void print_oven_data();
void check_timeout();


#endif /* GUI_H_ */
