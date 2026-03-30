/**
 * @file W25Q64_INS.h
 * @brief W25Q64 Flash 存储器指令集定义
 * @version 1.0
 * @date 2026-03-22
 *
 * @note 包含 W25Q64 所有操作指令、状态寄存器位定义
 *       参考 W25Q64FV 数据手册
 */

#ifndef __W25Q64_INS_H
#define __W25Q64_INS_H

/* ==================== 使能类指令 ==================== */

#define W25Q64_WRITE_ENABLE 0x06  /**< 写使能指令 */
#define W25Q64_WRITE_DISABLE 0x04 /**< 写失能指令 */

/* ==================== 状态寄存器指令 ==================== */

#define W25Q64_READ_STATUS_REGISTER_1 0x05 /**< 读状态寄存器 1 */
#define W25Q64_READ_STATUS_REGISTER_2 0x35 /**< 读状态寄存器 2 */
#define W25Q64_WRITE_STATUS_REGISTER 0x01  /**< 写状态寄存器指令 */

/* ==================== 编程类指令 ==================== */

#define W25Q64_PAGE_PROGRAM 0x02      /**< 页编程指令（标准 SPI 模式） */
#define W25Q64_QUAD_PAGE_PROGRAM 0x32 /**< 四线页编程指令 */

/* ==================== 擦除类指令 ==================== */

#define W25Q64_BLOCK_ERASE_64KB 0xD8 /**< 64KB 块擦除指令 */
#define W25Q64_BLOCK_ERASE_32KB 0x52 /**< 32KB 块擦除指令 */
#define W25Q64_SECTOR_ERASE_4KB 0x20 /**< 4KB 扇区擦除指令 */
#define W25Q64_CHIP_ERASE 0xc7       /**< 整片擦除指令 */
#define W25Q64_ERASE_SUSPEND 0x75    /**< 擦除暂停指令 */
#define W25Q64_ERASE_RESUME 0x7A     /**< 擦除恢复指令 */

/* ==================== 功耗管理指令 ==================== */

#define W25Q64_POWER_DOWN 0xB9                       /**< 进入掉电模式指令 */
#define W25Q64_HIGH_PERFORMANCE_MODE 0xA3            /**< 进入高性能模式指令 */
#define W25Q64_RELEASE_POWER_DOWN_HPM_DEVICE_ID 0xAB /**< 退出掉电/高性能模式并读取设备 ID */

/* ==================== 读取模式指令 ==================== */

#define W25Q64_CONTINUOUS_READ_MODE_RESET 0xFF /**< 连续读模式复位指令 */
#define W25Q64_READ_DATA 0x03                  /**< 标准读数据指令 */
#define W25Q64_FAST_READ 0x0B                  /**< 快速读数据指令 */

/* 双输出/双 I/O 读取 */
#define W25Q64_FAST_READ_DUAL_OUTPUT 0x3B /**< 双输出快速读指令 */
#define W25Q64_FAST_READ_DUAL_IO 0xBB     /**< 双 I/O 快速读指令 */

/* 四输出/四 I/O 读取 */
#define W25Q64_FAST_READ_QUAD_OUTPUT 0x6B   /**< 四输出快速读指令 */
#define W25Q64_FAST_READ_QUAD_IO 0xEB       /**< 四 I/O 快速读指令 */
#define W25Q64_OCTAL_WORD_READ_QUAD_IO 0xE3 /**< 八字节四 I/O 快速读指令 */

/* ==================== ID 相关指令 ==================== */

#define W25Q64_MANUFACTURER_DEVICE_ID 0x90 /**< 读制造商/设备 ID 指令 */
#define W25Q64_JEDEC_ID 0x9F               /**< 读 JEDEC ID 指令 */
#define W25Q64_READ_UNIQUE_ID 0x4B         /**< 读唯一 ID 指令 */

/* ==================== 辅助常量定义 ==================== */

#define W25Q64_DUMMY_BYTE 0xFF /**< 虚拟字节（用于 MOSI 空闲时填充） */

#endif
