/* Added adapter, 1 November 2026: report API to the user-supplied driver. */
#include "ssd1306_compat.h"

void SSD1306_Init(I2C_HandleTypeDef *i2c)
{
    if (i2c != &hi2c1) return;  /* Supplied driver is bound to hi2c1. */
    ssd1306_Init();
    ssd1306_Fill(0);
    ssd1306_UpdateScreen();
}

void SSD1306_Clear(void)
{
    ssd1306_Fill(0);  /* Clear the local framebuffer. */
}

void SSD1306_WriteText(uint16_t x, uint16_t y, const char *text)
{
    if (text == NULL || x > SSD1306_WIDTH - 6u ||
        y > SSD1306_HEIGHT - 7u) return;
    ssd1306_SetCursor((uint8_t)x, (uint8_t)y);
    ssd1306_WriteString(text);
}

void SSD1306_DrawBar(uint16_t x, uint16_t y, uint16_t width,
                     uint16_t height, uint16_t percentage)
{
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT ||
        width == 0u || height == 0u) return;

    /* Clip before adding coordinates or narrowing to the pixel API. */
    if (width > SSD1306_WIDTH - x) width = SSD1306_WIDTH - x;
    if (height > SSD1306_HEIGHT - y) height = SSD1306_HEIGHT - y;
    if (percentage > 100u) percentage = 100u;

    uint16_t fill_width = (width > 2u)
        ? (uint16_t)(((uint32_t)(width - 2u) * percentage) / 100u) : 0u;

    for (uint16_t row = 0; row < height; ++row)
    {
        for (uint16_t col = 0; col < width; ++col)
        {
            bool border = row == 0u || row == height - 1u ||
                          col == 0u || col == width - 1u;
            bool filled = col > 0u && col <= fill_width;
            ssd1306_DrawPixel((uint8_t)(x + col), (uint8_t)(y + row),
                              border || filled);
        }
    }
}

void SSD1306_Update(void)
{
    ssd1306_UpdateScreen();  /* Send the framebuffer over I2C. */
}
