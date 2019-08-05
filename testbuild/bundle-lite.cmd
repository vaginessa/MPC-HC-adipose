@echo off
cd ..
call build.bat x86 Release Main

cd testbuild

copy ..\bin\mpc-hc_x86\mpc-hc.exe .

7za a mpc-hc.7z mpc-hc.exe Shaders\* LAVFilters\* Lang\*
pause