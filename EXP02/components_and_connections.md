# EXP02 Components and connections

UART serial communication. Use the circuit for the selected program; each part below lists its own components and pin connections.

[Experiment overview](README.md) | [Viva questions and answers](viva_questions_and_answers.md)

## Part A STM32 Embedded C

Code: [code/STM32/uart_led_user_code.c](code/STM32/uart_led_user_code.c)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| STM32 development board targeting STM32F446RETx | 1 | Target MCU visible in screenshot; board includes ST-LINK USB connection. |
| USB data cable | 1 |  |
| Computer with Tera Term | 1 |  |
| Onboard LED | 1 | PA5 green LD2 shown in pinout. |

### Connections

| From | To | Notes |
| --- | --- | --- |
| Board ST-LINK USB connector | Computer USB | Photographed connection for programming and Virtual COM port. |
| USART2 TX PA2 | ST-LINK Virtual COM receive path | Board routing and solder bridges must match the board revision. |
| USART2 RX PA3 | ST-LINK Virtual COM transmit path | Already onboard on the source Nucleo-style arrangement. |
| PA5 | Onboard LD2 LED | No external LED wiring shown. |

### Setup

1. Configure USART2 asynchronous, 115200 baud, 8 data bits, no parity, 1 stop bit, no hardware flow control.
2. Select the board Virtual COM port in Tera Term using the same settings.
3. The user supplied the application in chat on 1 November 2026. Use the annotated integration routine after HAL, clock, GPIO and USART2 initialization in the board project.

### Expected behavior

The application sends a prompt, waits for one received character, echoes it, sets PA5 high for ASCII 1 or low for ASCII 0, and prints the corresponding LED status.

### Details to check

- Complete original generated CubeIDE project and .ioc are absent; the supplied application is an integration routine.
- HAL_MAX_DELAY makes reception blocking; this example handles manual terminal commands.
- Do not add an external adapter to the same UART without checking onboard ST-LINK routing.

## Part B ESP32 MicroPython

Code: [code/ESP32/uart_led.py](code/ESP32/uart_led.py)

### Components

| Component | Quantity | Notes |
| --- | --- | --- |
| ESP32 development board | 1 |  |
| USB data cable for ESP32 | 1 |  |
| USB-to-TTL UART adapter | 1 | Model not stated; verify 3.3 V signal levels. |
| USB cable for adapter | 1 if required |  |
| Jumper wires | 3 |  |
| Computer with serial terminal | 1 |  |
| Onboard LED on GPIO2 | 1 | Present on the photographed board; board-dependent. |

### Connections

| From | To | Notes |
| --- | --- | --- |
| USB-TTL adapter TX | ESP32 GPIO16 RX |  |
| USB-TTL adapter RX | ESP32 GPIO17 TX |  |
| USB-TTL adapter GND | ESP32 GND |  |
| ESP32 USB connector | Computer USB | Power and MicroPython console. |
| USB-TTL adapter USB | Computer USB | Tera Term opens this adapter COM port at 9600 baud. |
| GPIO2 | Onboard LED | No external LED circuit shown. |

### Setup

1. Run uart_led.py using MicroPython.
2. Configure the terminal connected to the external adapter for 9600 baud, 8N1, no flow control.
3. Send ASCII 1 or 0; optional CR/LF bytes are ignored by the two-command program.

### Expected behavior

UART2 receives b'1' to turn the GPIO2 LED on and b'0' to turn it off; replies go to UART2 and status is also printed on the MicroPython console.

### Details to check

- USB console output from print is separate from uart.write on GPIO17.
- Do not use an RS-232 voltage interface directly on ESP32 GPIO.
- The source sleeps 100 ms each iteration and reads one byte, so it is intended for slow manual commands.

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
