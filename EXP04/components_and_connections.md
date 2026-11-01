# EXP04 Components and connections

Analog input acquisition using ADC. Use the circuit for the selected program; each part below lists its own components and pin connections.

[Experiment overview](README.md) | [Viva questions and answers](viva_questions_and_answers.md)

## Part A STM32 ADC to UART

Code: [code/STM32/main.c](code/STM32/main.c)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| STM32 Nucleo development board | 1 | F4 HAL code; confirm exact board project before building. |
| 10 kOhm three terminal potentiometer | 1 | Suggested value authorized by the user; the photographed resistance value is not known. |
| USB data cable | 1 |  |
| Jumper wires | 3 or more |  |
| PC with serial terminal | 1 |  |

### Connections

| From | To | Notes |
| --- | --- | --- |
| STM32 3V3 | Potentiometer outer terminal 1 |  |
| STM32 GND | Potentiometer outer terminal 2 |  |
| Potentiometer centre wiper | STM32 PA0 ADC1_IN0 | Channel 0 in code; confirm pin against selected MCU. |
| STM32 ST-LINK USB | PC USB | USART2 virtual COM depends on the board routing and solder bridges. |

### Setup

1. Use STM32CubeIDE and the matching STM32 HAL package.
2. Keep generated project files; an extracted main.c alone is not a buildable firmware project.
3. Configure ADC1 channel 0 as 12 bit; configure USART2 at 115200 baud 8N1.
4. Ensure generated HAL MSP code enables ADC1 clock, PA0 analog mode, and USART2 clock and GPIO alternate functions.
5. The recovered clock code is device specific; regenerate configuration for the actual STM32 board.
6. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

### Expected behavior

Every 500 ms, prints ADC count and calculated millivolts; rotating the potentiometer changes the reading.

### Details to check

- The report names LM35/LDR in its generic aim, but the implementation and photos use a potentiometer.
- The original CubeIDE project, main.h and MSP files are absent.
- The 3.3 V conversion is approximate and depends on actual reference voltage.

## Part B ESP32 ADC to serial output

Code: [code/ESP32/main.py](code/ESP32/main.py)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| Classic ESP32 development board | 1 |  |
| 10 kOhm three terminal potentiometer | 1 | Suggested value authorized by the user; the photographed resistance value is not known. |
| USB data cable | 1 |  |
| Jumper wires | 3 |  |
| PC running Thonny | 1 |  |

### Connections

| From | To | Notes |
| --- | --- | --- |
| ESP32 3V3 | Potentiometer outer terminal 1 |  |
| ESP32 GND | Potentiometer outer terminal 2 |  |
| Potentiometer centre wiper | ESP32 GPIO34 |  |
| ESP32 USB | PC USB |  |

### Setup

1. Flash compatible MicroPython onto the classic ESP32 board and connect through Thonny.
2. Upload only this experiment main.py when selecting that experiment.
3. The source uses ADC.read(), returning 0 to 4095 on the original ESP32 configuration.
4. The recovered source does not set ADC attenuation. For reliable voltage measurement, configure attenuation for the input range and use calibration/read_uv() where supported.
5. Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

### Expected behavior

Prints raw ADC count and a calculated voltage once per second.

### Details to check

- The source formula raw/4095*3.3 is preserved for the lab record; it does not establish a calibrated ESP32 0 to 3.3 V ADC range.
- A 3.3 V potentiometer supply keeps the wiper within the board supply, but the ADC can saturate before the top of that range.

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP4/4th.docx`
- `IOT/EXP4/EXP4_2024300174_A.pdf`
- `IOT/EXP4/Screenshot 2026-08-24 122630.png`
- `IOT/EXP4/IMG20260824175952.jpg`
- `IOT/EXP4/IMG_20261005_001156.jpg`

Technical references:

- [MicroPython ESP32 ADC reference](https://www.micropython.org/resources/docs/en/latest/esp32/quickref.html)
