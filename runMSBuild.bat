call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat"
REM load xerces if not in dir
@echo off
echo checking file structure  for Xerces-c-3.1.4...
if exist "shared\xerces-c-3.1.4.zip" (
    goto :ok
) else goto :download
:download
echo downloading missing files.
powershell -Command "Invoke-WebRequest http://archive.apache.org/dist/xerces/c/3/sources/xerces-c-3.1.4.zip -OutFile shared\xerces-c-3.1.4.zip"
:ok
echo Install successful
REM Extract and build Xerces
rmdir /s /q shared\builds
rmdir /s /q shared\lib
rmdir /s /q shared\bin
rmdir /s /q shared\include
mkdir shared\builds
mkdir shared\lib
mkdir shared\bin
mkdir shared\include
powershell -nologo -noprofile -command "& { Expand-Archive -Path shared\xerces-c-3.1.4.zip -DestinationPath shared\builds\ -Force; }"
REM build xerces
cd shared\builds\xerces-c-3.1.4\projects\Win32\VC14\xerces-all\
MSBuild.exe xerces-all.sln /t:Build /p:Configuration="Static Release" /p:Platform=x64 /m
cd ..\..\..\..\..\..\..\
mkdir libs
move "shared\builds\xerces-c-3.1.4\Build\Win64\VC14\Static Release\xerces-c_static_3.lib" libs\xerces-c_3.lib
REM build libVectorworksMvrGdtf
MSBuild.exe libVectorworksMvrGdtf.sln /t:Build /p:Configuration=Release /p:Platform=x64 /m
x64\Release\libVectorworksMvrGdtfTestApp.exe