call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\Tools\VsDevCmd.bat"
REM build libVectorworksMvrGdtf
MSBuild.exe libVectorworksMvrGdtf.sln /t:Build /p:Configuration=%1 /p:Platform=x64 /m