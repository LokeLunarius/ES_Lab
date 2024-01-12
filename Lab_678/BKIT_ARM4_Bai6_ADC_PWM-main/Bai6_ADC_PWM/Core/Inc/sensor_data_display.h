/*
 * sensor_data_display.h
 *
 *  Created on: Dec 29, 2023
 *      Author: phatl
 */

#ifndef INC_SENSOR_DATA_DISPLAY_H_
#define INC_SENSOR_DATA_DISPLAY_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "led_7seg.h"
#include "button.h"
#include "lcd.h"
#include "picture.h"
#include "ds3231.h"
#include "uart.h"
#include "sensor.h"
#include "buzzer.h"
/* USER CODE END Includes */

void sensor_data_display();

#endif /* INC_SENSOR_DATA_DISPLAY_H_ */
