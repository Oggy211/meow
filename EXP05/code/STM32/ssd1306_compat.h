#ifndef SSD1306_COMPAT_H
#define SSD1306_COMPAT_H

#include "ssd1306.h"

/* Adapter for the report API; the user driver supports the global hi2c1 only. */
void SSD1306_Init(I2C_HandleTypeDef *i2c);
void SSD1306_Clear(void);
void SSD1306_WriteText(uint16_t x, uint16_t y, const char *text);
void SSD1306_DrawBar(uint16_t x, uint16_t y, uint16_t width,
                     uint16_t height, uint16_t percentage);
void SSD1306_Update(void);

#endif
