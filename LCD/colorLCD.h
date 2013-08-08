/*
 * colorLCD.h
 *
 *  Created on: Mar 19, 2012
 *      Author: RobG
 */

#ifndef COLORLCD_H_
#define COLORLCD_H_

#include <stdint.h>
#include "../DRIVE/GPIO.h"

#define HARD_SPI
#define HORIZONTAL

extern char text_buffer[20];

// define driver
//
//#define PCF8833 // use for 6100
//#define SPFD54124B // use for 6085 and 6101
//#define ST7735R // use for JD-T1800 (1.8")
//#define HX8340B // use for BTL221722 (2.2" without touch)
#define ILI9225B // 2.2" with touch

//
//
#ifdef PCF8833
//
#define USE8BIT
#define LCD_HEIGHT 130
#define LCD_WIDTH 130
#define LCD_OFFSET_HEIGHT 1
#define LCD_OFFSET_WIDTH 1
#define SPI9BIT
//
#else
#ifdef SPFD54124B
//
#define USE16BIT
#define LCD_HEIGHT 160
#define LCD_WIDTH 128
#define LCD_OFFSET_HEIGHT 1
#define LCD_OFFSET_WIDTH 2
#define SPI9BIT
//
#else
#ifdef ST7735R
//
#define USE16BIT
#define LCD_HEIGHT 160
#define LCD_WIDTH 128
#define LCD_OFFSET_HEIGHT 0
#define LCD_OFFSET_WIDTH 0
//
#else
#ifdef HX8340B
//
#define USE16BIT
#define SPI9BIT
#define LCD_HEIGHT 176 //horizontal 176, vertical 220
#define LCD_WIDTH 220 // horizontal 220, vertical 176
#define LCD_OFFSET_HEIGHT 0
#define LCD_OFFSET_WIDTH 0
//
#else
#ifdef ILI9225B
//
#define USE16BIT

#ifdef HORIZONTAL

#define LCD_HEIGHT 176
#define LCD_WIDTH 220

#else

#define LCD_HEIGHT 220
#define LCD_WIDTH 176

#endif

#define LCD_OFFSET_HEIGHT 0
#define LCD_OFFSET_WIDTH 0
//
#endif
#endif
#endif
#endif
#endif
//

// pins
#define LCD_SCLK_PIN P1_5
#define LCD_SCLK_PORT P1OUT

#define LCD_SD_PIN P1_7
#define LCD_SD_PORT P1OUT
#define LCD_SD_PORT_IN P1IN
#define LCD_SD_DIR P1DIR

#define LCD_SCE_PIN P2_0 // CS
#define LCD_SCE_PORT P2OUT
#define LCD_SCE_SETUP P2DIR

#define LCD_DC_PIN P1_0	//RS
#define LCD_DC_PORT P1OUT
#define LCD_DC_SETUP P1DIR

#define LCD_BLIGHT P2_3
#define LCD_BLIGHT_OUTPUT P2OUT
#define LCD_BLIGHT_SETUP P2DIR

//
#define LCD_SELECT LCD_SCE_PORT &= ~LCD_SCE_PIN
#define LCD_DESELECT LCD_SCE_PORT |= LCD_SCE_PIN
//
#define LCD_DC_LO LCD_DC_PORT &= ~LCD_DC_PIN
#define LCD_DC_HI LCD_DC_PORT |= LCD_DC_PIN
//
#define LCD_SD_IN LCD_SD_PORT_IN & LCD_SD_PIN
#define LCD_SD_OUT_HI LCD_SD_PORT |= LCD_SD_PIN
#define LCD_SD_OUT_LO LCD_SD_PORT &= ~LCD_SD_PIN
#define LCD_SD_DIR_O LCD_SD_DIR |= LCD_SD_PIN
#define LCD_SD_DIR_I LCD_SD_DIR &= ~LCD_SD_PIN
//
#define LCD_CLOCK LCD_SCLK_PORT |= LCD_SCLK_PIN; LCD_SCLK_PORT &= ~LCD_SCLK_PIN
#define LCD_SCLK_LO LCD_SCLK_PORT &= ~LCD_SCLK_PIN
#define LCD_SCLK_HI LCD_SCLK_PORT |= LCD_SCLK_PIN

void writeData(uint8_t data);
void writeCommand(uint8_t data);
void delay(uint8_t x10ms);

void initPCF8833();
void initSPFD54124B();
void initST7735R();
void initHX8340B();
void initILI9225B();
void initLUT();
void setGRAMILI9225B();
void gammaAdjustmentST7735();
void gammaAdjustmentHX8340();
void gammaAdjustmentILI9225B();

void setColor8(uint8_t color);
void setColor16(uint16_t color);
void setBackgroundColor16(uint16_t color);

void setArea(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void clearScreen(uint8_t blackWhite);
void drawPixel(uint8_t x, uint8_t y);
void drawChar(uint8_t x, uint8_t y, char c);
void drawString(uint8_t x, uint8_t y, char *string);
void drawChar11_16(uint8_t x, uint8_t y, char c);
void drawString11_16(uint8_t x, uint8_t y, char *string);
void drawChar8_12(uint8_t x, uint8_t y, char c);
void drawString8_12(uint8_t x, uint8_t y, char *string);
void drawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void drawRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void drawCircle(uint8_t x, uint8_t y, uint8_t radius);

void fillRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd);
void fillCircle(uint8_t x, uint8_t y, uint8_t radius);

void drawLogicLine(uint8_t x, uint8_t y, uint8_t length, uint8_t height, uint8_t * data);
//
void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t * data);
void drawImageLut(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data, uint16_t * lut);
void drawImageMono(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data);
void binaryToASCII(unsigned int n, char * digits);

//

#define COMMAND 0
#define DATA 1

// driver specific
#define SWRESET		0x01
#define	BSTRON		0x03
#define RDDIDIF		0x04
#define RDDST		0x09
#define SLEEPIN     0x10
#define	SLEEPOUT	0x11
#define	NORON		0x13
#define	INVOFF		0x20
#define INVON      	0x21
#define	SETCON		0x25
#define DISPOFF     0x28
#define DISPON      0x29
#define CASETP      0x2A
#define PASETP      0x2B
#define RAMWRP      0x2C
#define RGBSET	    0x2D
#define	MADCTL		0x36
#define SEP			0x37
#define	COLMOD		0x3A
#define DISCTR      0xB9
#define DOR			0xBA
#define	EC			0xC0
#define RDID1		0xDA
#define RDID2		0xDB
#define RDID3		0xDC
#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

#define SETOSC		0xB0
#define SETPWCTR4	0xB4
#define SETPWCTR5	0xB5
#define SETEXTCMD	0xC1
#define SETGAMMAP	0xC2
#define SETGAMMAN	0xC3
// ILI9225B specific
#define ILIGRAMADDRX	0x20
#define ILIGRAMADDRY 	0x21
#define ILIWRDATA   	0x22
#define ILIGRAMHEA		0x36
#define ILIGRAMHSA		0x37
#define ILIGRAMVEA		0x38
#define ILIGRAMVSA		0x39

// colors
#define COLOR_16_BLACK   		0x0000
#define COLOR_16_BLUE    		0x001F
#define COLOR_16_RED     		0xF800
#define COLOR_16_GREEN   		0x07E0
#define COLOR_16_CYAN    		0x07FF
#define COLOR_16_MAGENTA 		0xF81F
#define COLOR_16_YELLOW  		0xFFE0
#define COLOR_16_WHITE   		0xFFFF
//red
//orange
//blue
//green
#define COLOR_16_ORANGE			0xFD20
#define COLOR_16_ORANGE_RED		0xFA20
#define COLOR_16_DARK_ORANGE	0xFC60
//#define COLOR_16_GRAY			0xBDF7
#define COLOR_16_GRAY   		0x18C3
#define COLOR_16_NAVY			0x0010
#define COLOR_16_ROYAL_BLUE		0x435C
#define COLOR_16_SKY_BLUE		0x867D
#define COLOR_16_TURQUOISE		0x471A
#define COLOR_16_STEEL_BLUE		0x4416
#define COLOR_16_LIGHT_BLUE		0xAEDC
#define COLOR_16_AQUAMARINE		0x7FFA
#define COLOR_16_DARK_GREEN		0x0320
#define COLOR_16_DARK_OLIVE_GREEN	0x5345
#define COLOR_16_SEA_GREEN		0x2C4A
#define COLOR_16_SPRING_GREEN	0x07EF
#define COLOR_16_PALE_GREEN		0x9FD3
#define COLOR_16_GREEN_YELLOW	0xAFE5
#define COLOR_16_LIME_GREEN		0x3666
#define COLOR_16_FOREST_GREEN	0x2444
#define COLOR_16_KHAKI			0xF731
#define COLOR_16_GOLD			0xFEA0
#define COLOR_16_GOLDENROD		0xDD24
#define COLOR_16_SIENNA			0xA285
#define COLOR_16_BEIGE			0xF7BB
#define COLOR_16_TAN			0xD5B1
#define COLOR_16_BROWN			0xA145
#define COLOR_16_CHOCOLATE		0xD343
#define COLOR_16_FIREBRICK		0xB104
#define COLOR_16_HOT_PINK		0xFB56
#define COLOR_16_PINK			0xFE19
#define COLOR_16_DEEP			0xF8B2 //? DEEP what? PINK?
#define COLOR_16_VIOLET			0xEC1D
#define COLOR_16_DARK_VIOLET	0x901A
#define COLOR_16_PURPLE			0xA11E
#define COLOR_16_MEDIUM_PURPLE	0x939B

#endif /* COLORLCD_H_ */

