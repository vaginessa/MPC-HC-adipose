@echo off
cd ..
call build.bat x64 Release MPCHC

cd testbuild64

copy ..\bin\mpc-hc_x64\mpc-hc64.exe .

rd /s/y Shaders LAVFilters64 Lang

robocopy "..\src\mpc-hc\res\shaders\external" "Shaders" /S /XO /XF
robocopy "..\bin\mpc-hc_x64\LAVFilters64" "LAVFilters64" /S /XO /XF "*.pdb"
robocopy "..\bin\mpc-hc_x64\Lang" "Lang" /S /XO /XF

7za a mpc-hc64.7z mpc-hc64.exe Shaders\* LAVFilters64\* Lang\*
pause