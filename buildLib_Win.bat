:: This script expects the following arguments: 
:: %1 : Type "Release" or "Debug" 
:: %2 : Runtime Lib: "MD" or "MT"

@echo off
echo Provided arguments: %1 %2

if %1.==. goto ERROR
if %2.==. goto ERROR

@echo on

if exist build ( rd /S /Q build)

mkdir build && cd build

cmake -G "Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=libs -DCMAKE_CONFIGURATION_TYPES=%2 -Dxmlch-type=wchar_t -DCMAKE_CXX_FLAGS_RELEASE:STRING="%1 -O2 -Ob2 -DNDEBUG" ..

cd ..

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat"
REM build libVectorworksMvrGdtf
cd build
MSBuild.exe MvrGdtf.sln /t:Build /p:Configuration=%2 /m

goto END

:ERROR
@echo off
Color 04
echo Not all parameters are provided for this script!

:END
