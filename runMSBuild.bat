call "C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools\VsDevCmd.bat"
powershell -nologo -noprofile -command "& { Expand-Archive -Path shared\xerces-c-3.2.2.zip -DestinationPath shared\ -Force; }"
cd shared
cd xerces-c-3.2.2
mkdir build
cd build
cmake -G "Visual Studio 15 2017 Win64" -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=.\libs -DCMAKE_CONFIGURATION_TYPES:STRING=Release -Dxmlch-type=wchar_t -DCMAKE_CXX_FLAGS_RELEASE:STRING=%1 ..
cmake --build . --config Release --target install
cd ..\..\..\
copy "shared\xerces-c-3.2.2\build\libs\lib\xerces-c_3.lib" libs\xerces-c_3.lib -force
REM build libVectorworksMvrGdtf
MSBuild.exe libVectorworksMvrGdtf.sln /t:Build /p:Configuration=Release /p:Platform=x64 /m
x64\Release\libVectorworksMvrGdtfTestApp.exe