/**
 * @file W25Q64.c
 * @brief W25Q64 Flash 存储器驱动程序（基于软件 SPI）
 * @version 1.0
 * @date 2026-03-22
 *
 * @note 使用 MySPI 软件 SPI 驱动进行通信
 *       支持页编程、扇区擦除、数据读取等功能
 */

#include "stm32f1xx_hal.h"
#include "MySPI.h"
#include "W25Q64.h"
#include "W25Q64_INS.h"

/**
 * @note 调用以下函数前需确保已在 CubeMX 中配置好 SPI 引脚并调用 MX_GPIO_Init()
 * 具体引脚配置请参考 MySPI.h 文件
 */

/**
 * @brief 读取 W25Q64 的制造商 ID 和设备 ID
 * @param MID 指向存储制造商 ID 的变量（输出）
 * @param DID 指向存储设备 ID 的变量（输出）
 *
 * @note JEDEC ID 读取时序：
 *       1. CS 拉低
 *       2. 发送 0x9F 命令
 *       3. 依次读取：制造商 ID、存储器类型 ID、容量 ID
 *       4. CS 拉高
 *
 * @example
 *   uint8_t mid;
 *   uint16_t did;
 *   W25Q64_ReadID(&mid, &did);
 *   // W25Q64: mid=0xEF, did=0x4017
 */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();							  // CS 引脚置低，开始传输
	MySPI_SwapByte(W25Q64_JEDEC_ID);		  // 此 0X9F 代表读 ID 指令，在接下来的传输中从机将会发 ID 号给主机，但现在没有，故返回值不要，属于抛玉引砖
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE); // 此 0XFF 无实际意义，主要是为了把从机的数据交换过来，属于抛砖引玉，*MID 收到厂商 ID
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	*DID = (*DID << 8) | MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	//	*DID <<= 8;
	//	*DID |= MySPI_SwapByte(W25064_DUMMY_BYTE);
	MySPI_Stop();
}

/**
 * @brief 写使能操作
 * @note 所有写操作（编程、擦除）前必须先执行此函数
 *
 * @details W25Q64 写保护机制：
 *          - 上电默认处于写保护状态
 *          - 必须发送 0x06 写使能命令才能进行写操作
 *          - 写使能仅对下一个操作有效
 */
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE); // 紧随 MySPI_Start();的是指令码
	MySPI_Stop();
}

/**
 * @brief 等待 W25Q64 空闲（忙标志检测）
 * @note 超时时间设置为 10000 次循环
 *
 * @details 忙检测原理：
 *          1. 发送 0x05 命令（读状态寄存器 1）
 *          2. 持续读取状态字，检查 Bit0 (BUSY 标志)
 *          3. BUSY=1 表示正在执行操作，BUSY=0 表示空闲
 *
 * @attention 擦除和编程操作后必须调用此函数等待完成
 */
void W25Q64_WaitBusy(void)
{
	uint32_t TimeOut = 10000;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	// 判断状态寄存器 1 的最后一位数是否为 1，若 1，表示此时忙，进入等待状态
	while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
	{
		TimeOut--;
		if (TimeOut == 0)
		{
			break;
		}
	}

	MySPI_Stop();
}

/**
 * @brief 页编程操作（写入数据到指定地址）
 * @param Address 目标地址（24 位，范围：0x000000 ~ 0x3FFFFF）
 * @param DataArray 要写入的数据缓冲区指针
 * @param Count 要写入的字节数（最大 256 字节/页）
 *
 * @note 页编程特性：
 *       - 最小编程单位：1 字节
 *       - 最大编程单位：256 字节（1 页）
 *       - 如果跨页写入，地址会自动回绕到页首
 *       - 只能将 1 变为 0，不能将 0 变为 1
 *
 * @attention 使用前必须确保目标区域已擦除（全为 0xFF）
 */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	uint16_t i;
	W25Q64_WriteEnable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	MySPI_SwapByte(Address >> 16); // 连续发送 24 位地址
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	for (i = 0; i < Count; i++)
	{
		MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	W25Q64_WaitBusy(); // 此为事后等待，与事前等待略有不同，事后更保险，事前更效率
}

/**
 * @brief 扇区擦除操作（4KB）
 * @param Address 要擦除扇区内的任意地址
 *
 * @note 扇区擦除特性：
 *       - 擦除单位：4KB（1 个扇区）
 *       - 擦除后该扇区所有位变为 1（即 0xFF）
 *       - 可以多次擦除同一扇区（无影响）
 *       - W25Q64 共有 2048 个扇区（8MB / 4KB = 2048）
 *
 * @example
 *   // 擦除第 0 个扇区（地址 0x000000-0x000FFF）
 *   W25Q64_Sector_Erase(0x000000);
 *
 *   // 擦除包含地址 0x001234 的扇区
 *   W25Q64_Sector_Erase(0x001234); // 实际擦除 0x001000-0x001FFF
 */
void W25Q64_Sector_Erase(uint32_t Address)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	MySPI_SwapByte(Address >> 16); // 连续发送 24 位地址
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	MySPI_Stop();
	W25Q64_WaitBusy();
}

/**
 * @brief 读取数据操作（连续读取多个字节）
 * @param Address 起始读取地址（24 位）
 * @param DataArray 数据存储缓冲区指针（输出）
 * @param Count 要读取的字节数（最大 65536 字节）
 *
 * @note 数据读取特性：
 *       - 支持连续读取（自动递增地址）
 *       - 最大读取速度：50MHz（普通读取模式）
 *       - 可以跨越页、扇区边界读取
 *       - 读取操作无需等待（非破坏性操作）
 *
 * @example
 *   uint8_t buffer[256];
 *   // 从地址 0x000000 读取 256 字节
 *   W25Q64_ReadData(0x000000, buffer, 256);
 */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Address >> 16); // 连续发送 24 位地址
	MySPI_SwapByte(Address >> 8);
	MySPI_SwapByte(Address);
	for (i = 0; i < Count; i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
	// 注意：读取操作是非破坏性的，无需等待忙标志
	// 且前面的写/擦除操作已经等待过了，此时肯定不忙
}
