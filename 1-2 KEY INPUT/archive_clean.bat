@echo off
echo 正在执行归档清理：删除 Drivers 和 MDK-ARM 目录...

:: 删除 Drivers 目录（包含 HAL 库）
if exist "Drivers" (
    rmdir /s /q "Drivers"
    echo 删除 Drivers 目录成功。
)

:: 删除 MDK-ARM 目录（Keil 工具链支持文件）
if exist "MDK-ARM" (
    rmdir /s /q "MDK-ARM"
    echo 删除 MDK-ARM 目录成功。
)

:: 可选：保留 .ioc 和 .mxproject 用于重建工程
echo 保留 .ioc 和 .mxproject 以供后续重建工程。

echo 归档清理完成！
pause