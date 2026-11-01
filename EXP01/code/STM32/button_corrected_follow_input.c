/* Corrected alternative to button_as_recovered.c; not the original source.
 * Configure PC13 as a stable input and PC8 as push-pull output in CubeMX.
 * Call this routine after HAL, clock and GPIO initialization.
 */
#include "main.h"

void exp1_button_follow_input(void)
{
    while (1)
    {
        // Read the input each time so the LED also turns off on release.
        GPIO_PinState pressed = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, pressed);
    }
}
