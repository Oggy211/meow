# EXP03 Viva questions and answers

Timer and delay generation. Questions cover the documented STM32 and ESP32 implementations.

[Experiment overview](README.md) | [Components and connections](components_and_connections.md)

## 1 What is a hardware timer?

A peripheral counter driven by a clock, used to measure intervals or generate periodic events.

## 2 What does the prescaler do?

It divides the timer input clock before the counter increments.

## 3 What is ARR?

The auto-reload value that sets the end count for the timer period.

## 4 Why do PSC and ARR calculations use plus one?

A programmed divider PSC represents PSC+1, and an up-counter counting from zero through ARR uses ARR+1 counts.

## 5 What is the update frequency equation?

f_update = f_TIM / ((PSC+1)(ARR+1)) for this basic up-counting case.

## 6 Why is output frequency half the update rate?

The output toggles once per event; two toggles are needed for one full high-low cycle.

## 7 What is HAL_TIM_Base_Start_IT used for?

It starts a base timer with update interrupts enabled.

## 8 Where is PA5 toggled?

Inside HAL_TIM_PeriodElapsedCallback when the callback belongs to TIM2.

## 9 Can the printed STM32 main.c excerpt run alone?

No. It needs board headers, clock setup, generated timer clock/MSP/NVIC configuration and the interrupt handler.

## 10 Which STM32 timer constants are final?

The archive is inconsistent: text says PSC15 and ARR1622, while the screenshot says PSC299 and ARR373. The final project must confirm them.

## 11 What is the ESP32 timer rate and output rate?

The callback rate is 748 Hz; one toggle per callback produces an ideal 374 Hz output.

## 12 What is the ideal ESP32 output period?

1/374 s, approximately 2.674 ms.

## 13 Why use a timer instead of long blocking delays?

Periodic events can be scheduled while the main program continues other work.

## 14 Why keep an interrupt callback short?

Long callbacks delay other processing and increase timing disturbances.

## 15 How do you stop the MicroPython timer?

Call timer.deinit().

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
