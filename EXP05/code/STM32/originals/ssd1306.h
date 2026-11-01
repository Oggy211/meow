#ifndef SSD1306_H
#define SSD1306_H

#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <string.h>

#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT  64

// 7-bit address is 0x3C on most modules; HAL expects left-shifted 8-bit form
#define SSD1306_I2C_ADDR   (0x3C << 1)

extern I2C_HandleTypeDef hi2c1;

void ssd1306_Init(void);
void ssd1306_Fill(uint8_t color);              // 0x00 = black, 0xFF = white (for byte fill)
void ssd1306_UpdateScreen(void);
void ssd1306_DrawPixel(uint8_t x, uint8_t y, bool color);
// --- Simple text API (5x7 font) ---
void ssd1306_SetCursor(uint8_t x, uint8_t y);     // x,y in pixels (top-left of text)
void ssd1306_WriteChar(char ch);                  // draws 5x7 + 1px spacing
void ssd1306_WriteString(const char *s);          // draws until '\0' or edge

#endif
