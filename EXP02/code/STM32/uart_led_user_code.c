/* User-supplied Experiment 2 code, 1 November 2026.
 * Integration routine: call after HAL, clock, GPIO and USART2 initialization.
 * USART2: 115200 baud, 8N1, no flow control; PA5 output drives the LED.
 * Keep the generated project and huart2 definition; this is not full firmware.
 */
#include "main.h"
extern UART_HandleTypeDef huart2;

void exp2_uart_led(void)
{
    uint8_t c;
    char start_msg[] = "\r\nType 1 to ON, 0 to OFF\r\n> ";
    // Send the prompt once; sizeof - 1 excludes the terminating null byte.
    HAL_UART_Transmit(&huart2, (uint8_t*)start_msg, sizeof(start_msg)-1, HAL_MAX_DELAY);
    while (1)
    {
        // Wait for exactly one character from the serial terminal.
        if (HAL_UART_Receive(&huart2, &c, 1, HAL_MAX_DELAY) == HAL_OK)
        {
            HAL_UART_Transmit(&huart2, &c, 1, HAL_MAX_DELAY); // Echo the character.
            if (c == '1')
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
                char msg[] = "\r\nLED ON\r\n> ";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, sizeof(msg)-1, HAL_MAX_DELAY);
            }
            else if (c == '0')
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
                char msg[] = "\r\nLED OFF\r\n> ";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, sizeof(msg)-1, HAL_MAX_DELAY);
            }
        }
    }
}
