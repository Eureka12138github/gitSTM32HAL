/**
 * @file MySPI.c
 * @brief 软件 SPI 驱动 - 基于 HAL 库实现（依赖 CubeMX 初始化）
 * @version 2.0
 * @date 2026-03-22
 *
 * @note 使用 STM32F103C8 的 GPIOA 端口模拟 SPI 时序
 *       支持 SPI 模式 0 (CPOL=0, CPHA=0)
 *
 * ==================== CubeMX GPIO 配置说明 ====================
 *
 * 在 CubeMX 中配置以下引脚为 GPIO_Output 或 GPIO_Input：
 *
 * 1. CS (片选信号) - PA4
 *    - GPIO Mode: Output Push Pull (推挽输出)
 *    - GPIO Pull-up/Pull-down: Pull-up (上拉)
 *    - GPIO Output Level: High (高电平，初始禁用器件)
 *    - GPIO Speed: Medium Speed (10MHz, 推荐)
 *    - User Label: SPI_CS
 *
 * 2. SCK (时钟信号) - PA5
 *    - GPIO Mode: Output Push Pull (推挽输出)
 *    - GPIO Pull-up/Pull-down: Pull-down (下拉)
 *    - GPIO Output Level: Low (低电平)
 *    - GPIO Speed: Medium Speed (10MHz, 推荐)
 *    - User Label: SPI_SCK
 *
 * 3. MOSI (主机输出) - PA7
 *    - GPIO Mode: Output Push Pull (推挽输出)
 *    - GPIO Pull-up/Pull-down: Pull-down (下拉)
 *    - GPIO Output Level: Low (低电平)
 *    - GPIO Speed: Medium Speed (10MHz, 推荐)
 *    - User Label: SPI_MOSI
 *
 * 4. MISO (主机输入) - PA6
 *    - GPIO Mode: Input Floating (浮空输入) 或 Input Pull-up (上拉输入)
 *    - GPIO Pull-up/Pull-down: No pull-up and no pull-down (浮空)
 *    - User Label: SPI_MISO
 *
 * ============================================================
 * 硬件连接：
 * - CS   -> W25Q64 的 CS 引脚
 * - SCK  -> W25Q64 的 CLK 引脚
 * - MISO -> W25Q64 的 DO/DIO0 引脚
 * - MOSI -> W25Q64 的 DI/DIO1 引脚
 * ============================================================
 */

#include "stm32f1xx_hal.h"
#include "MySPI.h"

/* ==================== 引脚操作宏定义 ====================
 * 使用 HAL 库 GPIO 函数进行引脚操作
 * 注意：MY_SPI_*_PORT 和 MY_SPI_*_PIN 必须在 MySPI.h 中定义
 * ======================================================== */

// 片选引脚 CS - 低电平有效
#define MY_SPI_CS_LOW() HAL_GPIO_WritePin(MY_SPI_CS_PORT, MY_SPI_CS_PIN, GPIO_PIN_RESET)
#define MY_SPI_CS_HIGH() HAL_GPIO_WritePin(MY_SPI_CS_PORT, MY_SPI_CS_PIN, GPIO_PIN_SET)

// 时钟引脚 SCK
#define MY_SPI_SCK_LOW() HAL_GPIO_WritePin(MY_SPI_SCK_PORT, MY_SPI_SCK_PIN, GPIO_PIN_RESET)
#define MY_SPI_SCK_HIGH() HAL_GPIO_WritePin(MY_SPI_SCK_PORT, MY_SPI_SCK_PIN, GPIO_PIN_SET)

// 数据输出引脚 MOSI
#define MY_SPI_MOSI_LOW() HAL_GPIO_WritePin(MY_SPI_MOSI_PORT, MY_SPI_MOSI_PIN, GPIO_PIN_RESET)
#define MY_SPI_MOSI_HIGH() HAL_GPIO_WritePin(MY_SPI_MOSI_PORT, MY_SPI_MOSI_PIN, GPIO_PIN_SET)

// 数据输入引脚 MISO - 读取
#define MY_SPI_MISO_READ() HAL_GPIO_ReadPin(MY_SPI_MISO_PORT, MY_SPI_MISO_PIN)

/**
 * @brief SPI 开始通信（拉低片选）
 * @note 使用前请确保已在 CubeMX 中正确配置 GPIO 引脚并调用 MX_GPIO_Init()
 */
void MySPI_Start(void)
{
	MY_SPI_CS_LOW();
}

/**
 * @brief SPI 停止通信（拉高片选）
 */
void MySPI_Stop(void)
{
	MY_SPI_CS_HIGH();
}

/**
 * @brief SPI 交换一个字节（全双工）
 * @param ByteSend 要发送的字节
 * @return 接收到的字节
 *
 * @note SPI 模式 0 (CPOL=0, CPHA=0):
 *       - SCK 空闲状态为低电平
 *       - 数据在 SCK 上升沿采样（从机输出）/ 下降沿移位（主机输出）
 *       - MSB 先行
 *
 * @attention 关键时序参数：
 *            - tSU: MOSI 建立时间（数据必须在 SCK 上升沿前稳定）
 *            - tH: MOSI 保持时间（数据必须在 SCK 上升沿后保持）
 *            - tV: MISO 有效时间（从机输出数据到 MISO 的时间）
 */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i;
	uint8_t ByteReceive = 0; // 必须初始化为 0！

	for (i = 0; i < 8; i++)
	{
		// 步骤 1: 设置 MOSI（MSB 先行）
		if (ByteSend & (0x80 >> i))
		{
			MY_SPI_MOSI_HIGH();
		}
		else
		{
			MY_SPI_MOSI_LOW();
		}

		// 步骤 2: SCK 上升沿（从机采样 MOSI）
		MY_SPI_SCK_HIGH();

		// 步骤 3: 读取 MISO（从机输出数据）
		if (MY_SPI_MISO_READ())
		{
			ByteReceive |= (0x80 >> i);
		}

		// 步骤 4: SCK 下降沿（完成一个 bit 传输）
		MY_SPI_SCK_LOW();
	}

	return ByteReceive;
}
