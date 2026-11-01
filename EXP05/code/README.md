# Experiment 5 Analog sensor reading displayed on an I2C OLED

## Available code

Part A STM32 ADC and I2C OLED

- [STM32/main.c](STM32/main.c)
- [STM32/ssd1306.c](STM32/ssd1306.c)
- [STM32/ssd1306.h](STM32/ssd1306.h)
- [STM32/ssd1306_compat.c](STM32/ssd1306_compat.c)
- [STM32/ssd1306_compat.h](STM32/ssd1306_compat.h)

Use STM32CubeIDE and the matching STM32 HAL package.
Keep generated project files; an extracted main.c alone is not a buildable firmware project.
Select STM32F446RE; ADC1 channel 0 on PA0; I2C1 100 kHz with PB8/PB9 alternate function 4, open drain.
Check the OLED I2C address and driver settings before building.
Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.
Add main.c, ssd1306.c and ssd1306_compat.c to the HAL project; include both supplied headers. Build working copies, not the originals/ copies.
The lowercase user driver uses global hi2c1; the uppercase adapter accepts only &hi2c1.
The supplied driver embeds its font and uses the 0x3C OLED address shifted for HAL; no external font files are needed.

The report theory describes a digital I2C sensor, but the actual input is an analog potentiometer; only the OLED uses I2C.
User display driver is now included through an explicitly added compatibility adapter and percent glyph.
The driver ignores HAL I2C transfer error returns and uses blocking HAL_MAX_DELAY transfers.
Driver orientation and physical display operation need hardware verification; no full STM32 HAL project compilation or board test was performed.

Part B ESP32 ADC and I2C OLED

- [ESP32/main.py](ESP32/main.py)

Flash compatible MicroPython onto the classic ESP32 board and connect through Thonny.
Upload only this experiment main.py when selecting that experiment.
Copy the compatible ssd1306.py driver to the ESP32 filesystem.
The source uses SoftI2C at 100 kHz and OLED address 0x3C.
If blank, run an I2C scan and check supply, pin order, address and driver.
Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

ssd1306.py is not included in the archive.
The original raw/4095*3.3 formula is approximate even with ATTN_11DB.
A digital I2C sensor is not implemented in this source.

## Missing information
- ESP32 ssd1306.py driver.
