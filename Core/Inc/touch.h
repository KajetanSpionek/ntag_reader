/*
 * touch.h
 *
 *  Created on: 23.01.2019
 *      Author: Kajetan Spionek
 */

#ifndef INC_TOUCH_H_
#define INC_TOUCH_H_

#include "stm32f429i_discovery_ts.h"

void t_TouchDetect(uint32_t *x, uint32_t *y);
uint8_t t_BoxDetect(uint32_t x, uint32_t y);
uint8_t t_BoxMenu(uint32_t x, uint32_t y);

#endif /* INC_TOUCH_H_ */
