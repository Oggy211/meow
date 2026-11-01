# Required display driver

Copy a compatible MicroPython ssd1306.py to the ESP32 alongside main.py. The archive does not contain this file.

The application imports SSD1306_I2C and creates a 128 by 64 display at address 0x3C. The official MicroPython SSD1306 driver is maintained in the micropython-lib repository.

Official source: [MicroPython SSD1306 driver](https://github.com/micropython/micropython-lib/tree/master/micropython/drivers/display/ssd1306)