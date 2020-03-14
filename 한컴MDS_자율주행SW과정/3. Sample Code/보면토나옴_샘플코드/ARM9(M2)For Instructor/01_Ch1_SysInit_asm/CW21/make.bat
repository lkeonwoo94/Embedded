@echo off 
del .\test.bin
echo test.bin이 삭제되었습니다.
rem pause

.\objcopy app.elf -O binary .\test.bin

echo TEST.BIN이 작성되었습니다.
rem pause