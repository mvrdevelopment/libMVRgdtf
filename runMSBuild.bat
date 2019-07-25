call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat"
REM build libVectorworksMvrGdtf
MSBuild.exe libVectorworksMvrGdtf.sln /t:Build /p:Configuration=Release /p:Platform=x64 /m
x64\Release\libVectorworksMvrGdtfTestApp.exe