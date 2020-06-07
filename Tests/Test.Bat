@echo off
@echo Test %1
@echo Test %1 >>%2.res
if exist bridges.in del bridges.in>Nul
if exist bridges.out del bridges.out>Nul
copy %1 bridges.in >nul
Timer %2.exe 20000 65536 >>%2.res
if exist bridges.out goto next
@echo No output file! >>%2.res
goto end
:next
Check.exe %1 bridges.out %1.a >>%2.res
:end