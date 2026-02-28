@echo off
echo Cleaning Keil project intermediate files...

:: 编译输出文件
del /s /q *.o *.d *.crf *.axf *.elf *.bin *.hex *.lib *.lnp *.map *.lst *.sct *.tra *.dep

:: IDE 临时文件
del /s /q *.bak *.tmp *.__i *.iex

:: 日志文件
del /s /q JLinkLog.txt JLinkSettings.ini

:: HTML 报告（可选）
del /s /q *.htm

echo Done.