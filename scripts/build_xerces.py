import sys
import os.path
import urllib
import zipfile
import shutil

print("Building Xerces-c-lib")

windowsReleaseType = "-MD"
if sys.platform == "win32":
    if (len(sys.argv) >= 2):
        windowsReleaseType = sys.argv[1]

XERCES_VERSION = "3.2.2"
XERCES_ZIP_FILE = "shared/xerces-c-" + XERCES_VERSION + ".zip"
XERCES_DIR_PATH = "shared/xerces-c-" + XERCES_VERSION

pathToLibFile = "libs/libxerces-c.a"
if sys.platform == "win32":
    pathToLibFile = "libs/lib/xerces-c_3ddd.lib"

# check for other system lib file (.lib [for windows])
if not os.path.isfile(pathToLibFile):
    if not os.path.isfile(XERCES_ZIP_FILE):
        print("Downloading xerces")
        urllib.urlretrieve("http://archive.apache.org/dist/xerces/c/3/sources/xerces-c-" + XERCES_VERSION + ".zip", XERCES_ZIP_FILE)
    if not os.path.isdir("shared/xerces"):
        with zipfile.ZipFile(XERCES_ZIP_FILE, 'r') as zip_ref:
            zip_ref.extractall("shared")
            os.rename(XERCES_DIR_PATH, "shared/xerces")

    os.chdir("shared")

    extraCmakeOptions = "";
    if sys.platform == "win32":
        os.chdir("xerces")
        if not os.path.isdir("build"):
            os.mkdir("build")
        os.chdir("build")

       
        extraCmakeOptions += "-G \"Visual Studio 15 2017 Win64\" -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=libs -DCMAKE_CONFIGURATION_TYPES=\"Release\" -Dxmlch-type=wchar_t -DCMAKE_CXX_FLAGS_RELEASE:STRING=\""+ windowsReleaseType +" -O2 -Ob2 -DNDEBUG\""
        os.system("cmake "+ extraCmakeOptions +" ..")
        os.system("cmake --build . --config Release --target install")

        shutil.copytree("libs", "../../../libs")
    #we need some more cases for linux and should check all configure-options
    if sys.platform == "darwin" or sys.platform.startswith("linux"):
        os.system("make")

    