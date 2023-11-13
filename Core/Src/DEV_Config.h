
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

//#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdio.h>
//#include "spi.h"
//#include "tim.h"
#include "Debug.h"
#include "main.h"

#define UBYTE   uint8_t
#define uint8_t   uint16_t
#define UDOUBLE uint32_t

/**
 * GPIO config
**/
#define DEV_RST_PIN    		 lcd_res_GPIO_Port,lcd_res_Pin
#define DEV_DC_PIN      	lcd_dc_GPIO_Port,lcd_dc_Pin
#define DEV_CS_PIN			lcd_cs_GPIO_Port,lcd_cs_Pin
#define DEV_BL_PIN			lcd_bl_GPIO_Port,lcd_bl_Pin

//#define DEV_BL_PIN			TIM3->CCR2 					//PC7

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) HAL_GPIO_WritePin(_pin, _value == 0? GPIO_PIN_RESET:GPIO_PIN_SET)
#define DEV_Digital_Read(_pin) HAL_GPIO_ReadPin(_pin)

/**
 * SPI
**/
#define DEV_SPI_WRITE(_dat)  DEV_SPI_WRite(_dat);

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) HAL_Delay(__xms)

/**
 * PWM_BL
**/

#define DEV_Set_PWM(_Value) DEV_Digital_Write(DEV_BL_PIN,_Value)
//DEV_BL_PIN= _Value

/*-----------------------------------------------------------------------------*/
void DEV_SPI_WRite(uint8_t _dat);
int DEV_Module_Init(void);
void DEV_Module_Exit(void);
#endif
