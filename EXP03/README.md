# EXP03 Timer and delay generation

## Aim

Generate periodic output transitions using STM32 TIM2 interrupts and an ESP32 MicroPython timer, then observe the waveforms on an oscilloscope.

## Files

- [Components and pin connections for both parts](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)
- [Code integration notes](code/README.md)

## Parts and status

| Part | Available code | Status |
| --- | --- | --- |
| Part A STM32 Embedded C | [main_report_excerpt.c](code/STM32/main_report_excerpt.c) | Report code excerpt is included. Complete project, timer clock and final PSC/ARR selection remain unresolved. |
| Part B ESP32 MicroPython | [timer_toggle.py](code/ESP32/timer_toggle.py) | Complete screenshot program is included; confirm Timer 2 support for the actual board and firmware. |

## Setup and expected behavior

### Part A STM32 Embedded C

1. Use STM32CubeIDE with the correct STM32F446RETx board project.
2. Configure TIM2 internal clock and update interrupt; generated TIM2 clock/MSP/NVIC and IRQ handler support must be present.
3. Configure PA5 GPIO output; source also initializes PC13 input though it is unused by the callback.
4. Resolve settings conflict: printed source has PSC 15 and ARR 1622, while the CubeMX screenshot has PSC 299 and ARR 373. Obtain final .ioc and actual TIM2 input clock.

Expected behavior: TIM2 starts in interrupt mode. Each timer update calls HAL_TIM_PeriodElapsedCallback, which toggles PA5. For an up-counter, f_update = f_TIM / ((PSC+1)(ARR+1)); the square-wave frequency is f_update/2.

### Part B ESP32 MicroPython

1. Run timer_toggle.py on the source-compatible ESP32 MicroPython firmware.
2. Timer(2) and a 748 Hz periodic callback are used in the screenshot. Confirm timer ID support if using another ESP32 variant.
3. Keep callbacks short; use timer.deinit() from the console to stop.

Expected behavior: The callback toggles GPIO2 748 times per second, giving an ideal 374 Hz square wave, about 2.674 ms period and approximately 50 percent duty cycle.

## Missing items and unresolved details

- Final STM32 .ioc and complete CubeIDE project including SystemClock_Config and timer IRQ/MSP support.
- Confirmation whether PSC15/ARR1622 or PSC299/ARR373 is the intended final configuration.
- Exact ESP32 board model and MicroPython firmware version.

## Changes from the supplied material

- STM32 report code preserved as an explicitly incomplete project excerpt.
- ESP32 screenshot transcribed with explanatory comments.
- Both conflicting STM32 configuration variants are recorded without selecting an unsupported final value.
- The timer lab is numbered EXP3 by its folder and content; its report incorrectly prints Experiment No. 02.

## Validation

The code files were copied byte for byte from the prepared study pack, including explanatory comments and separate original or corrected variants. These are individual application files and integration routines. No complete STM32 HAL project build or hardware operation is claimed.

## All files in this experiment

- [README.md](README.md)
- [code/ESP32/timer_toggle.py](code/ESP32/timer_toggle.py)
- [code/README.md](code/README.md)
- [code/STM32/main_report_excerpt.c](code/STM32/main_report_excerpt.c)
- [components_and_connections.md](components_and_connections.md)
- [viva_questions_and_answers.md](viva_questions_and_answers.md)

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP3/EXP3_2024300174.docx`
- `IOT/EXP3/EXP3_2024300174.pdf`
- `IOT/EXP3_2024300174.docx`
- `IOT/EXP3/Screenshot 2026-08-17 181449.png`
- `IOT/EXP3/Screenshot 2026-08-24 115112.png`

Technical references:

- [ST UM1724 STM32 Nucleo 64 board manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf)
- [MicroPython Pin](https://docs.micropython.org/en/latest/library/machine.Pin.html)
- [MicroPython Timer](https://docs.micropython.org/en/latest/library/machine.Timer.html)
- [MicroPython UART](https://docs.micropython.org/en/latest/library/machine.UART.html)
