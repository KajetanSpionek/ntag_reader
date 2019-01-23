/*!
* \file lcd.h
* \author Kajetan Spionek
* Handles graphical interface displayed on LCD screen
*/

#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "nfc.h"

void lcd_Init(void);
void lcd_DisplayHeader(void);
void lcd_DisplayFDStatus(void);

void lcd_Menu(void);
void lcd_ClearScreen(void);
void lcd_PickColor(uint8_t color);
uint8_t lcd_BoxMenu(uint32_t x, uint32_t y);

void lcd_info(void);

void lcd_ToggleKeyboard(void);
void lcd_KeyboardRow1(void);
void lcd_KeyboardRow2(void);
void lcd_KeyboardRow3(void);
void lcd_KeyboardRow4(void);
void lcd_DisplayValues(uint8_t* data, uint8_t digits);



