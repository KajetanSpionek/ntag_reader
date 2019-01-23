/*
 * touch.c
 *
 *  Created on: 23.01.2019
 *      Author: Kajetan Spionek
 */

#include "touch.h"

/**
   * @brief Detecting touch position (x,y)
   * @param x: pointer to horizonal touched (on screen) position
   * @param y: pointer to vertical touched (on screen) position
   * @retval None
   */
void t_TouchDetect(uint32_t *x, uint32_t *y) {

	static TS_StateTypeDef TS_State;
	static uint32_t xx = 0, yy = 0;
	/* Get touch screen position */
	BSP_TS_GetState(&TS_State);

	xx = TS_State.X;
	yy = TS_State.Y;

	/* Checks if touch is detected */
	if(TS_State.TouchDetected){
	*x = xx;
	*y = yy;
	} else {
		*x = 9999;
		*y = 9999;
	}
}

/**
   * @brief Determines key which was pressed (on menu)
   * @param x: horizonal touched (on screen) position
   * @param y: vertical touched (on screen) position
   * @retval box: returns key key which was pressed
   */
uint8_t t_BoxMenu(uint32_t x, uint32_t y) {

		// Row 1
		if (y > 50 && y < 100) {
				return 0x01;
			}
		// Row 2
			if (y > 115 && y < 165) {
				return 0x02;
			}
		// Row 3
			if (y > 180 && y < 230) {
				return 0x03;
			}
		// Other place
			if (y > 0 && y < 320) {
				return 0x04;
			}
		// Not touched
			if (x == 9999 && y == 9999) return 0xEE;
			return 0xFF;
}

uint8_t t_BoxDetect(uint32_t x, uint32_t y) {

		// Row 1

		if (y > 60 && y < 110) {
				if (x > 25 && x < 75) return 0x1;
				if (x > 95 && x < 145) return 0x2;
				if (x > 165 && x < 215) return 0x3;
			}

		// Row 2

			if (y > 125 && y < 175) {
				if (x > 25 && x < 75) return 0x4;
				if (x > 95 && x < 145) return 0x5;
				if (x > 165 && x < 215)	return 0x6;
			}

		// Row 3

			if (y > 190 && y < 240) {
				if (x > 25 && x < 75) return 0x7;
				if (x > 95 && x < 145) return 0x8;
				if (x > 165 && x < 215)	return 0x9;
			}

		// Row 4

			if (y > 255 && y < 305) {
				if (x > 25 && x < 75) return 0x0A;
				if (x > 95 && x < 145) return 0x0;
				if (x > 165 && x < 215)	return 0x0B;
			}

		// Not touched

			if (x == 9999 && y == 9999) return 0xEE;

			return 0xFF;
}









