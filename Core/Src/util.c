/*
 * util.c
 *
 *  Created on: 23.01.2019
 *      Author: Kajetan Spionek
 *
 */

#include "util.h"

void clean_mem(void) {
	uint8_t data[16] = {0};
	uint8_t addr = 0x05;
	nfc_write(addr, &data);
}

void write_value(void) {
	HAL_Delay(100);
	uint32_t x = 0;
	uint32_t y = 0;
	uint8_t status = 0;
	uint8_t data[16] = {0};
	uint8_t clicked_tile = 0xFF;

	lcd_ToggleKeyboard();
	lcd_DisplayValues(&data, status);


	while(status < 4) {
		t_TouchDetect(&x, &y);
		clicked_tile = t_BoxDetect(x,y);
		if (clicked_tile != 0xFF && clicked_tile != 0xEE) {
			data[status] = clicked_tile;
			clicked_tile = 0xFF;
			status+=1;
			lcd_DisplayValues(&data, status);
			HAL_Delay(100);
		}
	};
	nfc_write(0x05, &data);
	lcd_ClearScreen();
}

