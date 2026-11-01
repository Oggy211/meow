# EXP03 Components and connections

Timer and delay generation. Use the circuit for the selected program; each part below lists its own components and pin connections.

[Experiment overview](README.md) | [Viva questions and answers](viva_questions_and_answers.md)

## Part A STM32 Embedded C

Code: [code/STM32/main_report_excerpt.c](code/STM32/main_report_excerpt.c)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| STM32 development board targeting STM32F446RETx | 1 |  |
| USB data cable | 1 |  |
| Digital storage oscilloscope | 1 |  |
| Oscilloscope probe and ground lead | 1 |  |
| Jumper wires | As needed |  |
| Onboard LED on PA5 | 1 | Output can be observed electrically even when toggling too fast to see. |

### Connections

| From | To | Notes |
| --- | --- | --- |
| STM32 PA5 | Oscilloscope probe tip | PA5 output toggled by TIM2 callback. |
| STM32 GND | Oscilloscope probe ground clip |  |
| STM32 ST-LINK USB connector | Computer USB |  |
| PA5 | Onboard LD2 LED | Board path; external LED is optional and would require a series resistor. |

### Setup

1. Use STM32CubeIDE with the correct STM32F446RETx board project.
2. Configure TIM2 internal clock and update interrupt; generated TIM2 clock/MSP/NVIC and IRQ handler support must be present.
3. Configure PA5 GPIO output; source also initializes PC13 input though it is unused by the callback.
4. Resolve settings conflict: printed source has PSC 15 and ARR 1622, while the CubeMX screenshot has PSC 299 and ARR 373. Obtain final .ioc and actual TIM2 input clock.

### Expected behavior

TIM2 starts in interrupt mode. Each timer update calls HAL_TIM_PeriodElapsedCallback, which toggles PA5. For an up-counter, f_update = f_TIM / ((PSC+1)(ARR+1)); the square-wave frequency is f_update/2.

### Details to check

- The final timer input clock is not supplied, so no reliable exact STM32 output frequency can be derived.
- The report observed about 376.93 Hz; that observation is not proof that the printed constants and screenshot settings describe the same run.
- The report excerpt omits SystemClock_Config and generated timer interrupt support, so it cannot link and run by itself.

## Part B ESP32 MicroPython

Code: [code/ESP32/timer_toggle.py](code/ESP32/timer_toggle.py)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| ESP32 development board | 1 |  |
| USB data cable | 1 |  |
| Digital storage oscilloscope | 1 |  |
| Oscilloscope probe and ground lead | 1 |  |
| Jumper wires | As needed |  |
| Onboard GPIO2 LED | 1 | Board-dependent; waveform measurement uses GPIO2 directly. |

### Connections

| From | To | Notes |
| --- | --- | --- |
| ESP32 GPIO2 | Oscilloscope probe tip |  |
| ESP32 GND | Oscilloscope probe ground clip |  |
| ESP32 USB connector | Computer USB |  |

### Setup

1. Run timer_toggle.py on the source-compatible ESP32 MicroPython firmware.
2. Timer(2) and a 748 Hz periodic callback are used in the screenshot. Confirm timer ID support if using another ESP32 variant.
3. Keep callbacks short; use timer.deinit() from the console to stop.

### Expected behavior

The callback toggles GPIO2 748 times per second, giving an ideal 374 Hz square wave, about 2.674 ms period and approximately 50 percent duty cycle.

### Details to check

- MicroPython callback scheduling and firmware/board differences can add timing jitter.
- The 748 Hz timer event rate is twice the output square-wave frequency.

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
