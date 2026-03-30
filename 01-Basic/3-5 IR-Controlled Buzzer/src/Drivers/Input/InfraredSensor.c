#include "InfraredSensor.h"
#include "stm32f1xx_hal.h"

uint8_t Infrared_Get(void)
{
	return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
}
