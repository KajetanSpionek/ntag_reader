/*
 * nfc.h
 *
 *  Created on: 23.01.2019
 *      Author: Kajetan Spionek
 */

#ifndef INC_NFC_H_
#define INC_NFC_H_

#include "stm32f429i_discovery.h"

#define NFC_ADDR 0xAA

void nfc_write(uint8_t addr, uint8_t *data);

void nfc_read(uint8_t addr, uint8_t *data);


#endif /* INC_NFC_H_ */
