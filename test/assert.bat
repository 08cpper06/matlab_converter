@echo off

set IN_FILE=%1.in
set OK_FILE=%1.ok


.\build\matlab_converter.exe %IN_FILE% > .\tmp.result
diff -q %OK_FILE% .\tmp.result > .\result.log

for %%A in (.\result.log) do set SIZE=%%~zA
if %SIZE% == 0 ( 
    echo %IN_FILE% -^> OK 
 ) else ( 
    echo %IN_FILE% -^> NG 
 ) 

del .\tmp.result
del .\result.log
