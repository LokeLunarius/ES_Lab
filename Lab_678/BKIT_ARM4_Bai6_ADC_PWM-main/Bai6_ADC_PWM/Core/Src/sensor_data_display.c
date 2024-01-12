/*
 * sensor_data_display.c
 *
 *  Created on: Dec 29, 2023
 *      Author: phatl
 */

#include "sensor_data_display.h"

uint8_t count_adc = 0;

void uart_display_float(float num)
{
	int num_front = num;
	int num_back = num*100 - num_front*100;
	uart_Rs232SendNum(num_front);
	uart_Rs232SendString(".");
	uart_Rs232SendNum(num_back);
}

float get_power_consumption(float voltage, float current)
{
//	uart_Rs232SendString("Voltage:		");
//	//uart_display_float(voltage);
//	uart_display_float(voltage);
//	uart_Rs232SendString("mV");
//	uart_Rs232SendString("\n");

//	uart_Rs232SendString("Current:		");
//	uart_display_float(current);
//	uart_Rs232SendString("mA");
//	uart_Rs232SendString("\n");

	float power_usage = voltage*current;
//	uart_Rs232SendString("Power Usage:	");
//	uart_display_float(power_usage);
//	uart_Rs232SendString("mW");
//	uart_Rs232SendString("\n");

	return power_usage;
}

char* light_status(uint16_t light_sensor_data)
{
	if( 0 <= light_sensor_data && light_sensor_data < 2048)
	{
		return "Weak";
	}
	else if(2048 <= light_sensor_data && light_sensor_data < 4096)
	{
		return "Strong";
	}
	return "Sensor Error";
}

float humid_simulation (uint16_t potentiometer)
{
	float data = potentiometer;
	return (data*100)/4095;
}

void sensor_data_send_serial(
		float voltage, float current, float power_usage,
		char* light_density, float humid, float temper)
{
	uart_Rs232SendString("\n");

	uart_Rs232SendNum(ds3231_hours);
	uart_Rs232SendString(":");
	uart_Rs232SendNum(ds3231_min);
	uart_Rs232SendString(":");
	uart_Rs232SendNum(ds3231_sec);
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Voltage: ");
	uart_display_float(voltage);
	uart_Rs232SendString(" mV");
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Current: ");
	uart_display_float(current);
	uart_Rs232SendString(" mA");
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Power Usage: ");
	uart_display_float(power_usage);
	uart_Rs232SendString(" mW");
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Light: ");
	uart_Rs232SendString(light_density);
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Humid: ");
	uart_display_float(humid);
	uart_Rs232SendString(" %");
	uart_Rs232SendString("\n");

	uart_Rs232SendString("Temperature: ");
	uart_display_float(temper);
	uart_Rs232SendString(" C");
	uart_Rs232SendString("\n");

	uart_Rs232SendString("\n");
}

void sensor_data_display()
{
	led7_SetDigit(ds3231_hours/10, 0, 0);
	led7_SetDigit(ds3231_hours%10, 1, 0);
	led7_SetDigit(ds3231_min/10, 2, 0);
	led7_SetDigit(ds3231_min%10, 3, 0);
	count_adc = (count_adc + 1)%20;
	if(count_adc == 0){
		sensor_Read();
		lcd_ShowStr(10, 100, "Voltage:", RED, BLACK, 16, 0);
		lcd_ShowIntNum(120, 100,sensor_GetVoltage()*1000, 4, RED, BLACK, 16);
		lcd_ShowStr(168, 100, "mV", RED, BLACK, 16, 0);

		lcd_ShowStr(10, 120, "Current:", RED, BLACK, 16, 0);
		lcd_ShowIntNum(120, 120,sensor_GetCurrent()/100, 4, RED, BLACK, 16);
		lcd_ShowStr(168, 120, "mA", RED, BLACK, 16, 0);

		float power_usage = get_power_consumption(sensor_GetVoltage()*1000,sensor_GetCurrent()/100);
		lcd_ShowStr(10, 140, "Power Usage:", RED, BLACK, 16, 0);
		lcd_ShowIntNum(120, 140, power_usage, 4, RED, BLACK, 16);
		lcd_ShowStr(168, 140, "mW", RED, BLACK, 16, 0);

		lcd_ShowStr(10, 160, "Light:", RED, BLACK, 16, 0);
		lcd_ShowIntNum(120, 160, sensor_GetLight(), 4, RED, BLACK, 16);
		lcd_ShowStr(168, 160, light_status(sensor_GetLight()), RED, BLACK, 16, 0);

		lcd_ShowStr(10, 180, "Humid Raw:", RED, BLACK, 16, 0);
		lcd_ShowIntNum(120, 180, sensor_GetPotentiometer(), 4, RED, BLACK, 16);

		lcd_ShowStr(10, 200, "Humid:", RED, BLACK, 16, 0);
		lcd_ShowFloatNum(120, 200, humid_simulation(sensor_GetPotentiometer()), 4, RED, BLACK, 16);
		lcd_ShowStr(168, 200, "%", RED, BLACK, 16, 0);

		lcd_ShowStr(10, 220, "Temperature:", RED, BLACK, 16, 0);
		lcd_ShowFloatNum(120, 220,sensor_GetTemperature(), 4, RED, BLACK, 16);
		lcd_ShowStr(168, 220, "C", RED, BLACK, 16, 0);


		sensor_data_send_serial(
				sensor_GetVoltage()*1000,
				sensor_GetCurrent()/100,
				power_usage,
				light_status(sensor_GetLight()),
				humid_simulation(sensor_GetPotentiometer()),
				sensor_GetTemperature()
				);


		if(humid_simulation(sensor_GetPotentiometer()) >= 70)
		{
			if(flag_timer2[2]==1)
			{
				buzzer_SetVolume(50);
				flag_timer2[2] = 0;
				uart_Rs232SendNum(ds3231_hours);
				uart_Rs232SendString(":");
				uart_Rs232SendNum(ds3231_min);
				uart_Rs232SendString(":");
				uart_Rs232SendNum(ds3231_sec);
				uart_Rs232SendString("\n");
				uart_Rs232SendString("Alert High Humid");
			}
		}
		else
		{
			buzzer_SetVolume(0);
		}

	}
}