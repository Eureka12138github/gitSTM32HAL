#include "LED.h"
#include "stm32f1xx_hal.h"
// LED 引脚宏定义
#define LED1_PORT GPIOA
#define LED1_PIN GPIO_PIN_1
#define LED2_PORT GPIOA
#define LED2_PIN GPIO_PIN_2

/**
 * @brief  点亮 LED1 (PA1 置低电平)
 * @param  无
 * @retval 无
 */
void LED1_ON(void)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);
}

/**
 * @brief  熄灭 LED1 (PA1 置高电平)
 * @param  无
 * @retval 无
 */
void LED1_OFF(void)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);
}

/**
 * @brief  翻转 LED1 状态
 * @param  无
 * @retval 无
 */
void LED1_Turn(void)
{
	HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN);
}

/**
 * @brief  点亮 LED2 (PA2 置低电平)
 * @param  无
 * @retval 无
 */
void LED2_ON(void)
{
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);
}

/**
 * @brief  熄灭 LED2 (PA2 置高电平)
 * @param  无
 * @retval 无
 */
void LED2_OFF(void)
{
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET);
}

/**
 * @brief  翻转 LED2 状态
 * @param  无
 * @retval 无
 */
void LED2_Turn(void)
{
	HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN);
}