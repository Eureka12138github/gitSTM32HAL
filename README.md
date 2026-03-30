# 🚀 STM32 HAL Library Templates

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![STM32](https://img.shields.io/badge/STM32-F103-blue.svg)](https://www.st.com/en/microcontrollers-microprocessors/stm32f1-series.html)
[![PlatformIO](https://img.shields.io/badge/IDE-PlatformIO-orange.svg)](https://platformio.org/)

> A collection of **functional templates** for STM32F103 microcontrollers based on **HAL Library** with PlatformIO.

💡 **Personal Learning Note:** This repository contains my learning notes and project templates. The code is based on the excellent tutorial by **Jiang Xie Ke Ji (江协科技)**, with my own comments and understanding added for self-study purposes.

---

## 📝 Notes

- **Example 3-5 Adaptation**: The original tutorial uses a photoresistor module to control a buzzer. However, due to hardware kit variations, this example has been adapted to use an infrared sensor instead. The functional logic and learning objectives remain identical.
- **Wiring Diagrams**: Complete wiring diagrams for all examples (both completed and upcoming) are available in the `00-Common/1-1 wiring-diagrams/` folder.

---

## 📦 Project Structure

```text
pio/
├── 00-Common/           # Common resources (1 template)
├── 01-Basic/            # Basic peripherals (6 templates)
├── 02-Communication/    # Communication protocols (2 templates)
├── 03-Timer/            # Timers (TODO - 12 templates)
├── 04-ADC-DMA/          # ADC & DMA (TODO - 4 templates)
├── 05-Advanced/         # Advanced features (TODO - 10 templates)
└── 99-Tools/            # Tools & resources 
```

---

## 🎯 Quick Start Guide

### Prerequisites

1. **Hardware**
   - STM32F103C8 (Blue Pill) development board
   - DAP-Link debugger or USB-to-TTL adapter
   - Required peripherals for each example (LEDs, buttons, sensors, etc.)

2. **Software**
   - Visual Studio Code with PlatformIO IDE extension
   - ST-Link or DAP-Link drivers installed

### Setup Steps

1. **Clone the repository**

   ```bash
   git clone https://github.com/Eureka12138github/gitSTM32HAL.git
   cd pio
   ```

2. **Open a project**
   - Open VSCode
   - Go to PlatformIO → Open Project
   - Select any example folder (e.g., `01-Basic/3-1 LED Blinking`)
   - Check README in selected project

3. **Build and upload**
   - Click the arrow icon (Upload) in the PlatformIO toolbar
   - Or use command palette: `PlatformIO: Upload`

---

## 📋 Template Index

### ✅ COMPLETED TEMPLATES

#### 🏗️ 00-Common - Common Resources

| Name | Description |
| --- | --- |
| [2-1 STM32 Project Template](00-Common/2-1%20STM32%20Project%20Template/ "2-1 STM32 工程模板") | PlatformIO base project template |

---

#### 🔌 01-Basic - Basic Peripherals

| Name | Function |
| --- | --- |
| [3-1 LED Blinking](01-Basic/3-1%20LED%20Blinking/ "3-1 LED 闪烁") | GPIO output, LED toggle |
| [3-2 LED Chaser](01-Basic/3-2%20LED%20Chaser/ "3-2 LED 流水灯") | Sequential GPIO control, patterns |
| [3-3 Buzzer](01-Basic/3-3%20Buzzer/ "3-3 蜂鸣器") | Active buzzer control |
| [3-4 Button Control of LED](01-Basic/3-4%20Button%20Control%20of%20LED/ "3-4 按键控制LED") | GPIO input, interrupt handling |
| [3-5 IR-Controlled Buzzer](01-Basic/3-5%20IR-Controlled%20Buzzer/ "3-5 对射式红外控制蜂鸣器") | IR sensor + buzzer (adapted from photoresistor) |
| [4-1 OLED Display](01-Basic/4-1%20OLED%20Display/ "4-1 OLED 显示") | I2C communication basics |

---

#### 📡 02-Communication - Communication Protocols

| Name | Protocol | Device |
| --- | --- | --- |
| [11-1 W25Q64 ReadWrite via Software SPI](02-Communication/11-1%20W25Q64%20ReadWrite%20via%20Software%20SPI/ "11-1 软件SPI读取W25Q64") | SPI (Software) | W25Q64 |
| [11-2 W25Q64 ReadWrite via Hardware SPI](02-Communication/11-2%20W25Q64%20ReadWrite%20via%20Hardware%20SPI/ "11-1 硬件SPI读取W25Q64") | SPI (Hardware) | W25Q64 |

---

### 📋 TODO - UPCOMING TEMPLATES

#### ⏱️ 03-Timer - Timers *(Not Implemented Yet)*

| Name | Function |
| --- | --- |
| 6-1 Timer Interrupt (Internal Trigger) | Basic timer interrupt |
| 6-1-1 Button Single/Double/Triple Click & Long Press | Complex button detection |
| 6-2 Timer Interrupt (External Trigger) | External trigger |
| 6-3 PWM Drive LED | PWM dimming |
| 6-4 PWM Drive Servo | Servo control |
| 6-5 PWM Drive DC Motor | Motor speed control |
| 6-6 Input Capture Mode Frequency Measurement | Frequency measurement |
| 6-7 PWMI Frequency & Duty Cycle Measurement | PWM analysis |
| 6-8 Encoder Interface Speed Measurement | Quadrature decoder |
| 6-9 Timer Measure Function Execution Time | Performance profiling |
| 5-2 Rotary Encoder Counter | Encoder counting |

---

#### 📊 04-ADC-DMA - Data Acquisition *(Not Implemented Yet)*

| Name | Function |
| --- | --- |
| 7-1 ADC Single Channel | Single-channel ADC |
| 7-2 ADC Multi Channel | Multi-channel scanning |
| 8-1 DMA Data Transfer | DMA transfer |
| 8-2 DMA + ADC Multi Channel | ADC + DMA combined |

---

#### ⚡ 05-Advanced - Advanced Features *(Not Implemented Yet)*

| Name | Function |
| --- | --- |
| 12-1 Read/Write Backup Registers | Backup registers |
| 12-2 Real-Time Clock (RTC) | RTC real-time clock |
| 13-1 Modify System Clock | System clock configuration |
| 13-2 Sleep Mode + UART TX/RX | Sleep low-power mode |
| 13-3 Stop Mode + IR Sensor Counter | Stop low-power mode |
| 13-4 Standby Mode + RTC | Standby low-power mode |
| 14-1 Independent Watchdog (IWDG) | Independent watchdog (IWDG) |
| 14-2 Window Watchdog (WWDG) | Window watchdog (WWDG) |
| 15-1 Read Internal FLASH | Internal FLASH programming |
| 15-2 Read Chip ID | Unique device ID |

---

## 📚 Resources

- [Jiang Xie Ke Ji STM32 Tutorial (Bilibili)](https://space.bilibili.com/27495688)
- [PlatformIO Documentation](https://docs.platformio.org/)

---

**Happy Coding & Learning!** 🚀

