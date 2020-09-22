import sys
import os.path
import urllib


thisFilePath = os.path.dirname(os.path.abspath(__file__))
os.chdir(thisFilePath)
os.chdir("..")
os.chdir("..")

isdir = os.path.isdir("xerces-c")
print ("Is Dir: ", isdir) 
if not isdir:
    os.system("git clone --branch xerces-3.2.2 https://github.com/apache/xerces-c.git")


os.chdir("xerces-c")
if not os.path.isdir("build"):
    os.mkdir("build")
os.chdir("build")

if sys.platform == "win32":
    os.system("cmake -G \"Visual Studio 15 2017 Win64\" -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=libs -DCMAKE_CONFIGURATION_TYPES=\"Release\" -Dxmlch-type=wchar_t -DCMAKE_CXX_FLAGS_RELEASE:STRING=\"-MD -O2 -Ob2 -DNDEBUG\" ..")
else:
    os.system("cmake .. -DBUILD_SHARED_LIBS=OFF -Dxmlch-type=uint16_t -Dnetwork=OFF")

os.system("cmake --build . --config Release --target install")