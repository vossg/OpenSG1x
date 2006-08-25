@echo off

python SConsLocal/scons.py %*

if NOT "%COMSPEC%" == "%SystemRoot%\system32\cmd.exe" goto endscons
if errorlevel 9009 echo Did you install python from www.python.org? Or perhaps you need to add python to your PATH!
@REM color 00 causes this script to exit with non-zero exit status
if errorlevel 1 color 00
:endscons


