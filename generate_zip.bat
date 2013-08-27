@echo off

set YYYY-MM-DD-HH-MM-SS=%DATE:~6,4%%DATE:~3,2%%DATE:~0,2%%TIME:~0,2%%TIME:~3,2%%TIME:~6,2%
set FIRST_HOUR_DIGIT="%YYYY-MM-DD-HH-MM-SS:~8,1%"

if %FIRST_HOUR_DIGIT%==" " (
	set YYYY-MM-DD-HH-MM-SS=%YYYY-MM-DD-HH-MM-SS:~0,8%0%YYYY-MM-DD-HH-MM-SS:~9,5%
)

"C:\Program Files\7-Zip\7z.exe" a "mkfusion-0.4.2_%YYYY-MM-DD-HH-MM-SS%.zip" * -r -x!*.dll -x!Makefile -x!*.Debug -x!*.Release -x!bin/* -x!deps/* -x!libs/apache2/* -x!libs/libssh/* -x!libs/iis/* -x!libs/qtservice/* -x!obj/* -x!WINDOWS/*.exe -x!*.zip -x!*.user -x!.svn
