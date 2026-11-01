# Experiment 1 GPIO

ESP32 files are separate experiments: run one at a time, or save the selected file as `main.py` on the MicroPython board. GPIO16 is an external LED. The button program uses GPIO4 with no internal pull resistor selected; use the documented active-high external bias circuit after confirming the resistor value.

STM32 files are integration routines recovered from screenshots, not full projects. Keep your board-specific CubeIDE project and its generated initialization. Configure the pins listed in each file, add the selected `.c` file to `Core/Src`, declare its function before `main`, and call that function after `HAL_Init`, `SystemClock_Config` and `MX_GPIO_Init`. Select only one experiment routine. The source button version latches on; the separate corrected version follows the input every loop.

The screenshot target MCU is STM32F446RETx. The original `.ioc`, full initialization and original resistor values are absent. Both C and Python files have short explanatory comments. Hardware operation has not been tested here.
