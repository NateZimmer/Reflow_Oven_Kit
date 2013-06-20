/*
 * gui.c
 *
 *  Created on: Apr 6, 2013
 *      Author: Nate
 */

#include "gui.h"
#include "colorLCD.h"
#include "touch.h"
#include "stdbool.h"
#include "stdio.h"
#include "../Oven/oven.h"
#include "../DRIVE/rtc.h"
#include "../DRIVE/timer.h"
#include "../Oven/oven_control.h"
#include "string.h"

static Text_Button Leaded;
static Text_Button Pb_Free;
static Text_Button Settings;
static Text_Button Start;
static Text_Button Back;

static Small_Text_Button Plus = {10,70," + "};
static Small_Text_Button Minus = {10,100," - "};
static Small_Text_Button Hours = {60,70,"Hours"};
static Small_Text_Button Mins = {60,100,"Minutes"};

static uint16_t Small_Button_Color = COLOR_16_RED;

static bool mins_selected=false;

static Pages Current_Page = Home_Page;

#define y_button_size 		20
#define Touch_Tolerance		5





void Create_Button(Text_Button * button_handle,uint8_t x_start, uint8_t y_start, char * display_text)
{
	uint8_t i=0;
	button_handle->xstart=x_start;
	button_handle->ystart=y_start;

	while(display_text[i])
	{
		button_handle->text[i]=display_text[i];
		i++;
	}
	button_handle->text[i]=display_text[i];

	button_handle->xend =8*i + x_start;
	button_handle->yend =y_start + y_button_size;

}

uint8_t Check_Small_Touch(Small_Text_Button *button_handle, uint16_t xval, uint16_t yval)
{
	uint8_t xstart = (button_handle->xstart);
	uint8_t ystart = (button_handle->ystart);
	uint8_t xend = 8*strlen(button_handle->text) + xstart;
	uint8_t yend = ystart + y_button_size;

	if(yval+xval)
	{
		if(((xval+Touch_Tolerance)>xstart)&&((yval+Touch_Tolerance)>ystart)&&((xval-Touch_Tolerance)<xend)&&((yval-Touch_Tolerance)<yend))
				return 1;
			else
				return 0;
	}
	else
		return 0;
}


uint8_t Check_Touch(Text_Button *button_handle, uint16_t xval, uint16_t yval)
{
	uint8_t xstart = (button_handle->xstart);
	uint8_t ystart = (button_handle->ystart);
	uint8_t xend = (button_handle->xend);
	uint8_t yend = (button_handle->yend);

	if(yval+xval)
	{
		if(((xval+Touch_Tolerance)>xstart)&&((yval+Touch_Tolerance)>ystart)&&((xval-Touch_Tolerance)<xend)&&((yval-Touch_Tolerance)<yend))
				return 1;
			else
				return 0;
	}
	else
		return 0;
}

void Create_Buttons()
{
	Create_Button(&Leaded,10,60,"Leaded");
	Create_Button(&Pb_Free,110,60,"Pb-Free");
	Create_Button(&Settings,140,150,"Settings");
	Create_Button(&Start,160,150,"Start");
	Create_Button(&Back,70,150,"Back");



}

void Draw_Button(Text_Button *button_handle)
{
	uint16_t bg_color =COLOR_16_RED;
	setColor16(bg_color);
	fillRect(button_handle->xstart, button_handle->ystart,button_handle->xend + 10, button_handle->yend);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(bg_color);
	setColor16(COLOR_16_WHITE);
	drawString8_12(button_handle->xstart+5, button_handle->ystart + 5, button_handle->text );
	setBackgroundColor16(COLOR_16_BLACK);

}

void Draw_Small_Button(Small_Text_Button *button_handle)
{
	uint8_t xend = 8*strlen(button_handle->text) + button_handle->xstart;
	uint8_t yend = button_handle->ystart + y_button_size;
	setColor16(Small_Button_Color);
	fillRect(button_handle->xstart, button_handle->ystart,xend + 10, yend);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(Small_Button_Color);
	setColor16(COLOR_16_WHITE);
	drawString8_12(button_handle->xstart+5, button_handle->ystart + 5, (char *)(button_handle->text));
	setBackgroundColor16(COLOR_16_BLACK);

}






void Draw_Home_Page()
{
	setColor16(0xFFFF);
	clearScreen(1);
	setColor16(COLOR_16_BLUE);
	fillRect(0, 0, 220, 30);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(COLOR_16_BLUE);
	drawString11_16(10, 10, "Reflow Oven V3");
	setBackgroundColor16(COLOR_16_BLACK);
	setColor16(COLOR_16_WHITE);
	drawString8_12(10,40, "Select Reflow Profile:");

	/*
	setColor16(COLOR_16_RED);
	fillRect(10, 60, 95, 90);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(COLOR_16_RED);
	setColor16(COLOR_16_WHITE);
	drawString11_16(20, 70, "Leaded");
	setBackgroundColor16(COLOR_16_BLACK);

	setColor16(COLOR_16_RED);
	fillRect(110, 60, 210, 90);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(COLOR_16_RED);
	setColor16(COLOR_16_WHITE);
	drawString11_16(120, 70, "Pb-Free");
	setBackgroundColor16(COLOR_16_BLACK);

	 */

	drawString(10, 90, "Peak: 210C");
	drawString(110, 90, "Peak: 230C");
	drawString(10, 105, "Ensure Thermocouple Touches PCB");
	drawString(10, 150, "Time:");
	drawString(10, 120, "Hardware/Software:");
	drawString(10, 130, "Nathan Zimmerman");
	setColor16(COLOR_16_WHITE);

	Draw_Button(&Leaded);
	Draw_Button(&Pb_Free);
	Draw_Button(&Settings);
}

void Draw_Oven_Page()
{
	setColor16(0xFFFF);
	clearScreen(1);
	setColor16(COLOR_16_WHITE);
	drawString(10, 150, "Time:");
	setBackgroundColor16(COLOR_16_BLACK);

	setColor16(COLOR_16_CYAN);
	drawString(10, 25, "Oven Temp:");
	setColor16(COLOR_16_ORANGE);
	drawString(120, 25, "Peak Temp:");
	setColor16(COLOR_16_GREEN);
	drawString(120, 40, "Duration:");

	setColor16(COLOR_16_WHITE);
	if(check_for_lead_profile())
	{
		setColor16(COLOR_16_GREEN);
		drawString8_12(10,5, "Lead");
		setColor16(COLOR_16_WHITE);
		drawString8_12(42,5, " Profile Selected:");
	}
	else
	{
		setColor16(COLOR_16_RED);
		drawString8_12(10,5, "Pb-Free");
		setColor16(COLOR_16_WHITE);
		drawString8_12(66,5, " Profile Selected:");
	}


	setColor16(COLOR_16_GRAY);
	fillRect(30, 55, 210, 55);
	fillRect(30, 65, 210, 65);
	fillRect(30, 75, 210, 75);
	fillRect(30, 85, 210, 85);
	fillRect(30, 95, 210, 95);
	fillRect(30, 105, 210, 105);
	fillRect(30, 115, 210, 115);
	fillRect(30, 125, 210, 125);
	setColor16(COLOR_16_WHITE);
	fillRect(30, 50, 31, 135); /// GRAPHIC!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	fillRect(30, 135, 210, 136);
	fillRect(28, 55, 33, 55); //240C
	drawString(5, 52, "240");
	fillRect(28, 65, 33, 65); //210C
	drawString(5, 62, "210");
	fillRect(28, 75, 33, 75); //180C
	drawString(5, 72, "180");
	fillRect(28, 85, 33, 85); //150C
	drawString(5, 82, "150");
	fillRect(28, 95, 33, 95); //120C
	drawString(5, 92, "120");
	fillRect(28, 105, 33, 105); //90C
	drawString(5, 102, "90");
	fillRect(28, 115, 33, 115); //50C
	drawString(5, 112, "60");
	fillRect(28, 125, 33, 125); //20C
	drawString(5, 122, "30");
	fillRect(61, 133, 61, 138);
	fillRect(91, 133, 91, 138);
	fillRect(121, 133, 121, 138);
	fillRect(151, 133, 151, 138);
	fillRect(181, 133, 181, 138);
	fillRect(211, 133, 211, 138);

	Draw_Button(&Start);

	if(!((oven_status==Oven_Reflowing) || (oven_status==Oven_Alarm) ))
	{
		Draw_Button(&Back);
	}
}

void Draw_Settings_Page()
{
	clearScreen(1);
	setColor16(0xFFFF);
	clearScreen(1);
	setColor16(COLOR_16_BLUE);
	fillRect(0, 0, 220, 30);
	setColor16(COLOR_16_WHITE);
	setBackgroundColor16(COLOR_16_BLUE);
	drawString11_16(10, 10, "Reflow Oven V3");
	setBackgroundColor16(COLOR_16_BLACK);
	setColor16(COLOR_16_WHITE);
	drawString8_12(10,40, "Time Selection:");
	setColor16(COLOR_16_WHITE);

	Draw_Small_Button(&Plus);
	Draw_Small_Button(&Minus);

	if(mins_selected)
	{
		Small_Button_Color = COLOR_16_BLUE;
		Draw_Small_Button(&Mins);
		Small_Button_Color = COLOR_16_RED;
		Draw_Small_Button(&Hours);
	}
	if(!mins_selected)
	{
		Small_Button_Color = COLOR_16_BLUE;
		Draw_Small_Button(&Hours);
		Small_Button_Color = COLOR_16_RED;
		Draw_Small_Button(&Mins);
	}

	Draw_Button(&Back);

}


void Check_Home_Page_Touch(Pages * page_return)
{
	uint16_t xval =0;
	uint16_t yval =0;
	TOUCH_VAL(&xval, &yval);

	if(Check_Touch(&Leaded, xval, yval))
	{
		set_profile_leaded();
		*page_return = Reflow_Page;
		return;
	}
	if(Check_Touch(&Pb_Free, xval, yval))
	{
		set_profile_pb_free();
		*page_return = Reflow_Page;
		return;
	}
	if(Check_Touch(&Settings, xval, yval))
	{

		*page_return = Settings_Page;
		return;
	}

	*page_return = Home_Page;

}

void Check_Reflow_Page_Touch(Pages * page_return)
{
	uint16_t xval =0;
	uint16_t yval =0;
	TOUCH_VAL(&xval, &yval);

	if(Check_Touch(&Back, xval, yval))
	{
		if(!((oven_status==Oven_Reflowing) || (oven_status==Oven_Alarm) ))
		{
		*page_return = Home_Page;
		BUZZER_OFF(); ///////////////////////////////////////////////////////////////
		}
		return;
	}
	if(Check_Touch(&Start, xval, yval))
	{
		if(Start.text[2]=='a')
		{
			if(start_oven())
			{
				Create_Button(&Start,160,150,"EStop");
				Draw_Oven_Page();
				_delay_cycles(10000000);
				*page_return = Reflow_Page;
				return;
			}
		}
		else
		{
			stop_oven();
			Create_Button(&Start,160,150,"Start");
			Draw_Oven_Page();
			_delay_cycles(10000000);
			*page_return = Reflow_Page;
			return;
		}

	}

	*page_return = Reflow_Page;

}

void Check_Settings_Page(Pages * page_return)
{
	uint16_t xval =0;
	uint16_t yval =0;

	TOUCH_VAL(&xval, &yval);
	if(Check_Small_Touch(&Mins,xval,yval))
	{
		Small_Button_Color = COLOR_16_BLUE;
		Draw_Small_Button(&Mins);
		Small_Button_Color = COLOR_16_RED;
		Draw_Small_Button(&Hours);
		mins_selected=true;
		_delay_cycles(10000000);
	}
	/*
	if(Check_Small_Touch(&Hours,xval,yval))
	{
		Small_Button_Color = COLOR_16_BLUE;

		Draw_Small_Button(&Hours);
		Small_Button_Color = COLOR_16_RED;
		Draw_Small_Button(&Mins);
		mins_selected=false;
		_delay_cycles(10000000);
	}

	if(Check_Small_Touch(&Plus,xval,yval))
	{
		if(mins_selected)
		{
			mins = (mins + 1)%60;
			get_time(text_buffer);
			drawString(10,160,text_buffer);
		}
		else
		{
			hours = hours%12+1;
			get_time(text_buffer);
			drawString(10,160,text_buffer);
		}
		_delay_cycles(10000000);
	}

	if(Check_Small_Touch(&Minus,xval,yval))
	{
		if(mins_selected)
		{
			mins -= 1;
			if(mins>60)
				mins=59;
			get_time(text_buffer);
			drawString(10,160,text_buffer);
		}
		else
		{
			hours -=1;
			if(hours<1)
				hours=12;
			get_time(text_buffer);
			drawString(10,160,text_buffer);
		}
		_delay_cycles(10000000);
	}
	*/

	if(Check_Touch(&Back,xval,yval))
	{
		*page_return = Home_Page;
	}


}

void Setup_LCD()
{
	initILI9225B();
	Create_Buttons();
	Draw_Home_Page();
}


void draw_status_message()
{
	switch(oven_status)
	{
		case Oven_Error:
			setColor16(COLOR_16_RED);
			drawString(10, 40,"ThermocoupleError");
			break;
		case Oven_Alarm:
			setColor16(COLOR_16_YELLOW);
			drawString(10, 40,"Slightly OpenDoor");
			break;
		case Oven_Cooldown:
			setColor16(COLOR_16_RED);
			drawString(10, 40,"Too Hot to Start ");
			break;
		case Oven_Reflowing:
			setColor16(COLOR_16_GREEN);
			drawString(10, 40,"Oven Reflowing    ");
			break;
		case Oven_Idle:
			setColor16(COLOR_16_GREEN);
			drawString(10, 40,"Oven Ready       ");
			break;

		default:
			break;
	}
}

void print_oven_data()
{
	uint16_t oven_temp =0;
	static uint8_t oven_temp_max=0;


	if(Current_Page ==Reflow_Page)
	{
		draw_status_message();
		oven_temp= get_temp();
		get_temp_str(oven_temp,text_buffer);
		setColor16(COLOR_16_CYAN);
		//drawString(10, 40, "Set Temp:");
		drawString(75, 25, text_buffer);
		if((oven_status==Oven_Reflowing) || (oven_status==Oven_Alarm) || (oven_status==Oven_Cooldown))
		{
			if(oven_temp_max<oven_temp)
			{
				oven_temp_max = oven_temp;
				setColor16(COLOR_16_ORANGE);
				drawString(185, 25, text_buffer);
			}
			/* 													---------Set Point
			setColor16(COLOR_16_PURPLE);
			sprintf(text_buffer,"%d",profile[profile_count]);
			drawString(75, 40, text_buffer);
			*/
			setColor16(COLOR_16_GREEN);
			get_reflow_time_string(text_buffer);
			drawString(177, 40, text_buffer);
			//oven_temp=get_profile_temp();
			//sprintf(text_buffer,"Profile Temp %d",oven_temp);
			//drawString(60, 150, text_buffer);
		}
		else
			oven_temp_max=0;

	}

}


void Page_Event_Handler()
{
	Pages Page_Return;
	switch( Current_Page)
	{

		case Home_Page:
			Check_Home_Page_Touch(&Page_Return);

			if (Page_Return ==Home_Page)
				_delay_cycles(1);
			else if(Page_Return ==Reflow_Page)
			{
				Current_Page =Reflow_Page;
				Draw_Oven_Page();
				_delay_cycles(10000000);
			}
			else if(Page_Return ==Settings_Page)
			{
				Current_Page =Settings_Page;
				Draw_Settings_Page();;
				_delay_cycles(10000000);
			}

			break;

		case Reflow_Page:
			Check_Reflow_Page_Touch(&Page_Return);

			if (Page_Return ==Reflow_Page)
				_delay_cycles(1);
			else if(Page_Return ==Home_Page)
			{
				Current_Page =Home_Page;
				Draw_Home_Page();
				_delay_cycles(10000000);
			}

			break;

		case Settings_Page:
			Check_Settings_Page(&Page_Return);
			if (Page_Return ==Home_Page)
			{
				Current_Page =Home_Page;
				Draw_Home_Page();
				_delay_cycles(10000000);
			}

			break;



	}

}

void update_graph()
{
	static uint8_t reflow_pixel_counter =0;
	uint16_t oven_temp=0;
	if((oven_status==Oven_Reflowing) || (oven_status==Oven_Alarm))
	{
			setColor16(COLOR_16_RED);
			oven_temp= get_temp();
			if(oven_temp>400) // Do not draw if thermocouple not connected
			{

			}
			else
			{
				drawRect(reflow_pixel_counter+32,135 - oven_temp/3,reflow_pixel_counter+33,136 - oven_temp/3);
				reflow_pixel_counter++;
			}
	}
	else
		reflow_pixel_counter =0;
}




