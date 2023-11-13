
#ifndef __LCD_1IN28_H
#define __LCD_1IN28_H	
	
#include "DEV_Config.h"
#include <stdint.h>

#include <stdlib.h>		//itoa()
#include <stdio.h>


#define LCD_1IN28_HEIGHT 240
#define LCD_1IN28_WIDTH 240


#define HORIZONTAL 0
#define VERTICAL   1

#define LCD_1IN28_SetBacklight(Value) DEV_SetBacklight(Value) 

#define LCD_1IN28_CS_0	    DEV_Digital_Write(DEV_CS_PIN, 0) 
#define LCD_1IN28_CS_1	    DEV_Digital_Write(DEV_CS_PIN, 1)
	                        
#define LCD_1IN28_RST_0	  DEV_Digital_Write(DEV_RST_PIN,0)
#define LCD_1IN28_RST_1	  DEV_Digital_Write(DEV_RST_PIN,1)
	                        
#define LCD_1IN28_DC_0	    DEV_Digital_Write(DEV_DC_PIN, 0)
#define LCD_1IN28_DC_1	    DEV_Digital_Write(DEV_DC_PIN, 1)  

typedef struct{
	uint8_t WIDTH;
	uint8_t HEIGHT;
	UBYTE SCAN_DIR;
}LCD_1IN28_ATTRIBUTES;
extern LCD_1IN28_ATTRIBUTES LCD_1IN28;

/********************************************************************************
function:	
			Macro definition variable name
********************************************************************************/
void LCD_1IN28_Init(UBYTE Scan_dir);
void LCD_1IN28_Clear(uint8_t Color);
void LCD_1IN28_Clear2(uint8_t Color);
void LCD_1IN28_Display(uint8_t *Image);
void LCD_1IN28_DisplayWindows(uint8_t Xstart, uint8_t Ystart, uint8_t Xend, uint8_t Yend, uint8_t *Image);
void LCD_1IN28_DisplayPoint(uint8_t X, uint8_t Y, uint8_t Color);

void LCD_1IN28_DrawPaint(uint8_t x, uint8_t y, uint8_t Color);
void LCD_1IN28_SetBackLight(uint8_t Value);
#endif
