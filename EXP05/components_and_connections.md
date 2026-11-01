# EXP05 Components and connections

Analog sensor reading displayed on an I2C OLED. Use the circuit for the selected program; each part below lists its own components and pin connections.

[Experiment overview](README.md) | [Viva questions and answers](viva_questions_and_answers.md)

## Part A STM32 ADC and I2C OLED

Code: [code/STM32/main.c](code/STM32/main.c), [code/STM32/ssd1306.c](code/STM32/ssd1306.c), [code/STM32/ssd1306.h](code/STM32/ssd1306.h), [code/STM32/ssd1306_compat.c](code/STM32/ssd1306_compat.c), [code/STM32/ssd1306_compat.h](code/STM32/ssd1306_compat.h)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| STM32F446RE Nucleo board | 1 | CubeMX screenshot selects STM32F446RETx. |
| 128 by 64 SSD1306 I2C OLED | 1 | 4 pins: GND VCC SCL SDA; supplied user driver uses address 0x3C. |
| 10 kOhm three terminal potentiometer | 1 | Suggested value authorized by the user; the photographed resistance value is not known. |
| USB data cable | 1 |  |
| Jumper wires | 7 or more |  |
| I2C pull-up resistors | 2 if absent | Check module pull-ups; suitable pull-ups to 3.3 V are required. |

### Connections

| From | To | Notes |
| --- | --- | --- |
| STM32 3V3 | Potentiometer outer terminal 1 |  |
| STM32 GND | Potentiometer outer terminal 2 and OLED GND |  |
| Potentiometer wiper | STM32 PA0 ADC1_IN0 |  |
| STM32 3V3 | OLED VCC | Use a module compatible with 3.3 V power and logic. |
| STM32 PB8 I2C1_SCL | OLED SCL |  |
| STM32 PB9 I2C1_SDA | OLED SDA |  |
| ST-LINK USB | PC USB |  |

### Setup

1. Use STM32CubeIDE and the matching STM32 HAL package.
2. Keep generated project files; an extracted main.c alone is not a buildable firmware project.
3. Select STM32F446RE; ADC1 channel 0 on PA0; I2C1 100 kHz with PB8/PB9 alternate function 4, open drain.
4. Check the OLED I2C address and driver settings before building.
5. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.
6. Add main.c, ssd1306.c and ssd1306_compat.c to the HAL project; include both supplied headers. Build working copies, not the originals/ copies.
7. The lowercase user driver uses global hi2c1; the uppercase adapter accepts only &hi2c1.
8. The supplied driver embeds its font and uses the 0x3C OLED address shifted for HAL; no external font files are needed.

### Expected behavior

Every 200 ms, displays ADC count, approximate voltage, potentiometer percentage and a bar graph.

### Details to check

- The report theory describes a digital I2C sensor, but the actual input is an analog potentiometer; only the OLED uses I2C.
- User display driver is now included through an explicitly added compatibility adapter and percent glyph.
- The driver ignores HAL I2C transfer error returns and uses blocking HAL_MAX_DELAY transfers.
- Driver orientation and physical display operation need hardware verification; no full STM32 HAL project compilation or board test was performed.

## Part B ESP32 ADC and I2C OLED

Code: [code/ESP32/main.py](code/ESP32/main.py)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| Classic ESP32 development board | 1 |  |
| 128 by 64 SSD1306 I2C OLED | 1 | Source address 0x3C. |
| 10 kOhm three terminal potentiometer | 1 | Suggested value authorized by the user; the photographed resistance value is not known. |
| USB data cable | 1 |  |
| Jumper wires | 7 or more |  |
| I2C pull-up resistors | 2 if absent | Pull SDA/SCL to 3.3 V if module has none. |

### Connections

| From | To | Notes |
| --- | --- | --- |
| ESP32 3V3 | Potentiometer outer terminal 1 and OLED VCC | Use a 3.3 V compatible module. |
| ESP32 GND | Potentiometer outer terminal 2 and OLED GND |  |
| Potentiometer wiper | ESP32 GPIO34 |  |
| ESP32 GPIO22 | OLED SCL |  |
| ESP32 GPIO21 | OLED SDA |  |
| ESP32 USB | PC USB |  |

### Setup

1. Flash compatible MicroPython onto the classic ESP32 board and connect through Thonny.
2. Upload only this experiment main.py when selecting that experiment.
3. Copy the compatible ssd1306.py driver to the ESP32 filesystem.
4. The source uses SoftI2C at 100 kHz and OLED address 0x3C.
5. If blank, run an I2C scan and check supply, pin order, address and driver.
6. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

### Expected behavior

Once per second, displays ADC SENSOR, raw ADC count and approximate voltage.

### Details to check

- ssd1306.py is not included in the archive.
- The original raw/4095*3.3 formula is approximate even with ATTN_11DB.
- A digital I2C sensor is not implemented in this source.

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
