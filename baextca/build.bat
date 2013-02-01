@echo off

echo Configuring environment...
set MSBUILD="%SystemRoot%\Microsoft.NET\Framework\v4.0.30319\msbuild.exe"
echo.

set outdir=%~dp0..\build

%MSBUILD% baextca.vcxproj /t:Rebuild /p:Configuration=Release,Platform=Win32 /p:RunCodeAnalysis=false /p:DefineConstants="TRACE" /p:OutDir="%outdir%\\" /l:FileLogger,Microsoft.Build.Engine;logfile=build.log
if %errorlevel% neq 0 (
	echo Build failed
	pause
	goto :EOF
)

echo.

goto :EOF

REM *****************************************************************
REM End of Main
REM *****************************************************************


REM *****************************************************************
REM Delete/create directory
REM *****************************************************************
:DeleteDir

rd %1% /q/s 2>nul 1>nul
rem md %1% 2>nul 1>nul
rem if exist %1% goto CREATED
rem echo Couldn't create %1% directory
rem pause
goto :EOF
:CREATED

goto :EOF
