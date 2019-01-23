#include "lcd.h"

extern UART_HandleTypeDef huart1;

/**
   * @brief Screen initialization
   * @param None
   * @retval None
   */
void lcd_Init(void) {
	
	BSP_LCD_Init();
	BSP_TS_Init(240, 360);
	
	BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
}

/**
   * @brief Displaying header on lcd "RDIF SYSTEM"
   * @param None
   * @retval None
   */
void lcd_DisplayHeader(void) {
	
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_DisplayStringAtLine(0,(uint8_t*)" NTAG  READER");
	//BSP_LCD_DisplayStringAtLine(12,(uint8_t*)"Nfc: Missing  ");
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
}

/**
   * @brief Displaying status of field detect
   * @param None
   * @retval None
   */
void lcd_DisplayFDStatus(void) {

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2) == 0) BSP_LCD_DisplayStringAtLine(12,(uint8_t*)"Nfc: In range  ");
	else BSP_LCD_DisplayStringAtLine(12,(uint8_t*)"Nfc: Missing  ");
	
}

/**
   * @brief Displaying pin keyboard
   * @param None
   * @retval None
   */
void lcd_Menu(void) {
	

	BSP_LCD_Clear(LCD_COLOR_WHITE);
	lcd_DisplayHeader();
	int start_x = 20;
	int start_y = 50;
	
	// Create borders
		for (int constx = 0; constx < 3; constx++) {
			lcd_PickColor(constx);
			BSP_LCD_FillRect(start_x,start_y+65*constx,199,49);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_DrawRect(start_x,start_y+65*constx,199,49);
		}
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
}

/**
   * @brief Clearing lcd screen
   * @param None
   * @retval None
   */
void lcd_ClearScreen(void) {
	
	BSP_LCD_Clear(LCD_COLOR_WHITE);	
}

void lcd_PickColor(uint8_t color) {
	switch(color) {
	case 0:
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTCYAN);
		break;
	case 1:
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTMAGENTA);
		break;
	case 2:
		BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
		break;
	default:
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		break;

	}
}

void lcd_info() {

	uint8_t data[16];
	uint8_t mes[50];

	//lcd_ClearScreen();
	void lcd_DisplayHeader(void);
	void lcd_DisplayFDStatus(void);

	//HAL_I2C_Mem_Read(&hi2c3, 0xAA, 0x00, 1, data,16,100);
	nfc_read(0x00, &data);

	sprintf(mes, "Uid:%x-%x-%x-%x", data[0], data[1], data[2], data[3]);
	BSP_LCD_DisplayStringAtLine(2,(uint8_t*)mes);
	sprintf(mes, "Uid:%x-%x-%x-%x", data[4], data[5], data[6], data[7]);
	BSP_LCD_DisplayStringAtLine(3,(uint8_t*)mes);
	sprintf(mes, "Conf:%2x-%2x", data[8], data[9]);
	BSP_LCD_DisplayStringAtLine(4,(uint8_t*)mes);
	sprintf(mes, "Lock:%2x-%2x", data[10], data[11]);
	BSP_LCD_DisplayStringAtLine(5,(uint8_t*)mes);
	sprintf(mes, "CC:%x-%x-%x-%x", data[12], data[13], data[14], data[15]);
	BSP_LCD_DisplayStringAtLine(6,(uint8_t*)mes);

	//HAL_I2C_Mem_Read(&hi2c3, 0xAA, 0x05, 1, data,16,100);
	nfc_read(0x05, &data);
	sprintf(mes, "V:%x-%x-%x-%x", data[0], data[1], data[2], data[3]);
	BSP_LCD_DisplayStringAtLine(8,(uint8_t*)mes);
}

/**
   * @brief Displaying pin keyboard
   * @param None
   * @retval None
   */
void lcd_ToggleKeyboard(void) {

	BSP_LCD_Clear(LCD_COLOR_WHITE);
	//lcd_DisplayPinState(0);

	int start_x = 25;
	int start_y = 60;

	// Create borders
	for (int const_x = 0; const_x < 3; const_x++) {
		for (int const_y = 0; const_y < 4; const_y++) {
			BSP_LCD_SetTextColor(LCD_COLOR_LIGHTCYAN);
			BSP_LCD_FillRect(start_x+70*const_x,start_y+65*const_y,49,49);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_DrawRect(start_x+70*const_x,start_y+65*const_y,49,49);

		}
	}

	lcd_KeyboardRow1();
	lcd_KeyboardRow2();
	lcd_KeyboardRow3();
	lcd_KeyboardRow4();

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

}

/**
   * @brief Displaying row 1 of buttons on keyboard
   * @param None
   * @retval None
   */
void lcd_KeyboardRow1(void) {

		uint8_t bit_map_1[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
															};

	uint8_t bit_map_2[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
																{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
															};

	uint8_t bit_map_3[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
															};
			// 1

		int base_x = 26;
		int base_y = 61;
		// 26,61

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_1[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// 2

		base_x = 96;
		base_y = 61;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_2[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// 3

		base_x = 166;
		base_y = 61;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_3[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}



}



/**
   * @brief Displaying row 2 of buttons on keyboard
   * @param None
   * @retval None
   */
void lcd_KeyboardRow2(void) {

	uint8_t bit_map_4[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
															};

	uint8_t bit_map_5[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
															};


	uint8_t bit_map_6[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
															};



	// 4

		int base_x = 26;
		int base_y = 126;


		// 26,61

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_4[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// 5

		base_x = 96;
		base_y = 126;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_5[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// 6

		base_x = 166;
		base_y = 126;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_6[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}






}



/**
   * @brief Displaying row 3 of buttons on keyboard
   * @param None
   * @retval None
   */
void lcd_KeyboardRow3(void) {

		uint8_t bit_map_7[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
																{0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
															};

	uint8_t bit_map_8[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
															};

	uint8_t bit_map_9[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
															};


		// 7

		int base_x = 26;
		int base_y = 191;

		// 26,61

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_7[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// 8

		base_x = 96;
		base_y = 191;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_8[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// 9

		base_x = 166;
		base_y = 191;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_9[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

}



/**
   * @brief Displaying row 4 of buttons on keyboard
   * @param None
   * @retval None
   */
void lcd_KeyboardRow4(void) {

	uint8_t bit_map_0[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
																};

	uint8_t bit_map_L[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
																{0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0},
																{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
																{0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
																{0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0},
																{0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																};

	uint8_t bit_map_R[12][12] = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
																{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
																};










	// L

		int base_x = 26;
		int base_y = 256;

		// 26,61

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_L[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// 0

		base_x = 96;
		base_y = 256;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_0[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

		// R

		base_x = 166;
		base_y = 256;

		for (int temp_y = 0; temp_y < 12; temp_y++) {
			for (int temp_x = 0; temp_x < 12; temp_x++) {
				if (bit_map_R[temp_y][temp_x] == 1)
					BSP_LCD_FillRect(base_x+temp_x*4,base_y+temp_y*4,4,4);
			}
		}

}

/**
   * @brief Displaying pin progress
   * @param no_digits: numbers of digits already pressed while inputing password
   * @retval None
   */
void lcd_DisplayValues(uint8_t* data, uint8_t digits) {

	BSP_LCD_ClearStringLine(1);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	uint8_t mes[30];

	switch(digits) {
		case 1: sprintf(mes," VAL: %d _ _ _ ",data[0]); break;
		case 2: sprintf(mes," VAL: %d %d _ _ ",data[0], data[1]); break;
		case 3: sprintf(mes," VAL: %d %d %d _ ",data[0], data[1], data[2]); break;
		case 4: sprintf(mes," VAL: %d %d %d %d ",data[0], data[1], data[2], data[3]); break;
		default: sprintf(mes," VAL: _ _ _ _ "); break;
	}
	BSP_LCD_DisplayStringAtLine(1, (uint8_t*)mes);
}







