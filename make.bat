@echo off

cls

mingw32-make clean
mingw32-make

echo;
echo;
echo;
echo ------- test --------



.\test\assert.bat .\test\001_step\01




