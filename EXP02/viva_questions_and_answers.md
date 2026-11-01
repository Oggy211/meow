# EXP02 Viva questions and answers

UART serial communication. Questions cover the documented STM32 and ESP32 implementations.

[Experiment overview](README.md) | [Components and connections](components_and_connections.md)

## 1 What does UART stand for?

Universal Asynchronous Receiver/Transmitter.

## 2 Why is UART asynchronous?

The devices do not share a separate clock line; agreed timing and start/stop bits frame each character.

## 3 Why cross TX and RX?

The output of one device must reach the input of the other.

## 4 Why connect ground?

The devices need a shared voltage reference for interpreting logic levels.

## 5 What does 8N1 mean?

Eight data bits, no parity bit and one stop bit.

## 6 What is a baud rate?

It is the rate of signalling symbols; for ordinary binary UART, each symbol carries one bit.

## 7 What settings are used for STM32 here?

USART2, 115200 baud, 8N1 and no hardware flow control.

## 8 What settings are used for ESP32 here?

UART2, 9600 baud, TX GPIO17 and RX GPIO16; LED GPIO2.

## 9 Why compare with b'1' rather than integer 1?

uart.read returns bytes; the ASCII character 1 is a byte sequence, not the number one.

## 10 What does uart.any() check?

Whether received characters are available to read.

## 11 What does uart.read(1) do?

It requests one received byte rather than a whole line.

## 12 Where does print appear?

On the MicroPython console; uart.write sends data through the configured UART2 pins.

## 13 What happens if baud rates differ?

Sampling is mistimed, causing corrupt characters or framing errors.

## 14 Why is the ESP32 USB-to-TTL adapter separate from its USB cable?

The experiment uses UART2 on GPIO16 and GPIO17; the board USB console normally uses a different interface.

## 15 How long is an ideal 8N1 character at 9600 baud?

One start bit, eight data bits and one stop bit take 10/9600 s, approximately 1.04 ms.

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
