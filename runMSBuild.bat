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
mkdir shared\builds
mkdir shared\lib
mkdir shared\bin
mkdir shared\include
powershell -nologo -noprofile -command "& { Add-Type -A 'System.IO.Compression.FileSystem'; [IO.Compression.ZipFile]::ExtractToDirectory('shared\xerces-c-3.1.4.zip', 'shared\builds\'); }"
msys2_shell.cmd -where . -mingw64 -c "make dependencies"

REM build libVectorworksMvrGdtf
MSBuild.exe libVectorworksMvrGdtf.sln /t:Build /p:Configuration=Release /p:Platform=x64
x64\Release\libVectorworksMvrGdtfTestApp.exe