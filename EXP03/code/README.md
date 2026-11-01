# Experiment 3 Timer and delay generation

ESP32: `ESP32/timer_toggle.py` reproduces the screenshot. It configures Timer 2 for 748 callbacks per second and toggles GPIO2 on each callback, giving an ideal output of 374 Hz. Timer IDs depend on the exact ESP32 variant and MicroPython firmware; use the source board/firmware or confirm available timers before changing the code. Stop it from the console using `timer.deinit()`.

STM32: `STM32/main_report_excerpt.c` preserves the code printed in the report. It is not a complete CubeIDE project. `SystemClock_Config`, headers and generated clock/MSP/interrupt support are needed. Configure TIM2 interrupt handling so `TIM2_IRQHandler` calls `HAL_TIM_IRQHandler(&htim2)` and enable the TIM2 clock and NVIC interrupt through the board's CubeMX project. The report uses PSC 15 and ARR 1622; the separate configuration screenshot uses PSC 299 and ARR 373. Neither source establishes the final timer clock, so the waveform frequency cannot be calculated reliably for that board yet. Do not combine the two variants silently.

Probe STM32 PA5 or ESP32 GPIO2, with probe ground on the same board's GND. The source target MCU is STM32F446RETx. Hardware operation has not been tested here.
