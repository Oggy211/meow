/* Experiment 4 STM32 ADC to UART. Recovered main.c, not a full CubeIDE project.
 * Retain generated main.h, HAL MSP setup, startup files and HAL drivers.
 * ADC1 channel 0 uses PA0 on the STM32F446 family; USART2 uses board setup.
 */
#include "main.h"
#include <stdio.h>
#include <string.h>
ADC_HandleTypeDef hadc1;
UART_HandleTypeDef huart2;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_ADC1_Init(void);
int main(void)
{
   HAL_Init();
   SystemClock_Config();
   MX_GPIO_Init();
   MX_USART2_UART_Init();
   MX_ADC1_Init();
   uint32_t adc_value;
   uint32_t voltage_mv;
   char message[100];
   while (1)
   {
       /* Start conversion and wait for the ADC result. */
       HAL_ADC_Start(&hadc1);
       if (HAL_ADC_PollForConversion(&hadc1, 1000) == HAL_OK)
       {
           adc_value = HAL_ADC_GetValue(&hadc1);
           /* Scale a 12-bit count with the lab 3.3 V reference assumption. */
           voltage_mv = (adc_value * 3300UL) / 4095UL;
           sprintf(message,
                   "ADC = %lu    Voltage = %lu mV\r\n",
                   adc_value,
                   voltage_mv);
           /* Send the measured count and calculated millivolts to the PC. */
           HAL_UART_Transmit(&huart2,
                             (uint8_t *)message,
                             strlen(message),
                             100);
       }
       HAL_ADC_Stop(&hadc1);
       HAL_Delay(500);
   }
}
void SystemClock_Config(void)
{
   RCC_OscInitTypeDef RCC_OscInitStruct = {0};
   RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
   __HAL_RCC_PWR_CLK_ENABLE();
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSIState = RCC_HSI_ON;
   RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
   RCC_OscInitStruct.PLL.PLLM = 16;
   RCC_OscInitStruct.PLL.PLLN = 336;
   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
   RCC_OscInitStruct.PLL.PLLQ = 2;
   RCC_OscInitStruct.PLL.PLLR = 2;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
       Error_Handler();
   }
   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_SYSCLK |
                                 RCC_CLOCKTYPE_PCLK1 |
                                 RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
   {
       Error_Handler();
   }
}
static void MX_ADC1_Init(void)
{
   ADC_ChannelConfTypeDef sConfig = {0};
   hadc1.Instance = ADC1;
   hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
   hadc1.Init.Resolution = ADC_RESOLUTION_12B;
   hadc1.Init.ScanConvMode = DISABLE;
   hadc1.Init.ContinuousConvMode = ENABLE;
   hadc1.Init.DiscontinuousConvMode = DISABLE;
   hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
   hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
   hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
   hadc1.Init.NbrOfConversion = 1;
   hadc1.Init.DMAContinuousRequests = DISABLE;
   hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
   if (HAL_ADC_Init(&hadc1) != HAL_OK)
   {
       Error_Handler();
   }
   sConfig.Channel = ADC_CHANNEL_0;
   sConfig.Rank = 1;
   sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
   if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
   {
       Error_Handler();
   }
}
static void MX_USART2_UART_Init(void)
{
   huart2.Instance = USART2;
   huart2.Init.BaudRate = 115200;
   huart2.Init.WordLength = UART_WORDLENGTH_8B;
   huart2.Init.StopBits = UART_STOPBITS_1;
   huart2.Init.Parity = UART_PARITY_NONE;
   huart2.Init.Mode = UART_MODE_TX_RX;
   huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   huart2.Init.OverSampling = UART_OVERSAMPLING_16;
   if (HAL_UART_Init(&huart2) != HAL_OK)
   {
       Error_Handler();
   }
}
static void MX_GPIO_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStruct = {0};
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
   GPIO_InitStruct.Pin = B1_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);
   GPIO_InitStruct.Pin = LD2_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}
void Error_Handler(void)
{
   __disable_irq();
   while (1)
   {
   }
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif
