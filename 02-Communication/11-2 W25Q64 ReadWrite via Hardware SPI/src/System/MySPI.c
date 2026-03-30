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
 * @brief 简单的延时函数（用于 SPI 时序）
 * @note 根据实际工作频率调整延时时间
 *       如果速度不够，可以增加 NOP 数量或使用定时器
 */
static void MySPI_Delay(void)
{
	// 简单软件延时，可根据需要调整
	// 对于中低速应用，几个 NOP 指令即可
	__NOP();
	__NOP();
}

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
 *       - 在 SCK 上升沿采样（从机输出数据）
 *       - 在 SCK 下降沿移位（主机输出数据）
 *
 * @attention ByteReceive 必须初始化为 0，否则会导致数据错误！
 *            这是因为未初始化的局部变量可能包含随机值
 */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
	uint8_t i;
	uint8_t ByteReceive = 0; // 必须初始化为 0！

	for (i = 0; i < 8; i++)
	{
		// 1. 主机在 SCK 低电平时将数据放到 MOSI 上（MSB 先行）
		if (ByteSend & (0x80 >> i))
		{
			MY_SPI_MOSI_HIGH();
		}
		else
		{
			MY_SPI_MOSI_LOW();
		}

		// 2. 短暂延时确保数据稳定
		MySPI_Delay();

		// 3. SCK 置高，产生上升沿
		MY_SPI_SCK_HIGH();

		// 4. 从机在上升沿采样 MOSI 数据，同时主机在上升沿读取 MISO 数据
		MySPI_Delay();

		// 5. 读取 MISO 引脚状态
		if (MY_SPI_MISO_READ())
		{
			ByteReceive |= (0x80 >> i); // 将对应位设为 1
		}

		// 6. SCK 置低，产生下降沿，准备下一次数据传输
		MY_SPI_SCK_LOW();
	}

	return ByteReceive;
}
