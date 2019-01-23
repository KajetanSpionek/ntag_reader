/*
 * nfc.c
 *
 *  Created on: 23.01.2019
 *      Author: Kajetan Spionek
 */

#include "nfc.h"

extern I2C_HandleTypeDef hi2c3;

void nfc_write(uint8_t addr, uint8_t *data) {
	HAL_I2C_Mem_Write(&hi2c3, NFC_ADDR, addr, 1, data, 16, 100);
}

void nfc_read(uint8_t addr, uint8_t *data) {
	HAL_I2C_Mem_Read(&hi2c3, 0xAA, addr, 1, data, 16, 100);
}


