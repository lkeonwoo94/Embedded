@echo off 
del .\test.bin
echo test.bin�� �����Ǿ����ϴ�.
rem pause

.\objcopy app.elf -O binary .\test.bin

echo TEST.BIN�� �ۼ��Ǿ����ϴ�.
rem pause