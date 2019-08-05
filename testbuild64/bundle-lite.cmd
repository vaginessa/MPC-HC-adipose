@echo off
cd ..
call build.bat x64 Release Main

cd testbuild64

copy ..\bin\mpc-hc_x64\mpc-hc64.exe .

7za a mpc-hc64.7z mpc-hc64.exe Shaders\* LAVFilters64\* Lang\*
pause