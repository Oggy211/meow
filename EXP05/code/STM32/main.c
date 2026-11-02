
#include "stm32f4xx_hal.h"
#include "ssd1306_compat.h"
#include <stdio.h>
#include <stdint.h>

/* Peripheral handles */
ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;

/* Function declarations */
static void SystemClock_Config(void);
static void GPIO_Init(void);
static void ADC1_Init(void);
static void I2C1_Init(void);
static void Error_Handler(void);

int main(void)
{
    HAL_Init();

    SystemClock_Config();
    GPIO_Init();
    ADC1_Init();
    I2C1_Init();

    /* Initialize OLED */
    SSD1306_Init(&hi2c1);

    uint32_t adc_value;
    float voltage;

    char adc_text[20];
    char voltage_text[20];

    while (1)
    {
        /* Start ADC conversion */
        if (HAL_ADC_Start(&hadc1) != HAL_OK)
            Error_Handler();

        /* Wait for conversion to finish */
        if (HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK)
            Error_Handler();

        /* Read digital ADC value */
        adc_value = HAL_ADC_GetValue(&hadc1);

        /* Convert ADC value to approximate voltage */
        voltage = (adc_value * 3.3f) / 4095.0f;

        /* Format display values */
        snprintf(adc_text, sizeof(adc_text),
                 "ADC: %lu",
                 (unsigned long)adc_value);

        snprintf(voltage_text, sizeof(voltage_text),
                 "V: %.2f V",
                 (double)voltage);

        /* Clear OLED display */
        SSD1306_Clear();

        /* Display ADC value */
        SSD1306_WriteText(0, 0, adc_text);

        /* Display voltage */
        SSD1306_WriteText(0, 16, voltage_text);

        /* Update OLED */
        SSD1306_Update();

        /* Stop ADC */
        HAL_ADC_Stop(&hadc1);

        HAL_Delay(500);
    }
}

/* System Clock Configuration */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef osc = {0};
    RCC_ClkInitTypeDef clk = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    osc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    osc.HSIState = RCC_HSI_ON;
    osc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    osc.PLL.PLLState = RCC_PLL_NONE;

    if (HAL_RCC_OscConfig(&osc) != HAL_OK)
        Error_Handler();

    clk.ClockType = RCC_CLOCKTYPE_HCLK |
                    RCC_CLOCKTYPE_SYSCLK |
                    RCC_CLOCKTYPE_PCLK1 |
                    RCC_CLOCKTYPE_PCLK2;

    clk.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
    clk.APB1CLKDivider = RCC_HCLK_DIV1;
    clk.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&clk, FLASH_LATENCY_0) != HAL_OK)
        Error_Handler();
}

/* GPIO Configuration */
static void GPIO_Init(void)
{
    GPIO_InitTypeDef gpio = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /* PA0: ADC1 Channel 0 */
    gpio.Pin = GPIO_PIN_0;
    gpio.Mode = GPIO_MODE_ANALOG;
    gpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &gpio);

    /* PB8: I2C1 SCL */
    gpio.Pin = GPIO_PIN_8;
    gpio.Mode = GPIO_MODE_AF_OD;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &gpio);

    /* PB9: I2C1 SDA */
    gpio.Pin = GPIO_PIN_9;
    gpio.Mode = GPIO_MODE_AF_OD;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &gpio);
}

/* ADC1 Configuration */
static void ADC1_Init(void)
{
    ADC_ChannelConfTypeDef channel = {0};

    __HAL_RCC_ADC1_CLK_ENABLE();

    hadc1.Instance = ADC1;

    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    if (HAL_ADC_Init(&hadc1) != HAL_OK)
        Error_Handler();

    channel.Channel = ADC_CHANNEL_0;
    channel.Rank = 1;
    channel.SamplingTime = ADC_SAMPLETIME_144CYCLES;

    if (HAL_ADC_ConfigChannel(&hadc1, &channel) != HAL_OK)
        Error_Handler();
}

/* I2C1 Configuration */
static void I2C1_Init(void)
{
    __HAL_RCC_I2C1_CLK_ENABLE();

    hi2c1.Instance = I2C1;

    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c1) != HAL_OK)
        Error_Handler();
}

/* Error Handler */
static void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {
    }
}
