
#ifndef __GUI_PAINT_H
#define __GUI_PAINT_H

#include "DEV_Config.h"
#include "fonts.h"
#include "Debug.h"

typedef struct {

     uint8_t Width;
     uint8_t Height;
     uint8_t WidthMemory;
     uint8_t HeightMemory;
     uint8_t Color;
     uint8_t Rotate;
     uint8_t Mirror;
     uint8_t WidthByte;
     uint8_t HeightByte;
} PAINT;
extern  PAINT Paint;

/**
 * Display rotate
**/
#define ROTATE_0            0
#define ROTATE_90           90
#define ROTATE_180          180
#define ROTATE_270          270

/**
 * Display Flip
**/
typedef enum {
    MIRROR_NONE  = 0x00,
    MIRROR_HORIZONTAL = 0x01,
    MIRROR_VERTICAL = 0x02,
    MIRROR_ORIGIN = 0x03,
} MIRROR_IMAGE;
#define MIRROR_IMAGE_DFT MIRROR_NONE

/**
 * image color
**/

#define WHITE					0xFFFF
#define BLACK					0x0000	  
#define BLUE 					0x001F  
#define BRED 					0XF81F
#define GRED 					0XFFE0
#define GBLUE					0X07FF
#define RED  					0xF800
#define MAGENTA					0xF81F
#define GREEN					0x07E0
#define CYAN 					0x7FFF
#define YELLOW					0xFFE0
#define BROWN					0XBC40 
#define BRRED					0XFC07 
#define GRAY 					0X8430 
#define DARKBLUE				0X01CF
#define LIGHTBLUE				0X7D7C
#define GRAYBLUE     			0X5458
#define LIGHTGREEN   	 		0X841F
#define LGRAY 			  		0XC618
#define LGRAYBLUE    			0XA651
#define LBBLUE        			0X2B12


#define IMAGE_BACKGROUND    	WHITE
#define FONT_FOREGROUND     	BLACK
#define FONT_BACKGROUND    		WHITE

/**
 * The size of the point
**/
typedef enum {
    DOT_PIXEL_1X1  = 1,		// 1 x 1
    DOT_PIXEL_2X2  , 		// 2 X 2
    DOT_PIXEL_3X3  ,		// 3 X 3
    DOT_PIXEL_4X4  ,		// 4 X 4
    DOT_PIXEL_5X5  , 		// 5 X 5
    DOT_PIXEL_6X6  , 		// 6 X 6
    DOT_PIXEL_7X7  , 		// 7 X 7
    DOT_PIXEL_8X8  , 		// 8 X 8
} DOT_PIXEL;
#define DOT_PIXEL_DFT  DOT_PIXEL_1X1  //Default dot pilex

/**
 * Point size fill style
**/
typedef enum {
    DOT_FILL_AROUND  = 1,		// dot pixel 1 x 1
    DOT_FILL_RIGHTUP  , 		// dot pixel 2 X 2
} DOT_STYLE;
#define DOT_STYLE_DFT  DOT_FILL_AROUND  //Default dot pilex

/**
 * Line style, solid or dashed
**/
typedef enum {
    LINE_STYLE_SOLID = 0,
    LINE_STYLE_DOTTED,
} LINE_STYLE;

/**
 * Whether the graphic is filled
**/
typedef enum {
    DRAW_FILL_EMPTY = 0,
    DRAW_FILL_FULL,
} DRAW_FILL;

//init and Clear
void Paint_NewImage(uint8_t Width, uint8_t Height, uint8_t Rotate, uint8_t Color);
void Paint_SelectImage(UBYTE *image);
void Paint_SetClearFuntion(void (*Clear)(uint8_t));
void Paint_SetDisplayFuntion(void (*Display)(uint8_t,uint8_t,uint8_t));
void Paint_SetRotate(uint8_t Rotate);
void Paint_SetMirroring(UBYTE mirror);
void Paint_SetPixel(uint8_t Xpoint, uint8_t Ypoint, uint8_t Color);

void Paint_Clear(uint8_t Color);
void Paint_ClearWindows(uint8_t Xstart, uint8_t Ystart, uint8_t Xend, uint8_t Yend, uint8_t Color);


//Drawing
void Paint_DrawPoint(uint8_t Xpoint, uint8_t Ypoint, uint8_t Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
void Paint_DrawLine(uint8_t Xstart, uint8_t Ystart, uint8_t Xend, uint8_t Yend, uint8_t Color, DOT_PIXEL Line_width, LINE_STYLE Line_Style);
void Paint_DrawRectangle(uint8_t Xstart, uint8_t Ystart, uint8_t Xend, uint8_t Yend, uint8_t Color, DOT_PIXEL Line_width, DRAW_FILL Filled );
void Paint_DrawCircle(uint8_t X_Center, uint8_t Y_Center, uint8_t Radius, uint8_t Color, DOT_PIXEL Line_width, DRAW_FILL Draw_Fill );

//Display string
void Paint_DrawChar(uint8_t Xstart, uint8_t Ystart, const char Acsii_Char, sFONT* Font, uint8_t Color_Background, uint8_t Color_Foreground);
void Paint_DrawString_EN(uint8_t Xstart, uint8_t Ystart, const char * pString, sFONT* Font, uint8_t Color_Background, uint8_t Color_Foreground);
void Paint_DrawNum(uint8_t Xpoint, uint8_t Ypoint, int32_t Nummber, sFONT* Font, uint8_t Color_Background, uint8_t Color_Foreground);

//pic
void Paint_DrawImage(const unsigned char *image,uint8_t Startx, uint8_t Starty,uint8_t Endx, uint8_t Endy); 


#endif





