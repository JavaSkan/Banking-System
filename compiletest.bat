@echo off
setlocal enabledelayedexpansion
set "src_files="
for %%f in (src\*.cpp) do (
    if /i not "%%~nxf"=="main.cpp" (
        set "src_files=!src_files! %%f"
    )
)
@echo on

g++ -g -std=c++17 tests\*.cpp %src_files% -Iinclude -o tests/BankingSystemTestVer.exe 

pause