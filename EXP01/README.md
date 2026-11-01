# EXP01 GPIO input and output

## Aim

Configure digital outputs and inputs on STM32 using Embedded C and ESP32 using MicroPython, then demonstrate LED blinking and push-button control.

## Files

- [Components and pin connections for both parts](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)
- [Code integration notes](code/README.md)

## Parts and status

| Part | Available code | Status |
| --- | --- | --- |
| Part A STM32 Embedded C | [gpio_blink_user_code.c](code/STM32/gpio_blink_user_code.c), [button_as_recovered.c](code/STM32/button_as_recovered.c), [button_corrected_follow_input.c](code/STM32/button_corrected_follow_input.c) | Recovered integration routines; original and corrected button variants are separate. Complete CubeIDE project is still required. |
| Part B ESP32 MicroPython | [led_blink.py](code/ESP32/led_blink.py), [button_led.py](code/ESP32/button_led.py) | Recovered MicroPython programs are included; resistor values and exact board remain to be confirmed. |

## Setup and expected behavior

### Part A STM32 Embedded C

1. Use STM32CubeIDE and the correct board project; target MCU in screenshots is STM32F446RETx.
2. Configure PA5 and PC9 as GPIO push-pull outputs for blink; configure PC13 input and PC8 output for button.
3. Original complete Cube project, .ioc and clock initialization are absent. Use the selected integration routine after generated initialization.

Expected behavior: Blink source sequences PA5 high for 1 s, low for 1 s, then PC9 high for 1 s and low for 1 s; each pin repeats every 4 s. The source button routine latches PC8 high after the first high PC13 reading. The separate corrected routine makes PC8 follow PC13.

### Part B ESP32 MicroPython

1. Install compatible MicroPython firmware and use a MicroPython IDE such as Thonny.
2. Run led_blink.py or button_led.py separately. Save the selected program as main.py if automatic start is required.

Expected behavior: Blink: GPIO16 on for 1 s and off for 1 s, with matching console messages. Button: GPIO4 high turns GPIO16 on; low turns it off; status is printed every 100 ms.

## Missing items and unresolved details

- Original STM32 CubeIDE project and .ioc with complete initialization.
- LED series resistor values and ESP32 pull-down resistor value.
- Exact ESP32 board model and STM32 board revision.

## Changes from the supplied material

- Short comments added to transcribed code; code logic preserved in files marked as recovered.
- STM32 screenshot loop bodies were placed inside named integration functions, with generated initialization explicitly required.
- A separate corrected button file reads the current input each loop; original latching version is retained.

## Validation

The code files were copied byte for byte from the prepared study pack, including explanatory comments and separate original or corrected variants. These are individual application files and integration routines. No complete STM32 HAL project build or hardware operation is claimed.

## All files in this experiment

- [README.md](README.md)
- [code/ESP32/button_led.py](code/ESP32/button_led.py)
- [code/ESP32/led_blink.py](code/ESP32/led_blink.py)
- [code/README.md](code/README.md)
- [code/STM32/button_as_recovered.c](code/STM32/button_as_recovered.c)
- [code/STM32/button_corrected_follow_input.c](code/STM32/button_corrected_follow_input.c)
- [code/STM32/gpio_blink_user_code.c](code/STM32/gpio_blink_user_code.c)
- [components_and_connections.md](components_and_connections.md)
- [viva_questions_and_answers.md](viva_questions_and_answers.md)

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
