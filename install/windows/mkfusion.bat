@echo off

for /f %%i in ('svnversion') do set REV=%%i

"c:\Program Files\Inno Setup 5\ISCC.exe" "/dPACKAGE_VERSION=0.5.0.%REV%" mkfusion.iss

