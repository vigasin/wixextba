@echo off

path=%wix%\bin;%path%

rd obj /q/s 2>nul 1>nul
md obj 1>nul 2>nul

echo Building examples...

Call :build Bundle1
Call :build Bundle2
Call :build Bundle3
Call :build Bundle4
Call :build Bundle5
Call :build Bundle6
Call :build Bundle7
Call :build Bundle8

rd obj /q/s 2>nul 1>nul

echo.
echo Build complete
echo.

goto :EOF
REM *****************************************************************
REM End of Main
REM *****************************************************************


REM *****************************************************************
REM  Build WiX code
REM *****************************************************************
:build
candle -nologo -ext WixUtilExtension -ext WixNetFxExtension -ext ..\build\WixBalExtensionExt.dll -out obj\ %1.wxs
if %errorlevel% neq 0 (
  echo Candle error: %errorlevel%
  pause
  goto :EOF
)

light -nologo -spdb -ext WixUtilExtension -ext WixNetFxExtension -ext ..\build\WixBalExtensionExt.dll obj\%1.wixobj -o %1.exe
if %errorlevel% neq 0 (
  echo Light error: %errorlevel%
  pause
  goto :EOF
)
goto :EOF
REM *****************************************************************
