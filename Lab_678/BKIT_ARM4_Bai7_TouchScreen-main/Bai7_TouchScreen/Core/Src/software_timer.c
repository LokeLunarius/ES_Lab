/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

#define TIMER_CYCLE_2 1

//software timer variable
uint16_t flag_timer2[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t timer2_counter[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t timer2_MUL[12] = {0,0,0,0,0,0,0,0,0,0,0,0};


/**
  * @brief  Init timer interrupt
  * @param  None
  * @retval None
  */
void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}


void timer_EnableDelayUs(){
	HAL_TIM_Base_Start(&htim1);
}
/**
  * @brief  Set duration of software timer interrupt
  * @param  duration Duration of software timer interrupt
  * @retval None
  */
void setTimer2(uint16_t duration, int tim2_arr_pos){
	timer2_MUL[tim2_arr_pos] = duration/TIMER_CYCLE_2;
	timer2_counter[tim2_arr_pos] = timer2_MUL[tim2_arr_pos];
	flag_timer2[tim2_arr_pos] = 0;
}

/**
  * @brief  Timer interrupt routine
  * @param  htim TIM Base handle
  * @note	This callback function is called by system
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		for(int i = 0; i < 12; i++)
		{
			if(timer2_counter[i] > 0){
				timer2_counter[i]--;
				if(timer2_counter[i] == 0) {
					flag_timer2[i] = 1;
					timer2_counter[i] = timer2_MUL[i];
				}
			}
		}
		// 1ms interrupt here
		led7_Scan();
	}
}

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
}

