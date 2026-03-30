#include "Key.h"
#include "stm32f1xx_hal.h"

// 按键引脚宏定义
#define KEY1_PORT GPIOB
#define KEY1_PIN GPIO_PIN_1
#define KEY2_PORT GPIOB
#define KEY2_PIN GPIO_PIN_11

/**
 * @brief  检测按键是否按下（低电平有效）
 * @param  无
 * @retval 返回按键值：0-无按键，1-KEY1 按下，2-KEY2 按下
 */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;

	if (HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while (HAL_GPIO_ReadPin(KEY1_PORT, KEY1_PIN) == GPIO_PIN_RESET)
			;
		HAL_Delay(20);
		KeyNum = 1;
	}

	if (HAL_GPIO_ReadPin(KEY2_PORT, KEY2_PIN) == GPIO_PIN_RESET)
	{
		HAL_Delay(20);
		while (HAL_GPIO_ReadPin(KEY2_PORT, KEY2_PIN) == GPIO_PIN_RESET)
			;
		HAL_Delay(20);
		KeyNum = 2;
	}

	return KeyNum;
}