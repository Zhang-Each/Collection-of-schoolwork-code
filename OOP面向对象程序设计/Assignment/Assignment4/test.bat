@echo off
echo Please input the command you need to do
echo You can input "pdadd","pdlist","pdremove"."pdshow"
set /p command=
if %command%==pdadd (call pdadd.exe)
if %command%==pdlist (call pdlist.exe)
if %command%==pdshow (call pdshow.exe)
if %command%==pdremove (call pdremove.exe)
pause
