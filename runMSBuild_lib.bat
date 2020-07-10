call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat"
REM build libVectorworksMvrGdtf
cd build
MSBuild.exe MvrGdtf.sln /t:Build /p:Configuration=%1 /m
Release/MvrGdtfUnitTest.exe