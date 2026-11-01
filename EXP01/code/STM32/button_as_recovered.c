/* Recovered from Screenshot 2026-07-27 125313.png.
 * Integration routine: PC13 input, PC8 push-pull output.
 * Source behavior retained: val never resets after the first HIGH input.
 */
#include "main.h"

void exp1_button_as_recovered(void)
{
    uint8_t val = 0;
    while (1)
    {
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET)
        {
            val = 1; // Latches HIGH; the source has no reset assignment.
        }
        if (val == 1)
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);
        }
    }
}
