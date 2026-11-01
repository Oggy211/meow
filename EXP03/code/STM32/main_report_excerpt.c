/* Transcribed from EXP3_2024300174.docx.
 * Incomplete project excerpt: SystemClock_Config and generated TIM2 MSP/IRQ
 * support are not in the archive. The report uses PSC=15, ARR=1622;
 * its separate CubeMX screenshot instead uses PSC=299, ARR=373.
 * Confirm the final .ioc and timer input clock before calculating frequency.
 */
#include "main.h"
TIM_HandleTypeDef htim2;
/* Function Prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
int main(void)
{
    /* Initialize HAL library */
    HAL_Init();
    /* Configure system clock */
    SystemClock_Config();
    /* Initialize GPIO and TIM2 */
    MX_GPIO_Init();
    MX_TIM2_Init();
    /* Start TIM2 in interrupt mode */
    HAL_TIM_Base_Start_IT(&htim2);
    /* Infinite loop */
    while (1)
    {
        /* Timer operates independently through interrupt */
    }
}
/* TIM2 Initialization */
static void MX_TIM2_Init(void)
{
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    htim2.Instance = TIM2;
    /* Timer configuration */
    htim2.Init.Prescaler = 15;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 1622;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload =
        TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    /* Select internal clock */
    sClockSourceConfig.ClockSource =
        TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2,
                                  &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* Timer master configuration */
    sMasterConfig.MasterOutputTrigger =
        TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode =
        TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(
            &htim2,
            &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}
/* GPIO Initialization */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* Enable GPIO clocks */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /* Set PA5 initially LOW */
    HAL_GPIO_WritePin(GPIOA,
                      GPIO_PIN_5,
                      GPIO_PIN_RESET);
    /* Configure PC13 as input */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    /* Configure PA5 as output */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
/* Timer Period Elapsed Callback */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        /* Toggle LED/output whenever TIM2 expires */
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
}
/* Error Handler */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
