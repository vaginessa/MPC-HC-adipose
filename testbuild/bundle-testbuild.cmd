@echo off

copy ..\bin\mpc-hc_x86\mpc-hc.exe .

xcopy /e/i /y ..\bin\mpc-hc_x86\Shaders Shaders
xcopy /e/i /y ..\bin\mpc-hc_x86\LAVFilters LAVFilters
xcopy /e/i /y ..\bin\mpc-hc_x86\Lang Lang

7za a mpc-hc.7z mpc-hc.exe Shaders LAVFilters Lang
pause