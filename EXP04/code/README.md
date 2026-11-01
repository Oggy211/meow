# Experiment 4 Analog input acquisition using ADC

## Available code

Part A STM32 ADC to UART

- [STM32/main.c](STM32/main.c)

Use STM32CubeIDE and the matching STM32 HAL package.
Keep generated project files; an extracted main.c alone is not a buildable firmware project.
Configure ADC1 channel 0 as 12 bit; configure USART2 at 115200 baud 8N1.
Ensure generated HAL MSP code enables ADC1 clock, PA0 analog mode, and USART2 clock and GPIO alternate functions.
The recovered clock code is device specific; regenerate configuration for the actual STM32 board.
Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

The report names LM35/LDR in its generic aim, but the implementation and photos use a potentiometer.
The original CubeIDE project, main.h and MSP files are absent.
The 3.3 V conversion is approximate and depends on actual reference voltage.

Part B ESP32 ADC to serial output

- [ESP32/main.py](ESP32/main.py)

Flash compatible MicroPython onto the classic ESP32 board and connect through Thonny.
Upload only this experiment main.py when selecting that experiment.
The source uses ADC.read(), returning 0 to 4095 on the original ESP32 configuration.
The recovered source does not set ADC attenuation. For reliable voltage measurement, configure attenuation for the input range and use calibration/read_uv() where supported.
Use a 10 kOhm potentiometer as the suggested value; its outer terminals go to 3V3 and GND and the centre wiper goes to the documented ADC pin.

The source formula raw/4095*3.3 is preserved for the lab record; it does not establish a calibrated ESP32 0 to 3.3 V ADC range.
A 3.3 V potentiometer supply keeps the wiper within the board supply, but the ADC can saturate before the top of that range.

## Missing information
- Original STM32 CubeIDE project and generated supporting files.
