@echo off
cd ..
call build.bat x86 Release MPCHC

cd testbuild

copy ..\bin\mpc-hc_x86\mpc-hc.exe .

rd /s/y Shaders LAVFilters Lang

robocopy "..\src\mpc-hc\res\shaders\external" "Shaders" /S /XO /XF
robocopy "..\bin\mpc-hc_x86\LAVFilters" "LAVFilters" /S /XO /XF "*.pdb"
robocopy "..\bin\mpc-hc_x86\Lang" "Lang" /S /XO /XF

7za a mpc-hc.7z mpc-hc.exe Shaders\* LAVFilters\* Lang\*
pause