#include "ssd1306.h"

static uint8_t ssd1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];
// ---- Simple text state ----
static uint8_t cursor_x = 0, cursor_y = 0;

// 5x7 font (ASCII subset). Each glyph is 5 columns, LSB = top pixel.
// Characters not in table will render as space.
typedef struct { char c; uint8_t col[5]; } glyph5x7_t;

static const glyph5x7_t FONT5x7[] = {
    // Digits
    {'0',{0x3E,0x45,0x49,0x51,0x3E}},
    {'1',{0x00,0x21,0x7F,0x01,0x00}},
    {'2',{0x21,0x43,0x45,0x49,0x31}},
    {'3',{0x42,0x41,0x51,0x69,0x46}},
    {'4',{0x0C,0x14,0x24,0x7F,0x04}},
    {'5',{0x72,0x51,0x51,0x51,0x4E}},
    {'6',{0x1E,0x29,0x49,0x49,0x06}},
    {'7',{0x40,0x47,0x48,0x50,0x60}},
    {'8',{0x36,0x49,0x49,0x49,0x36}},
    {'9',{0x30,0x49,0x49,0x4A,0x3C}},

    // Uppercase A–Z
    {'A',{0x3F,0x48,0x48,0x48,0x3F}},
    {'B',{0x7F,0x49,0x49,0x49,0x36}},
    {'C',{0x3E,0x41,0x41,0x41,0x22}},
    {'D',{0x7F,0x41,0x41,0x22,0x1C}},
    {'E',{0x7F,0x49,0x49,0x49,0x41}},
    {'F',{0x7F,0x48,0x48,0x48,0x40}},
    {'G',{0x3E,0x41,0x49,0x49,0x2E}},
    {'H',{0x7F,0x08,0x08,0x08,0x7F}},
    {'I',{0x00,0x41,0x7F,0x41,0x00}},
    {'J',{0x02,0x01,0x41,0x7E,0x40}},
    {'K',{0x7F,0x08,0x14,0x22,0x41}},
    {'L',{0x7F,0x01,0x01,0x01,0x01}},
    {'M',{0x7F,0x20,0x18,0x20,0x7F}},
    {'N',{0x7F,0x10,0x08,0x04,0x7F}},
    {'O',{0x3E,0x41,0x41,0x41,0x3E}},
    {'P',{0x7F,0x48,0x48,0x48,0x30}},
    {'Q',{0x3E,0x41,0x45,0x42,0x3D}},
    {'R',{0x7F,0x48,0x4C,0x4A,0x31}},
    {'S',{0x31,0x49,0x49,0x49,0x46}},
    {'T',{0x40,0x40,0x7F,0x40,0x40}},
    {'U',{0x7E,0x01,0x01,0x01,0x7E}},
    {'V',{0x7C,0x02,0x01,0x02,0x7C}},
    {'W',{0x7E,0x01,0x0E,0x01,0x7E}},
    {'X',{0x63,0x14,0x08,0x14,0x63}},
    {'Y',{0x70,0x08,0x07,0x08,0x70}},
    {'Z',{0x43,0x45,0x49,0x51,0x61}},

    // Minimal punctuation / space
    {' ',{0x00,0x00,0x00,0x00,0x00}},
    {':',{0x00,0x36,0x36,0x00,0x00}},
    {'-',{0x08,0x08,0x08,0x08,0x08}},
    {'.',{0x00,0x60,0x60,0x00,0x00}},
    {'/',{0x03,0x0C,0x30,0x40,0x00}},
};
static const uint16_t FONT5x7_SZ = sizeof(FONT5x7)/sizeof(FONT5x7[0]);

static const uint8_t* font5x7_lookup(char c){
    for (uint16_t i=0;i<FONT5x7_SZ;i++){
        if (FONT5x7[i].c == c) return FONT5x7[i].col;
    }
    // fallback = space
    for (uint16_t i=0;i<FONT5x7_SZ;i++){
        if (FONT5x7[i].c == ' ') return FONT5x7[i].col;
    }
    return NULL;
}

// ---- Low-level helpers ----
static void ssd1306_WriteCommand(uint8_t cmd) {
    uint8_t tx[2] = {0x00, cmd}; // 0x00 = control byte for commands
    HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, tx, 2, HAL_MAX_DELAY);
}

static void ssd1306_WriteDataChunk(uint8_t *data, uint16_t len) {
    // 0x40 = control byte for data
    // send in small chunks so stack/driver buffers aren’t exceeded
    while (len) {
        uint8_t chunk = (len > 16) ? 16 : len;
        uint8_t tx[1 + 16];
        tx[0] = 0x40;
        memcpy(&tx[1], data, chunk);
        HAL_I2C_Master_Transmit(&hi2c1, SSD1306_I2C_ADDR, tx, (uint16_t)(1 + chunk), HAL_MAX_DELAY);
        data += chunk;
        len  -= chunk;
    }
}

// ---- Public API ----
void ssd1306_Init(void) {
    HAL_Delay(100); // small power-up delay

    ssd1306_WriteCommand(0xAE); // Display OFF

    // --- Memory addressing mode ---
    ssd1306_WriteCommand(0x20); // Set Memory Addressing Mode
    ssd1306_WriteCommand(0x00); // Horizontal Addressing Mode

    // --- Display orientation (FIXED) ---
    ssd1306_WriteCommand(0xA1); // Segment remap: column addr 0 mapped to SEG0 (normal)
    ssd1306_WriteCommand(0xC8); // COM scan direction: normal (COM0 = top row)

    // --- Display geometry ---
    ssd1306_WriteCommand(0x40); // Set display start line = 0
    ssd1306_WriteCommand(0xD3); // Display offset
    ssd1306_WriteCommand(0x00); // No offset

    // --- Multiplex ratio (height - 1) ---
    ssd1306_WriteCommand(0xA8);
    ssd1306_WriteCommand(0x3F); // 0x3F = 63 for 128x64 display

    // --- COM pin hardware configuration ---
    ssd1306_WriteCommand(0xDA);
    ssd1306_WriteCommand(0x12);

    // --- Contrast ---
    ssd1306_WriteCommand(0x81);
    ssd1306_WriteCommand(0x7F);

    // --- Pre-charge period ---
    ssd1306_WriteCommand(0xD9);
    ssd1306_WriteCommand(0xF1);

    // --- VCOMH deselect level ---
    ssd1306_WriteCommand(0xDB);
    ssd1306_WriteCommand(0x40);

    // --- Clock divide ratio/oscillator freq ---
    ssd1306_WriteCommand(0xD5);
    ssd1306_WriteCommand(0x80);

    // --- Charge pump ---
    ssd1306_WriteCommand(0x8D);
    ssd1306_WriteCommand(0x14);

    // --- Resume and normal display ---
    ssd1306_WriteCommand(0xA4); // Entire display ON (resume RAM content)
    ssd1306_WriteCommand(0xA6); // Normal display (not inverted)

    // --- Turn display ON ---
    ssd1306_WriteCommand(0xAF);
}

void ssd1306_Fill(uint8_t color) {
    memset(ssd1306_Buffer, color, sizeof(ssd1306_Buffer));
}

// Horizontal addressing: set full column/page then dump buffer
void ssd1306_UpdateScreen(void) {
    ssd1306_WriteCommand(0x21); // set column address
    ssd1306_WriteCommand(0x00); // start
    ssd1306_WriteCommand(SSD1306_WIDTH - 1); // end

    ssd1306_WriteCommand(0x22); // set page address
    ssd1306_WriteCommand(0x00); // start page
    ssd1306_WriteCommand((SSD1306_HEIGHT/8) - 1); // end page

    ssd1306_WriteDataChunk(ssd1306_Buffer, sizeof(ssd1306_Buffer));
}

void ssd1306_DrawPixel(uint8_t x, uint8_t y, bool color) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;

    // If using COM scan dec (0xC8), flip Y so lines are top→bottom
    y = (SSD1306_HEIGHT - 1u) - y;

    uint16_t byteIndex = x + (y / 8) * SSD1306_WIDTH;
    uint8_t  bitMask   = 1u << (y % 8);
    if (color) ssd1306_Buffer[byteIndex] |=  bitMask;
    else       ssd1306_Buffer[byteIndex] &= ~bitMask;
}

void ssd1306_SetCursor(uint8_t x, uint8_t y){
    cursor_x = x;
    cursor_y = y;
}

void ssd1306_WriteChar(char ch){
    const uint8_t* g = font5x7_lookup(ch);
    if (!g) return;

    // Draw 5 columns × 7 rows
    for (uint8_t col=0; col<5; col++){
        uint8_t colbits = g[col];
        for (uint8_t row=0; row<7; row++){
            bool on = (colbits & (1U << row)) != 0;
            ssd1306_DrawPixel(cursor_x + col, cursor_y + row, on);
        }
    }
    // 1px spacing column (clear it)
    for (uint8_t row=0; row<7; row++){
        ssd1306_DrawPixel(cursor_x + 5, cursor_y + row, false);
    }
    cursor_x += 6; // advance cursor (5px glyph + 1px space)
}

void ssd1306_WriteString(const char *s){
    while (*s){
        if (cursor_x + 6 >= SSD1306_WIDTH){
            // simple wrap to next line (8px line height)
            cursor_x = 0;
            cursor_y += 8;
            if (cursor_y + 7 >= SSD1306_HEIGHT) break; // stop if out of space
        }
        ssd1306_WriteChar(*s++);
    }
}