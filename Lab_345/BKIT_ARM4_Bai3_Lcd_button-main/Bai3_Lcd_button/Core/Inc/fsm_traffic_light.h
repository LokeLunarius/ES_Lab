/*
 * fsm_traffic_light.h
 *
 *  Created on: Nov 29, 2023
 *      Author: phatl
 */

#ifndef INC_FSM_TRAFFIC_LIGHT_H_
#define INC_FSM_TRAFFIC_LIGHT_H_

#include "all_header.h"

#define INIT			1000000
#define NORMAL			1000001
#define MOD_RED			1000002
#define MOD_YELLOW		1000003
#define MOD_GREEN		1000004

#define RED_LED			1000005
#define RED_BLINK		1000006
#define YELLOW_LED		1000007
#define YELLOW_BLINK	1000008
#define GREEN_LED		1000009
#define GREEN_BLINK		1000010

#define NORTH_SOUTH		1000011
#define EAST_WEST		1000012

extern int status_NS;
extern int status_EW;
extern int status_mode;

void fsm_traffic_light(void);

#endif /* INC_FSM_TRAFFIC_LIGHT_H_ */
