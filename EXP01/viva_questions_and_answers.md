# EXP01 Viva questions and answers

GPIO input and output. Questions cover the documented STM32 and ESP32 implementations.

[Experiment overview](README.md) | [Components and connections](components_and_connections.md)

## 1 What is GPIO?

A programmable pin used to read or drive digital logic levels.

## 2 How does input mode differ from output mode?

Input mode senses an external level; output mode drives a level chosen by software.

## 3 Why is an LED resistor required?

It limits LED current and protects the LED and GPIO. Its value must suit supply voltage, LED forward voltage and permitted current.

## 4 What is a floating input?

An input without a defined bias or driven signal; noise can make its reading change unpredictably.

## 5 What does a pull-down resistor do?

It holds the input near ground when the switch is open; pressing the active-high switch connects the input to 3.3 V.

## 6 Which ESP32 pins are used here?

GPIO16 drives the external LED and GPIO4 reads the push button.

## 7 Which STM32 pins appear in the screenshots?

PA5 and PC9 for the blink example; PC13 input and PC8 output for the button example.

## 8 What is polling?

Repeatedly reading an input inside the main loop to detect its state.

## 9 What is switch bounce?

A mechanical contact may change state several times around a press or release; software or hardware filtering can reject these short transitions.

## 10 Does sleep(0.1) guarantee debouncing?

No. It slows polling, but a dedicated debounce decision or stable-time check is needed for reliable event counting.

## 11 What does HAL_GPIO_WritePin do?

It sets a selected STM32 GPIO output high or low through the HAL library.

## 12 Why does the original STM32 LED stay on after release?

The variable val is set to 1 on a high input and is never set back to 0.

## 13 How does the corrected STM32 version solve that?

It reads PC13 in every iteration and writes that current state to PC8.

## 14 What is the ESP32 blink frequency?

One second high plus one second low gives a 2 s period, or 0.5 Hz.

## 15 Why is each STM32 blink pin only high for one quarter of its repeating sequence?

The source handles the PA5 high/low pair and then the PC9 high/low pair, with four separate one-second delays.

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
