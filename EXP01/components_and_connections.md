# EXP01 Components and connections

GPIO input and output. Use the circuit for the selected program; each part below lists its own components and pin connections.

[Experiment overview](README.md) | [Viva questions and answers](viva_questions_and_answers.md)

## Part A STM32 Embedded C

Code: [code/STM32/gpio_blink_user_code.c](code/STM32/gpio_blink_user_code.c), [code/STM32/button_as_recovered.c](code/STM32/button_as_recovered.c), [code/STM32/button_corrected_follow_input.c](code/STM32/button_corrected_follow_input.c)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| STM32 development board targeting STM32F446RETx | 1 | Target confirmed by screenshots; exact board revision not stated. |
| USB data cable | 1 |  |
| External LED | 1 | Rewire from PC9 for blink to PC8 for button experiment. |
| LED current-limiting resistor | 1 | Value not recorded; confirm before wiring. |
| Breadboard and jumper wires | As needed |  |
| Onboard B1 push button | 1 | PC13 input shown in configuration screenshot. |

### Connections

| From | To | Notes |
| --- | --- | --- |
| PA5 | Onboard LD2 LED | Nucleo-style onboard LED path; code drives PA5. |
| PC9 | Series resistor then external LED anode | Blink version; resistor value needs confirmation. |
| External LED cathode | Board GND |  |
| PC8 | Series resistor then external LED anode | Button version replaces the PC9 connection. |
| PC13 | B1 user button | Board input circuitry; confirm actual board model/revision. |
| Board ST-LINK USB connector | Computer USB | Programming and power as photographed. |

### Setup

1. Use STM32CubeIDE and the correct board project; target MCU in screenshots is STM32F446RETx.
2. Configure PA5 and PC9 as GPIO push-pull outputs for blink; configure PC13 input and PC8 output for button.
3. Original complete Cube project, .ioc and clock initialization are absent. Use the selected integration routine after generated initialization.

### Expected behavior

Blink source sequences PA5 high for 1 s, low for 1 s, then PC9 high for 1 s and low for 1 s; each pin repeats every 4 s. The source button routine latches PC8 high after the first high PC13 reading. The separate corrected routine makes PC8 follow PC13.

### Details to check

- Do not describe the source button code as turning off on release; val is never reset.
- Exact LED resistor value is absent.
- A full standalone Cube firmware build cannot be supplied from the screenshots alone.

## Part B ESP32 MicroPython

Code: [code/ESP32/led_blink.py](code/ESP32/led_blink.py), [code/ESP32/button_led.py](code/ESP32/button_led.py)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| ESP32 development board | 1 |  |
| USB data cable | 1 |  |
| LED | 1 |  |
| LED current-limiting resistor | 1 | Value not stated. |
| Push button | 1 |  |
| External pull-down resistor | 1 | Value not stated; required by source active-high button circuit because no internal pull is selected. |
| Breadboard and jumper wires | As needed |  |

### Connections

| From | To | Notes |
| --- | --- | --- |
| GPIO16 | Series resistor then LED anode |  |
| LED cathode | ESP32 GND |  |
| GPIO4 | One side of push button |  |
| Other side of push button | ESP32 3.3 V | Active-high circuit matching source logic. |
| GPIO4 | Pull-down resistor then GND | Bias input low while released; confirm resistor value. |
| ESP32 USB connector | Computer USB |  |

### Setup

1. Install compatible MicroPython firmware and use a MicroPython IDE such as Thonny.
2. Run led_blink.py or button_led.py separately. Save the selected program as main.py if automatic start is required.

### Expected behavior

Blink: GPIO16 on for 1 s and off for 1 s, with matching console messages. Button: GPIO4 high turns GPIO16 on; low turns it off; status is printed every 100 ms.

### Details to check

- Pin(4, Pin.IN) does not explicitly enable an internal pull; do not leave the input floating.
- The source does not provide proper switch debouncing.
- GPIO16 availability and onboard LED pins vary by exact ESP32 board; this experiment uses an external GPIO16 LED.

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP1/EXP1_2024300174_A.docx`
- `IOT/EXP1/EXP1_2024300174_A.pdf`
- `IOT/EXP1/Screenshot 2026-07-27 121355.png`
- `IOT/EXP1/Screenshot 2026-07-27 125313.png`
- `IOT/EXP1/Screenshot 2026-08-03 165507.png`
- `IOT/EXP1/Screenshot 2026-08-03 172709.png`

Technical references:

- [ST UM1724 STM32 Nucleo 64 board manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf)
- [MicroPython Pin](https://docs.micropython.org/en/latest/library/machine.Pin.html)
- [MicroPython Timer](https://docs.micropython.org/en/latest/library/machine.Timer.html)
- [MicroPython UART](https://docs.micropython.org/en/latest/library/machine.UART.html)
