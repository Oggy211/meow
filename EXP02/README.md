# EXP02 UART serial communication

## Aim

Use UART communication on STM32 and ESP32 to receive serial-terminal commands that turn an LED on and off.

## Files

- [Components and pin connections for both parts](components_and_connections.md)
- [Viva questions and answers](viva_questions_and_answers.md)
- [Code integration notes](code/README.md)

## Parts and status

| Part | Available code | Status |
| --- | --- | --- |
| Part A STM32 Embedded C | [uart_led_user_code.c](code/STM32/uart_led_user_code.c) | User-supplied UART application is included as an integration routine. Complete CubeIDE project is still required. |
| Part B ESP32 MicroPython | [uart_led.py](code/ESP32/uart_led.py) | Recovered MicroPython program is included; confirm the external adapter voltage and board. |

## Setup and expected behavior

### Part A STM32 Embedded C

1. Configure USART2 asynchronous, 115200 baud, 8 data bits, no parity, 1 stop bit, no hardware flow control.
2. Select the board Virtual COM port in Tera Term using the same settings.
3. The user supplied the application in chat on 1 November 2026. Use the annotated integration routine after HAL, clock, GPIO and USART2 initialization in the board project.

Expected behavior: The application sends a prompt, waits for one received character, echoes it, sets PA5 high for ASCII 1 or low for ASCII 0, and prints the corresponding LED status.

### Part B ESP32 MicroPython

1. Run uart_led.py using MicroPython.
2. Configure the terminal connected to the external adapter for 9600 baud, 8N1, no flow control.
3. Send ASCII 1 or 0; optional CR/LF bytes are ignored by the two-command program.

Expected behavior: UART2 receives b'1' to turn the GPIO2 LED on and b'0' to turn it off; replies go to UART2 and status is also printed on the MicroPython console.

## Missing items and unresolved details

- Complete original STM32 CubeIDE project and .ioc with generated initialization.
- USB-to-TTL adapter model and verified logic voltage.
- Exact ESP32 board model.

## Changes from the supplied material

- ESP32 screenshot code transcribed with short comments; original behavior retained.
- STM32 application supplied by the user in chat on 1 November 2026, annotated and wrapped in a named integration function without changing command behavior.

## Validation

The code files were copied byte for byte from the prepared study pack, including explanatory comments and separate original or corrected variants. These are individual application files and integration routines. No complete STM32 HAL project build or hardware operation is claimed.

## All files in this experiment

- [README.md](README.md)
- [code/ESP32/uart_led.py](code/ESP32/uart_led.py)
- [code/README.md](code/README.md)
- [code/STM32/uart_led_user_code.c](code/STM32/uart_led_user_code.c)
- [components_and_connections.md](components_and_connections.md)
- [viva_questions_and_answers.md](viva_questions_and_answers.md)

## Sources

Archive paths below identify the evidence in the supplied ZIP; the original reports and media are not copied into this code folder.

- `IOT/EXP2/2nd.docx`
- `IOT/EXP2/EXP2_2024300174_A.pdf.pdf`
- `IOT/EXP2/Screenshot 2026-08-10 163222.png`
- `IOT/EXP2/Screenshot 2026-08-10 170919.png`
- `IOT/EXP2/Screenshot 2026-08-17 164103.png`
- User-supplied chat code for Experiment 2 (1 November 2026)

Technical references:

- [ST UM1724 STM32 Nucleo 64 board manual](https://www.st.com/resource/en/user_manual/dm00105823.pdf)
- [MicroPython Pin](https://docs.micropython.org/en/latest/library/machine.Pin.html)
- [MicroPython Timer](https://docs.micropython.org/en/latest/library/machine.Timer.html)
- [MicroPython UART](https://docs.micropython.org/en/latest/library/machine.UART.html)
