/*
 * fsm_traffic_light.c
 *
 *  Created on: Nov 29, 2023
 *      Author: phatl
 */

#include "fsm_traffic_light.h"

int status_NS = INIT;
int status_EW = INIT;
int status_mode = INIT;
int counter_NS = 0;
int counter_EW = 0;
int blink = 0;
int red_time = 10;
int yellow_time = 2;
int green_time = 7;
int init_red_time = 0;
int init_yellow_time = 0;
int init_green_time = 0;

void led_blink()
{
		lcd_DrawCircle(60, 30, RED, 18, 0);
		lcd_DrawCircle(120, 30, YELLOW, 18, 0);
		lcd_DrawCircle(180, 30, GREEN, 18, 0);

		lcd_DrawCircle(180, 270, RED, 18, 0);
		lcd_DrawCircle(120, 270, YELLOW, 18, 0);
		lcd_DrawCircle(60, 270, GREEN, 18, 0);

		lcd_DrawCircle(30, 90, RED, 18, 0);
		lcd_DrawCircle(30, 150, YELLOW, 18, 0);
		lcd_DrawCircle(30, 210, GREEN, 18, 0);

		lcd_DrawCircle(210, 210, RED, 18, 0);
		lcd_DrawCircle(210, 150, YELLOW, 18, 0);
		lcd_DrawCircle(210, 90, GREEN, 18, 0);
}
void display_led(int status, int direction)
{
	switch (direction) {
		case NORTH_SOUTH:
			switch (status) {
				case RED_LED:
					lcd_DrawCircle(60, 30, RED, 18, 1);
					lcd_DrawCircle(120, 30, YELLOW, 18, 0);
					lcd_DrawCircle(180, 30, GREEN, 18, 0);

					lcd_DrawCircle(180, 270, RED, 18, 1);
					lcd_DrawCircle(120, 270, YELLOW, 18, 0);
					lcd_DrawCircle(60, 270, GREEN, 18, 0);
					break;
				case YELLOW_LED:
					lcd_DrawCircle(60, 30, RED, 18, 0);
					lcd_DrawCircle(120, 30, YELLOW, 18, 1);
					lcd_DrawCircle(180, 30, GREEN, 18, 0);

					lcd_DrawCircle(180, 270, RED, 18, 0);
					lcd_DrawCircle(120, 270, YELLOW, 18, 1);
					lcd_DrawCircle(60, 270, GREEN, 18, 0);
					break;
				case GREEN_LED:
					lcd_DrawCircle(60, 30, RED, 18, 0);
					lcd_DrawCircle(120, 30, YELLOW, 18, 0);
					lcd_DrawCircle(180, 30, GREEN, 18, 1);

					lcd_DrawCircle(180, 270, RED, 18, 0);
					lcd_DrawCircle(120, 270, YELLOW, 18, 0);
					lcd_DrawCircle(60, 270, GREEN, 18, 1);
					break;
				default:
					break;
			}
			break;
		case EAST_WEST:
			switch (status) {
				case RED_LED:
					lcd_DrawCircle(30, 90, RED, 18, 1);
					lcd_DrawCircle(30, 150, YELLOW, 18, 0);
					lcd_DrawCircle(30, 210, GREEN, 18, 0);

					lcd_DrawCircle(210, 210, RED, 18, 1);
					lcd_DrawCircle(210, 150, YELLOW, 18, 0);
					lcd_DrawCircle(210, 90, GREEN, 18, 0);
					break;
				case YELLOW_LED:
					lcd_DrawCircle(30, 90, RED, 18, 0);
					lcd_DrawCircle(30, 150, YELLOW, 18, 1);
					lcd_DrawCircle(30, 210, GREEN, 18, 0);

					lcd_DrawCircle(210, 210, RED, 18, 0);
					lcd_DrawCircle(210, 150, YELLOW, 18, 1);
					lcd_DrawCircle(210, 90, GREEN, 18, 0);
					break;
				case GREEN_LED:
					lcd_DrawCircle(30, 90, RED, 18, 0);
					lcd_DrawCircle(30, 150, YELLOW, 18, 0);
					lcd_DrawCircle(30, 210, GREEN, 18, 1);

					lcd_DrawCircle(210, 210, RED, 18, 0);
					lcd_DrawCircle(210, 150, YELLOW, 18, 0);
					lcd_DrawCircle(210, 90, GREEN, 18, 1);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}


void mode_normal()
{
	if(status_NS == RED_LED)
	{
		if(counter_NS == 0 && counter_EW == 0)
		{
			lcd_Clear(WHITE);
			counter_NS = init_green_time;
			counter_EW = init_red_time;
			status_NS = GREEN_LED;
			status_EW = RED_LED;
		}
		if(counter_EW == 0 && counter_NS > 0)
		{
			lcd_Clear(WHITE);
			counter_EW = init_yellow_time + 1;
			status_EW = YELLOW_LED;
		}
	}
	else if(status_EW == RED_LED)
	{
		if(counter_NS == 0 && counter_EW == 0)
		{
			lcd_Clear(WHITE);
			counter_NS = init_red_time;
			counter_EW = init_green_time;
			status_NS = RED_LED;
			status_EW = GREEN_LED;
		}
		if(counter_NS == 0 && counter_EW > 0)
		{
			lcd_Clear(WHITE);
			counter_NS = init_yellow_time + 1;
			status_NS = YELLOW_LED;
		}
	}

	display_led(status_NS, NORTH_SOUTH);
	display_led(status_EW, EAST_WEST);
	counter_NS--;
	counter_EW--;
}

void increase_time_led()
{
	switch (status_mode) {
		case MOD_RED:
			if(red_time > 99)
			{
				red_time = 1;
			}
			red_time++;
			break;
		case MOD_YELLOW:
			if(yellow_time > 3)
			{
				yellow_time = 1;
			}
			yellow_time++;
			break;
		case MOD_GREEN:
			if(green_time >= red_time - yellow_time)
			{
				green_time = 1;
			}
			green_time++;
			break;
		default:
			break;
	}
}

void decrease_time_led()
{
	switch (status_mode) {
		case MOD_RED:
			if(red_time <= 0)
			{
				red_time = 99;

			}
			red_time--;
			break;
		case MOD_YELLOW:
			if(yellow_time <= 0)
			{
				yellow_time = 3;
			}
			yellow_time++;
			break;
		case MOD_GREEN:
			if(green_time <= 0)
			{
				green_time = init_red_time - init_yellow_time;
			}
			green_time--;
			break;
		default:
			break;
	}
}

void fsm_traffic_light(void)
{
	button_Scan();
	switch (status_mode) {
		case INIT:
			init_red_time = red_time;
			init_yellow_time = yellow_time;
			init_green_time = green_time;
			status_NS = RED_LED;
			counter_NS = init_red_time;
			status_EW = GREEN_LED;
			counter_EW = init_green_time;
			status_mode = NORMAL;
		case NORMAL:
//			led7_SetDigit(counter_NS/10, 0, 0);
//			led7_SetDigit(counter_NS%10, 1, 0);
//			led7_SetDigit(counter_EW/10, 2, 0);
//			led7_SetDigit(counter_EW%10, 3, 0);
			if(flag_timer2[5] == 1)
			{
				led7_SetDigit(counter_NS/10, 0, 0);
				led7_SetDigit(counter_NS%10, 1, 0);
				led7_SetDigit(counter_EW/10, 2, 0);
				led7_SetDigit(counter_EW%10, 3, 0);
			}
			if(flag_timer2[1] == 1)
			{
				mode_normal();
				flag_timer2[1]	= 0;
			}
			if(button_count[0] == 1)
			{
				HAL_Delay(300);
				button_count[0] = 0;
				led_blink();
				status_mode = MOD_RED;
			}
			break;
		case MOD_RED:
			if(flag_timer2[5] == 1)
			{
				flag_timer2[5] = 0;
				led7_SetDigit(red_time/10, 0, 0);
				led7_SetDigit(red_time%10, 1, 0);
				led7_SetDigit(init_red_time/10, 2, 0);
				led7_SetDigit(init_red_time%10, 3, 0);
			}
			if(flag_timer2[2] == 1)
			{
				if(blink == 0)
				{
					display_led(RED_LED, NORTH_SOUTH);
					display_led(RED_LED, EAST_WEST);
					blink = 1;
				}
				else
				{
					blink = 0;
					lcd_Clear(WHITE);
					led_blink();
				}
				flag_timer2[2] = 0;
			}
			if(button_count[0] == 1)
			{
				HAL_Delay(300);
				button_count[0] = 0;
				led_blink();
				status_mode = MOD_GREEN;
			}
			if(button_count[1] == 1)
			{
				HAL_Delay(300);
				button_count[1] = 0;
				increase_time_led();
			}
			if(button_count[2] == 1)
			{
				HAL_Delay(300);
				button_count[2] = 0;
				decrease_time_led();
			}
			if(button_count[3]==1)
			{
				HAL_Delay(300);
				button_count[3] = 0;
				init_red_time = red_time;
				init_green_time = init_red_time - init_yellow_time - 1;
				if(status_NS == RED_LED)
				{
					counter_NS = init_red_time;
					counter_EW = init_green_time;
				}
				else if(status_EW == RED_LED)
				{
					counter_NS = init_green_time;
					counter_EW = init_red_time;
				}
			}
			break;
		case MOD_YELLOW:
			if(flag_timer2[5] == 1)
			{
				flag_timer2[5] = 0;
				led7_SetDigit(yellow_time/10, 0, 0);
				led7_SetDigit(yellow_time%10, 1, 0);
				led7_SetDigit(init_yellow_time/10, 2, 0);
				led7_SetDigit(init_yellow_time%10, 3, 0);
			}
			if(flag_timer2[3] == 1)
			{
				if(blink == 0)
				{
					display_led(YELLOW_LED, NORTH_SOUTH);
					display_led(YELLOW_LED, EAST_WEST);
					blink = 1;
				}
				else
				{
					blink = 0;
					lcd_Clear(WHITE);
					led_blink();
				}
				flag_timer2[3] = 0;
			}
			if(button_count[0] == 1)
			{
				HAL_Delay(300);
				button_count[0] = 0;
				led_blink();
				status_mode = NORMAL;
				red_time = init_red_time;
				yellow_time = init_yellow_time;
				green_time = init_green_time;
			}
			if(button_count[1] == 1)
			{
				HAL_Delay(300);
				button_count[1] = 0;
				increase_time_led();
			}
			if(button_count[2] == 1)
			{
				HAL_Delay(300);
				button_count[2] = 0;
				decrease_time_led();
			}
			if(button_count[3]==1)
			{
				HAL_Delay(300);
				button_count[3] = 0;
				init_yellow_time = red_time;
				init_green_time = init_red_time - init_yellow_time - 1;
				if(status_NS == RED_LED)
				{
					counter_NS = init_red_time;
					counter_EW = init_green_time;
				}
				else if(status_EW == RED_LED)
				{
					counter_NS = init_green_time;
					counter_EW = init_red_time;
				}
			}
			break;
		case MOD_GREEN:
			if(flag_timer2[5] == 1)
			{
				flag_timer2[5] = 0;
				led7_SetDigit(green_time/10, 0, 0);
				led7_SetDigit(green_time%10, 1, 0);
				led7_SetDigit(init_green_time/10, 2, 0);
				led7_SetDigit(init_green_time%10, 3, 0);
			}
			if(flag_timer2[4] == 1)
			{
				if(blink == 0)
				{
					display_led(GREEN_LED, NORTH_SOUTH);
					display_led(GREEN_LED, EAST_WEST);
					blink = 1;
				}
				else
				{
					blink = 0;
					lcd_Clear(WHITE);
					led_blink();
				}
				flag_timer2[4] = 0;
			}
			if(button_count[0] == 1)
			{
				HAL_Delay(300);
				button_count[0] = 0;
				led_blink();
				status_mode = MOD_YELLOW;
			}
			if(button_count[1] == 1)
			{
				HAL_Delay(300);
				button_count[1] = 0;
				increase_time_led();
			}
			if(button_count[2] == 1)
			{
				HAL_Delay(300);
				button_count[2] = 0;
				decrease_time_led();
			}
			if(button_count[3]==1)
			{
				HAL_Delay(300);
				button_count[3] = 0;
				init_green_time = green_time;
				init_red_time = init_green_time + init_yellow_time + 1;
				if(status_NS == RED_LED)
				{
					counter_NS = init_red_time;
					counter_EW = init_green_time;
				}
				else if(status_EW == RED_LED)
				{
					counter_NS = init_green_time;
					counter_EW = init_red_time;
				}
			}
			break;
		default:
			break;
	}
}
