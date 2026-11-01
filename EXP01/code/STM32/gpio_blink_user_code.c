/* Recovered from Screenshot 2026-07-27 121355.png.
 * Integration routine, not a complete CubeIDE project.
 * Configure PA5 and PC9 as push-pull outputs; call after HAL/clock/GPIO init.
 */
#include "main.h"

void exp1_gpio_blink(void)
{
    while (1)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);   // PA5 LED on.
        HAL_Delay(1000);                                   // Wait 1 second.
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_Delay(1000);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);   // PC9 LED on.
        HAL_Delay(1000);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
        HAL_Delay(1000);
    }
}
