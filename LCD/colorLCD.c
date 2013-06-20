/*
 * colorLCD.c
 *
 *  Created on: Mar 20, 2012
 *      Author: RG1540
 */

#include "colorLCD.h"
#include "FONT/font_5x7.h"
#include "FONT/font_11x16.h"
#include "FONT/font_8x12.h"
#include "msp430g2553.h"
#include "../DRIVE/spi.h"

uint8_t colorLowByte = 0;
uint8_t colorHighByte = 0;
uint8_t bgColorLowByte = 0;
uint8_t bgColorHighByte = 0;

char text_buffer[20];

//char fontSize = 0;
//const char fontSupport[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

//////////////////////
// color
//////////////////////
void setColor8(uint8_t color) {
	colorLowByte = color;
}

void setColor16(uint16_t color) {
	colorLowByte = color;
	colorHighByte = color >> 8;
}

void setBackgroungColor8(uint8_t color) {
	bgColorLowByte = color;
}

void setBackgroundColor16(uint16_t color) {
	bgColorLowByte = color;
	bgColorHighByte = color >> 8;
}

/////////////////
// drawing
/////////////////

void setArea(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {

#ifdef HORIZONTAL
	uint8_t trueXStart, trueYStart, trueXEnd, trueYEnd; // horizontal
	trueXStart = yStart; // horizontal
	trueXEnd = yEnd; // horizontal
	trueYStart = xStart; // horizontal
	trueYEnd = xEnd; // horizontal

	writeCommand(ILIGRAMHEA);
	writeData(0);
	writeData(trueXEnd + LCD_OFFSET_WIDTH); // horizontal
	writeCommand(ILIGRAMHSA);
	writeData(0);
	writeData(trueXStart + LCD_OFFSET_WIDTH); // horizontal

	writeCommand(ILIGRAMVEA);
	writeData(0);
	writeData(trueYEnd + LCD_OFFSET_HEIGHT); // horizontal
	writeCommand(ILIGRAMVSA);
	writeData(0);
	writeData(trueYStart + LCD_OFFSET_HEIGHT); // horizontal

	writeCommand(ILIGRAMADDRX);
	writeData(0);
	writeData(trueXStart + LCD_OFFSET_WIDTH); // horizontal
	writeCommand(ILIGRAMADDRY);
	writeData(0);
	writeData(trueYStart + LCD_OFFSET_HEIGHT); // horizontal

	writeCommand(ILIWRDATA);
#else
	writeCommand(ILIGRAMHEA);
	writeData(0);
	writeData(xEnd + LCD_OFFSET_WIDTH);
	writeCommand(ILIGRAMHSA);
	writeData(0);
	writeData(xStart + LCD_OFFSET_WIDTH);

	writeCommand(ILIGRAMVEA);
	writeData(0);
	writeData(yEnd + LCD_OFFSET_HEIGHT);
	writeCommand(ILIGRAMVSA);
	writeData(0);
	writeData(yStart + LCD_OFFSET_HEIGHT);

	writeCommand(ILIGRAMADDRX);
	writeData(0);
	writeData(xStart + LCD_OFFSET_WIDTH);
	writeCommand(ILIGRAMADDRY);
	writeData(0);
	writeData(yStart + LCD_OFFSET_HEIGHT);

	writeCommand(ILIWRDATA);
#endif


}

void clearScreen(uint8_t blackWhite) {
	setArea(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
	const unsigned int totalPixels = (unsigned int)LCD_WIDTH *(unsigned int)LCD_HEIGHT;
	setBackgroundColor16(blackWhite ? 0x0000 : 0xFFFF);
	unsigned int c = 0;
	while (c < totalPixels) {
#ifdef USE16BIT
		writeData(bgColorHighByte);
#endif
		writeData(bgColorLowByte);
		c++;
	}
}

void drawPixel(uint8_t x, uint8_t y) {
	setArea(x, y, x, y);
#ifdef USE16BIT
	writeData(colorHighByte);
#endif
	writeData(colorLowByte);
}

//////////////////////////
// 5x7 font - this function does not draw background pixels
//////////////////////////
//void drawChar(uint8_t x, uint8_t y, char c) {
//	uint8_t col = 0;
//	uint8_t row = 0;
//	uint8_t bit = 0x01;
//  uint8_t oc = c - 0x20;
//	while (row < 8) {
//		while (col < 5) {
//			if (font[oc][col] & bit)
//				drawPixel(x + col, y + row);
//			col++;
//		}
//		col = 0;
//		bit <<= 1;
//		row++;
//	}
//}

////////////////
// 5x7 font - this function draws background pixels
////////////////
void drawChar(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x01;
	uint8_t oc = c - 0x20;
	setArea(x, y, x + 4, y + 7); // if you want to fill column between chars, change x + 4 to x + 5

	while (row < 8) {
		while (col < 5) {
			if (font[oc][col] & bit) {
				//foreground
#ifdef USE16BIT
				writeData(colorHighByte);
#endif
				writeData(colorLowByte);
			} else {
				//background
#ifdef USE16BIT
				writeData(bgColorHighByte);
#endif
				writeData(bgColorLowByte);
			}
			col++;
		}
		// if you want to fill column between chars, writeData(bgColor) here
		col = 0;
		bit <<= 1;
		row++;
	}
}

void drawString(uint8_t x, uint8_t y, char *string) {
	uint8_t xs = x;
	while (*string) {
		drawChar(xs, y, *string++);
		xs += 6;
	}
}

////////////////
// 11x16 font - this function does not draw background pixels
////////////////
//void drawChar11_16(uint8_t x, uint8_t y, char c) {
//	uint8_t col = 0;
//	uint8_t row = 0;
//	uint16_t bit = 0x0001;
//	uint8_t oc = c - 0x20;
//	while (row < 16) {
//		while (col < 11) {
//			if (font_11x16[oc][col] & bit)
//				drawPixel(x + col, y + row);
//			col++;
//		}
//		col = 0;
//		bit <<= 1;
//		row++;
//	}
//}

////////////////
// 11x16 font - this function draws background pixels
////////////////
void drawChar11_16(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint16_t bit = 0x0001;
	uint8_t oc = c - 0x20;
	setArea(x, y, x + 10, y + 15);
	while (row < 16) {
		while (col < 11) {
			if (font_11x16[oc][col] & bit) {
				//foreground
#ifdef USE16BIT
				writeData(colorHighByte);
#endif
				writeData(colorLowByte);
			} else {
				//background
#ifdef USE16BIT
				writeData(bgColorHighByte);
#endif
				writeData(bgColorLowByte);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

void drawString11_16(uint8_t x, uint8_t y, char *string) {
	uint8_t xs = x;
	while (*string) {
		drawChar11_16(xs, y, *string++);
		xs += 12;
	}
}

////////////////
// 8x12 font - this function does not draw background pixels
////////////////
//void drawChar8_12(uint8_t x, uint8_t y, char c) {
//	uint8_t col = 0;
//	uint8_t row = 0;
//	uint8_t bit = 0x80;
//  uint8_t oc = c - 0x20;
//	while (row < 12) {
//		while (col < 8) {
//			if (font_8x12[oc][row] & bit)
//				drawPixel(x + col, y + row);
//			bit >>= 1;
//			col++;
//		}
//		bit = 0x80;
//		col = 0;
//		row++;
//	}
//}

////////////////
// 8x12 font - this function draws background pixels
////////////////
void drawChar8_12(uint8_t x, uint8_t y, char c) {
	uint8_t col = 0;
	uint8_t row = 0;
	uint8_t bit = 0x80;
	uint8_t oc = c - 0x20;
	setArea(x, y, x + 7, y + 11);
	while (row < 12) {
		while (col < 8) {
			if (font_8x12[oc][row] & bit) {
				//foreground
#ifdef USE16BIT
				writeData(colorHighByte);
#endif
				writeData(colorLowByte);
			} else {
				//background
#ifdef USE16BIT
				writeData(bgColorHighByte);
#endif
				writeData(bgColorLowByte);
			}
			bit >>= 1;
			col++;
		}
		bit = 0x80;
		col = 0;
		row++;
	}

}

void drawString8_12(uint8_t x, uint8_t y, char *string) {
	uint8_t xs = x;
	while (*string) {
		drawChar8_12(xs, y, *string++);
		xs += 8;
	}
}

////////////////////////
// images
////////////////////////
//data is 16 bit color
void drawImage(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t * data) {

}

// lut is used, ?0 means skip, sort of a mask?
void drawImageLut(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data,
		uint16_t * lut) {

}

// each bit represents color, fg and bg colors are used, ?how about 0 as a mask?
void drawImageMono(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * data) {

}

////////////////////////
// shapes
////////////////////////

void drawLogicLine(uint8_t x, uint8_t y, uint8_t length, uint8_t height,
		uint8_t * data) {
	uint8_t last = (*data & 0x80);
	uint8_t counter = 0;
	while (counter < length) {
		uint8_t bitCounter = 0;
		uint8_t byte = *data;
		while (bitCounter < 8 && counter < length) {
			if (last == (byte & 0x80)) {
				//draw pixel
				uint8_t h = (byte & 0x80) ? (height + y) : y;
				drawPixel(x + counter, h);
			} else {
				// draw line
				if (byte & 0x80) {
					drawLine(x + counter - 1, y, x + counter, y + height);
				} else {
					drawLine(x + counter - 1, y + height, x + counter, y);
				}
			}
			last = byte & 0x80;
			byte <<= 1;
			bitCounter++;
			counter++;
		}
		*data++;
	}
}

void drawLine(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {

	uint8_t x0, x1, y0, y1;
	uint8_t d = 0;

// handle direction
	if (yStart > yEnd) {
		y0 = yEnd;
		y1 = yStart;
	} else {
		y1 = yEnd;
		y0 = yStart;
	}

	if (xStart > xEnd) {
		x0 = xEnd;
		x1 = xStart;
	} else {
		x1 = xEnd;
		x0 = xStart;
	}

// check if horizontal
	if (y0 == y1) {
		d = x1 - x0 + 1;
		setArea(x0, y0, x1, y1);
		while (d-- > 0) {
#ifdef USE16BIT
			writeData(colorHighByte);
#endif
			writeData(colorLowByte);
		}

	} else if (x0 == x1) { // check if vertical
		d = y1 - y0 + 1;
		setArea(x0, y0, x1, y1);
		while (d-- > 0) {
#ifdef USE16BIT
			writeData(colorHighByte);
#endif
			writeData(colorLowByte);
		}

	} else { // angled
		char dx, dy;
		int sx, sy;

		if (xStart < xEnd) {
			sx = 1;
			dx = xEnd - xStart;
		} else {
			sx = -1;
			dx = xStart - xEnd;
		}

		if (yStart < yEnd) {
			sy = 1;
			dy = yEnd - yStart;
		} else {
			sy = -1;
			dy = yStart - yEnd;
		}

		int e1 = dx - dy;
		int e2;

		while (1) {
			drawPixel(xStart, yStart);
			if (xStart == xEnd && yStart == yEnd)
				break;
			e2 = 2 * e1;
			if (e2 > -dy) {
				e1 = e1 - dy;
				xStart = xStart + sx;
			}
			if (e2 < dx) {
				e1 = e1 + dx;
				yStart = yStart + sy;
			}
		}
	}
}

void drawRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {

	drawLine(xStart, yStart, xEnd, yStart);
	drawLine(xStart, yEnd, xEnd, yEnd);
	drawLine(xStart, yStart, xStart, yEnd);
	drawLine(xEnd, yStart, xEnd, yEnd);
}

void drawCircle(uint8_t x, uint8_t y, uint8_t radius) {
	int dx = radius;
	int dy = 0;
	int xChange = 1 - 2 * radius;
	int yChange = 1;
	int radiusError = 0;
	while (dx >= dy) {
		drawPixel(x + dx, y + dy);
		drawPixel(x - dx, y + dy);
		drawPixel(x - dx, y - dy);
		drawPixel(x + dx, y - dy);
		drawPixel(x + dy, y + dx);
		drawPixel(x - dy, y + dx);
		drawPixel(x - dy, y - dx);
		drawPixel(x + dy, y - dx);
		dy++;
		radiusError += yChange;
		yChange += 2;
		if (2 * radiusError + xChange > 0) {
			dx--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

/////////////////////////
// fill
/////////////////////////

void fillRect(uint8_t xStart, uint8_t yStart, uint8_t xEnd, uint8_t yEnd) {
	setArea(xStart, yStart, xEnd, yEnd);
	uint16_t total = (xEnd - xStart + 1) * (yEnd - yStart + 1);
	uint16_t c = 0;
	while (c < total) {
#ifdef USE16BIT
		writeData(colorHighByte);
#endif
		writeData(colorLowByte);
		c++;
	}
}

void fillCircle(uint8_t x, uint8_t y, uint8_t radius) {
	int dx = radius;
	int dy = 0;
	int xChange = 1 - 2 * radius;
	int yChange = 1;
	int radiusError = 0;
	while (dx >= dy) {
		drawLine(x + dy, y + dx, x - dy, y + dx);
		drawLine(x - dy, y - dx, x + dy, y - dx);
		drawLine(x - dx, y + dy, x + dx, y + dy);
		drawLine(x - dx, y - dy, x + dx, y - dy);
		dy++;
		radiusError += yChange;
		yChange += 2;
		if (2 * radiusError + xChange > 0) {
			dx--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}



void initILI9225B() {

	LCD_BLIGHT_SETUP |= LCD_BLIGHT;
	LCD_BLIGHT_OUTPUT |= LCD_BLIGHT;

#ifdef HARD_SPI

	//////////////////////////////

	LCD_SCE_SETUP |= LCD_SCE_PIN;
	LCD_SCE_PORT |= LCD_SCE_PIN;
	LCD_DC_SETUP |= LCD_DC_PIN;
	LCD_DC_PORT |= LCD_DC_PIN;

	SPI_B_INIT();

#else
	P1OUT |= LCD_SCLK_PIN + LCD_SCE_PIN + LCD_SD_PIN + LCD_DC_PIN;
	P1DIR |= LCD_SCLK_PIN + LCD_SCE_PIN + LCD_SD_PIN + LCD_DC_PIN;
#endif


	_delay_cycles(10000);
	writeCommand(0x28);
	delay(20);

#ifdef HORIZONTAL
	writeCommand(0x01);
	writeData(0x03); // set SS and NL bit
//	writeData(0x00); // set SS and NL bit
	writeData(0x1C);
	writeCommand(0x02);
	writeData(0x01); // set 1 line inversion
	writeData(0x00);
	writeCommand(0x03);
	writeData(0x10); // set GRAM write direction and BGR=1.//1030
	writeData(0x38);
#else
	writeCommand(0x01);
	writeData(0x01); // set SS and NL bit
	writeData(0x1C);
	writeCommand(0x02);
	writeData(0x01); // set 1 line inversion
	writeData(0x00);
	writeCommand(0x03);
	writeData(0x10); // set GRAM write direction and BGR=1.//1030
	writeData(0x30);
#endif

	writeCommand(0x08);
	writeData(0x08); // set BP and FP
	writeData(0x08);
	writeCommand(0x0C);
	writeData(0x00); // RGB interface setting 0x0110 for RGB 18Bit and 0111for RGB16Bit
	writeData(0x00);
	writeCommand(0x0F);
	writeData(0x0b); // Set frame rate//0b01
	writeData(0x01);
	delay(5);
	writeCommand(0x10);
	writeData(0x0a); // Set SAP,DSTB,STB//0800
	writeData(0x00);
	writeCommand(0x11);
	writeData(0x10); // Set APON,PON,AON,VCI1EN,VC
	writeData(0x38);
	delay(5);
	writeCommand(0x12);
	writeData(0x11); // Internal reference voltage= Vci;
	writeData(0x21);
	writeCommand(0x13);
	writeData(0x00); // Set GVDD
	writeData(0x63);
	writeCommand(0x14);
	writeData(0x4b); // Set VCOMH/VCOML voltage//3944
	writeData(0x44);
	writeCommand(ILIGRAMADDRX);
	writeData(0x00);
	writeData(0x00);
	writeCommand(ILIGRAMADDRY);
	writeData(0x00);
	writeData(0x00);
	setGRAMILI9225B();
	gammaAdjustmentILI9225B();

//TODO add horizontal/vertical settings

	delay(5);
	writeCommand(0x07);
	writeData(0x10);
	writeData(0x17);

}

////////////////////////////////////
// gamma, lut, and other inits
////////////////////////////////////
void gammaAdjustmentST7735() {
	const uint8_t gmctrp1[] = { 0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2d,
			0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10 };
	const uint8_t gmctrn1[] = { 0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
			0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10 };
// gamma correction is needed for accurate color but is not necessary.
	uint8_t c = 0;
	writeCommand(ST7735_GMCTRP1); // gamma adjustment (+ polarity)
	while (c < 16) {
		writeData(gmctrp1[c]);
		c++;
	}
	c = 0;
	writeCommand(ST7735_GMCTRN1); // gamma adjustment (- polarity)
	while (c < 16) {
		writeData(gmctrn1[c]);
		c++;
	}
}

void gammaAdjustmentHX8340() {
	const uint8_t gammap[] = { 0x60, 0x71, 0x01, 0x0E, 0x05, 0x02, 0x09, 0x31,
			0x0A }; //9th is CGM
	const uint8_t gamman[] = { 0x67, 0x30, 0x61, 0x17, 0x48, 0x07, 0x05, 0x33 };
	uint8_t c = 0;
	writeCommand(SETGAMMAP);
	while (c < 9) {
		writeData(gammap[c]);
		c++;
	}
	c = 0;
	writeCommand(SETGAMMAN);
	while (c < 8) {
		writeData(gamman[c]);
		c++;
	}

}

void gammaAdjustmentILI9225B() {
	const uint8_t dataMSB[] = { 0x00, 0x09, 0x0d, 0x09, 0x04, 0x05, 0x00, 0x00,
			0x17, 0x00 };
	const uint8_t dataLSB[] = { 0x03, 0x00, 0x05, 0x00, 0x07, 0x02, 0x00, 0x05,
			0x00, 0x1F };
	const uint8_t cmd = 0x50;
	uint8_t c = 0;
	while (c < 10) {
		writeCommand(cmd + c);
		writeData(dataMSB[c]);
		writeData(dataLSB[c]);
		c++;
	}
}

void setGRAMILI9225B() {
	const uint8_t dataLSB[] = { 0x00, 0xDB, 0x00, 0x00, 0xDB, 0x00, 0xAF, 0x00,
			0xDB, 0x00 };
	const uint8_t cmd = 0x30;
	uint8_t c = 0;
	while (c < 10) {
		writeCommand(cmd + c);
		writeData(0x00);
		writeData(dataLSB[c]);
		c++;
	}
}

void initLUT() {
// 128-Bytes must be written to the LUT regardless of the color mode.
// 4K-color (4-4-4) and 65K-color(5-6-5) data input are transferred 6(R)-6(G)-6(B) through RGB LUT table.
	writeCommand(RGBSET);
	uint8_t c;
	for (c = 0; c < 0x1F; c += 2) {
		writeData(c);
	}
	for (c = 0; c < 0x3F; c++) {
		writeData(c);
	}
	for (c = 0; c < 0x1F; c += 2) {
		writeData(c);
	}
}

////////////////////////////////////
// write & delay
////////////////////////////////////

// code duplication, but we are saving clock cycles by not passing dataCommand
void writeData(uint8_t data) {
	LCD_SELECT;
#ifdef SPI9BIT
	LCD_SD_OUT_HI;
	LCD_CLOCK;
#else
	LCD_DC_HI;
#endif

#ifdef HARD_SPI
	SPI_B_SEND(data);

#else

	uint8_t c=0;
	while (c < 8) {
		(data & 0x80) ? (LCD_SD_OUT_HI) : (LCD_SD_OUT_LO);
		LCD_CLOCK;
		data <<= 1;
		c++;
	}

#endif


	LCD_DESELECT;
}

// code duplication, but we are saving clock cycles by not passing dataCommand
void writeCommand(uint8_t data) {
	LCD_SELECT;
#ifdef SPI9BIT
	LCD_SD_OUT_LO;
	LCD_CLOCK;
#else
	LCD_DC_LO;
#endif

#ifdef HARD_SPI
	SPI_B_SEND(data);
#else
	uint8_t c=0;
	while (c < 8) {
		(data & 0x80) ? (LCD_SD_OUT_HI) : (LCD_SD_OUT_LO);
		LCD_CLOCK;
		data <<= 1;
		c++;
	}
#endif

	LCD_DESELECT;
}

void delay(uint8_t x10ms) {
	while (x10ms > 0) {
		_delay_cycles(160000);
		x10ms--;
	}
}

void binaryToASCII(unsigned int n, char * digits) {
	__asm(" clr		R14");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" rla		R12");
	__asm(" dadd	R14, R14");
	__asm(" mov.b	R14, 3(R13)");
	__asm(" swpb	R14");
	__asm(" mov.b	R14, 1(R13)");
	__asm(" rra		R14");
	__asm(" rra		R14");
	__asm(" rra		R14");
	__asm(" rra		R14");
	__asm(" mov.b	R14, 0(R13)");
	__asm(" swpb	R14");
	__asm(" mov.b	R14, 2(R13)");
	__asm(" and		#0x0F0F, 0(R13)");
	__asm(" and		#0x0F0F, 2(R13)");
	__asm(" add.b	#0x30, 3(R13)");
	__asm(" tst.b	0(R13)");
	__asm(" jnz l1");
	__asm(" mov.b	#0x20, 0(R13)");
	__asm(" tst.b	1(R13)");
	__asm(" jnz l2");
	__asm(" mov.b	#0x20, 1(R13)");
	__asm(" tst.b	2(R13)");
	__asm(" jnz l3");
	__asm(" mov.b	#0x20, 2(R13)");
	__asm(" jmp l4");
	__asm("l1:");
	__asm(" add.b	#0x30, 0(R13)");
	__asm("l2:");
	__asm(" add.b	#0x30, 1(R13)");
	__asm("l3:");
	__asm(" add.b	#0x30, 2(R13)");
	__asm("l4:");
	return;
}
