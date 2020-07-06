import os.path
import urllib
import zipfile

print("Building Xerces-c-lib")

XERCES_VERSION = "3.2.2"
XERCES_ZIP_FILE = "shared/xerces-c-" + XERCES_VERSION + ".zip"
XERCES_DIR_PATH = "shared/xerces-c-" + XERCES_VERSION


if not os.path.exists("shared/builds"):
    os.mkdir("shared/builds")
    os.mkdir("shared/lib")
    os.mkdir("shared/include")
    os.mkdir("shared/bin")

# check for other system lib file (.lib [for windows])
if not os.path.isfile("shared/lib/libxerces-c.a"):
    print ("===============================================================")
    print ("= M A K E   X e r c e s - C                                   =")
    print ("===============================================================")
    if not os.path.isfile(XERCES_ZIP_FILE):
        print("Downloading xerces")
        urllib.urlretrieve("http://archive.apache.org/dist/xerces/c/3/sources/xerces-c-" + XERCES_VERSION + ".zip", XERCES_ZIP_FILE)
    if not os.path.isdir(XERCES_DIR_PATH):
        with zipfile.ZipFile(XERCES_ZIP_FILE, 'r') as zip_ref:
            zip_ref.extractall("shared")