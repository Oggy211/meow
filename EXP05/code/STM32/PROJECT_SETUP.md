# STM32 OLED project setup

The user supplied ssd1306.c and ssd1306.h on 1 November 2026. Their originals are preserved in originals/. Build the working copies in this folder, not the originals.

Add main.c, ssd1306.c and ssd1306_compat.c to the matching STM32F446RE HAL project. Place ssd1306.h and ssd1306_compat.h on the include path. The adapter connects the report's uppercase function calls to the driver's lowercase functions; only the global hi2c1 handle is supported.

The working driver adds a percent glyph for the report's POT display. Its font is embedded; no separate font files are required. The adapter adds bounded text positioning and a clipped percentage bar. The original I2C address is 0x3C, shifted left for STM32 HAL.

Keep the project's startup files, linker script, HAL drivers and HAL configuration. The report application initializes PA0 for ADC1 and PB8/PB9 for I2C1 at 100 kHz. Reconcile generated initialization with this application rather than compiling two competing main functions or peripheral handles.

The supplied driver uses blocking HAL_MAX_DELAY transfers and ignores the returned I2C error status. If the display fails, check power, address, wiring and pull-ups; this code does not report bus errors. Driver orientation and actual display operation require hardware verification. The application and adapter have not been compiled in a complete STM32 HAL project or run on hardware here.
