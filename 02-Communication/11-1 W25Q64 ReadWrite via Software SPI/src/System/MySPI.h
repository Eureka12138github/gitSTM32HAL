#ifndef __MYSPI_H
#define __MYSPI_H

#include <stdint.h>

/* ==================== SPI 引脚宏定义 ====================
 *
 * 使用说明：
 * 1. 这些引脚宏必须在 CubeMX 中正确配置
 * 2. 在 main.h 或此文件中定义引脚映射
 * 3. 默认使用 PA4-PA7，如需修改请取消注释并更改引脚定义
 *
 * ======================================================== */

// 取消下面注释以使用自定义引脚

#define MY_SPI_CS_PORT GPIOA
#define MY_SPI_CS_PIN GPIO_PIN_4

#define MY_SPI_SCK_PORT GPIOA
#define MY_SPI_SCK_PIN GPIO_PIN_5

#define MY_SPI_MISO_PORT GPIOA
#define MY_SPI_MISO_PIN GPIO_PIN_6

#define MY_SPI_MOSI_PORT GPIOA
#define MY_SPI_MOSI_PIN GPIO_PIN_7

// 函数声明
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t MySPI_SwapByte(uint8_t ByteSend);

#endif
