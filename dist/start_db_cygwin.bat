@echo off

SET MAKE_MODE=UNIX
set USER=reiners
set HOME=/home/reiners
SET PATH=f:\cygwin\bin;%PATH%

f:
cd \user\reiners\opensg_dailybuild

bash dailybuild_copy
