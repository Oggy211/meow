# EXP05 Analog sensor reading displayed on an I2C OLED

## Aim

Measure a potentiometer with the STM32 and ESP32 ADCs and display the reading on an SSD1306 OLED through I2C.

## Files

- [Components and pin connections for both parts](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)
- [Code integration notes](code/README.md)

## Parts and status

| Part | Available code | Status |
| --- | --- | --- |
| Part A STM32 ADC and I2C OLED | [main.c](code/STM32/main.c), [ssd1306.c](code/STM32/ssd1306.c), [ssd1306.h](code/STM32/ssd1306.h), [ssd1306_compat.c](code/STM32/ssd1306_compat.c), [ssd1306_compat.h](code/STM32/ssd1306_compat.h) | Application, user driver, compatibility adapter and original driver copies are included. Complete CubeIDE project is still required. |
| Part B ESP32 ADC and I2C OLED | [main.py](code/ESP32/main.py) | Application is included. The external ssd1306.py driver must still be supplied or installed. |

## Setup and expected behavior

### Part A STM32 ADC and I2C OLED

1. Use STM32CubeIDE and the matching STM32 HAL package.
2. Keep generated project files; an extracted main.c alone is not a buildable firmware project.
3. Select STM32F446RE; ADC1 channel 0 on PA0; I2C1 100 kHz with PB8/PB9 alternate function 4, open drain.
4. Check the OLED I2C address and driver settings before building.
5. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.
6. Add main.c, ssd1306.c and ssd1306_compat.c to the HAL project; include both supplied headers. Build working copies, not the originals/ copies.
7. The lowercase user driver uses global hi2c1; the uppercase adapter accepts only &hi2c1.
8. The supplied driver embeds its font and uses the 0x3C OLED address shifted for HAL; no external font files are needed.

Expected behavior: Every 200 ms, displays ADC count, approximate voltage, potentiometer percentage and a bar graph.

### Part B ESP32 ADC and I2C OLED

1. Flash compatible MicroPython onto the classic ESP32 board and connect through Thonny.
2. Upload only this experiment main.py when selecting that experiment.
3. Copy the compatible ssd1306.py driver to the ESP32 filesystem.
4. The source uses SoftI2C at 100 kHz and OLED address 0x3C.
5. If blank, run an I2C scan and check supply, pin order, address and driver.
6. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

Expected behavior: Once per second, displays ADC SENSOR, raw ADC count and approximate voltage.

## Missing items and unresolved details

- ESP32 ssd1306.py driver.

## Changes from the supplied material

- Separated the report MicroPython and C programs into two files.
- Preserved source behavior and short comments.
- Specified a suggested 10 kOhm potentiometer with user authorization; this is not a recovered component marking.
- Integrated user-supplied lowercase SSD1306 driver and preserved original .c/.h in STM32/originals/.
- Added ssd1306_compat.h/.c to map report uppercase calls to user lowercase API, with coordinate clipping and a percentage bar.
- Added the missing percent glyph to the working embedded font; main.c now includes the compatibility header.
- Cast percentage to unsigned int to match the %u formatting argument.

## Validation

The code files were copied byte for byte from the prepared study pack, including explanatory comments and separate original or corrected variants. These are individual application files and integration routines. No complete STM32 HAL project build or hardware operation is claimed.

## All files in this experiment

- [README.md](README.md)
- [code/ESP32/MISSING_DEPENDENCIES.md](code/ESP32/MISSING_DEPENDENCIES.md)
- [code/ESP32/main.py](code/ESP32/main.py)
- [code/README.md](code/README.md)
- [code/STM32/PROJECT_SETUP.md](code/STM32/PROJECT_SETUP.md)
- [code/STM32/main.c](code/STM32/main.c)
- [code/STM32/originals/ssd1306.c](code/STM32/originals/ssd1306.c)
- [code/STM32/originals/ssd1306.h](code/STM32/originals/ssd1306.h)
- [code/STM32/ssd1306.c](code/STM32/ssd1306.c)
- [code/STM32/ssd1306.h](code/STM32/ssd1306.h)
- [code/STM32/ssd1306_compat.c](code/STM32/ssd1306_compat.c)
- [code/STM32/ssd1306_compat.h](code/STM32/ssd1306_compat.h)
- [components_and_connections.md](components_and_connections.md)
- [viva_questions_and_answers.md](viva_questions_and_answers.md)

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP5/EXP5_2024300174_A.docx`
- `IOT/EXP5/IMG20260923165847.jpg`
- `IOT/EXP5/IMG20260923165900.jpg`
- `IOT/EXP5/IMG20261013164808.jpg`
- `IOT/EXP5/IMG20261013164823.jpg`
- User-supplied STM32 ssd1306.c attachment and ssd1306.h chat text on 1 November 2026

Technical references:

- [MicroPython ESP32 ADC reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
- [Official MicroPython SSD1306 driver](https://github.com/micropython/micropython-lib/tree/master/micropython/drivers/display/ssd1306)
