@echo off

SET MAKE_MODE=UNIX
set USER=dreiners
set HOME=/cygdrive/c/users/dreiners
SET PATH=c:\users\dreiners\cygwin\bin;c:\users\dreiners\cygwin\usr\X11R6\bin;%PATH%;c:\Program Files\Microsoft Visual Studio .NET 2003\Common7\IDE;c:\Program Files\Microsoft Visual Studio .NET 2003\Common7\Tools
vsvars32.bat

c:
cd \users\dreiners\OpenSG_db

bash dailybuild_copy
