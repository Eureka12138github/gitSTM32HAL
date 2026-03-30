#include "Buzzer.h"
#include "stm32f1xx_hal.h"

#define BUZZER_IO_PORT GPIOB
#define BUZZER_IO GPIO_PIN_12

void Buzzer_ON(void)
{
	HAL_GPIO_WritePin(BUZZER_IO_PORT, BUZZER_IO, GPIO_PIN_RESET);
}
void Buzzer_OFF(void)
{
	HAL_GPIO_WritePin(BUZZER_IO_PORT, BUZZER_IO, GPIO_PIN_SET);
}
void Buzzer_Turn(void)
{
	if (GPIO_ReadOutputDataBit(BUZZER_IO_PORT, BUZZER_IO) == 0)
	{
		HAL_GPIO_WritePin(BUZZER_IO_PORT, BUZZER_IO, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(BUZZER_IO_PORT, BUZZER_IO, GPIO_PIN_RESET);
	}
}