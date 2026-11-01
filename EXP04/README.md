# EXP04 Analog input acquisition using ADC

## Aim

Measure the variable voltage from a potentiometer with STM32 and ESP32 ADCs and display the readings through a serial terminal.

## Files

- [Components and pin connections for both parts](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)
- [Code integration notes](code/README.md)

## Parts and status

| Part | Available code | Status |
| --- | --- | --- |
| Part A STM32 ADC to UART | [main.c](code/STM32/main.c) | Recovered main.c is included. Generated CubeIDE support files are still required. |
| Part B ESP32 ADC to serial output | [main.py](code/ESP32/main.py) | Recovered MicroPython program is included. ADC attenuation and calibration limitations are documented. |

## Setup and expected behavior

### Part A STM32 ADC to UART

1. Use STM32CubeIDE and the matching STM32 HAL package.
2. Keep generated project files; an extracted main.c alone is not a buildable firmware project.
3. Configure ADC1 channel 0 as 12 bit; configure USART2 at 115200 baud 8N1.
4. Ensure generated HAL MSP code enables ADC1 clock, PA0 analog mode, and USART2 clock and GPIO alternate functions.
5. The recovered clock code is device specific; regenerate configuration for the actual STM32 board.
6. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

Expected behavior: Every 500 ms, prints ADC count and calculated millivolts; rotating the potentiometer changes the reading.

### Part B ESP32 ADC to serial output

1. Flash compatible MicroPython onto the classic ESP32 board and connect through Thonny.
2. Upload only this experiment main.py when selecting that experiment.
3. The source uses ADC.read(), returning 0 to 4095 on the original ESP32 configuration.
4. The recovered source does not set ADC attenuation. For reliable voltage measurement, configure attenuation for the input range and use calibration/read_uv() where supported.
5. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

Expected behavior: Prints raw ADC count and a calculated voltage once per second.

## Missing items and unresolved details

- Original STM32 CubeIDE project and generated supporting files.

## Changes from the supplied material

- Recovered ESP32 main.py by transcribing the complete screenshot.
- Added short comments to recovered code; preserved ADC configuration and lab voltage formulas.
- Specified a suggested 10 kOhm potentiometer with user authorization; this is not a recovered component marking.

## Validation

The code files were copied byte for byte from the prepared study pack, including explanatory comments and separate original or corrected variants. These are individual application files and integration routines. No complete STM32 HAL project build or hardware operation is claimed.

## All files in this experiment

- [README.md](README.md)
- [code/ESP32/main.py](code/ESP32/main.py)
- [code/README.md](code/README.md)
- [code/STM32/main.c](code/STM32/main.c)
- [components_and_connections.md](components_and_connections.md)
- [viva_questions_and_answers.md](viva_questions_and_answers.md)

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP4/4th.docx`
- `IOT/EXP4/EXP4_2024300174_A.pdf`
- `IOT/EXP4/Screenshot 2026-08-24 122630.png`
- `IOT/EXP4/IMG20260824175952.jpg`
- `IOT/EXP4/IMG_20261005_001156.jpg`

Technical references:

- [MicroPython ESP32 ADC reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
