#-----------------------------------------------------------------------------
#----- Copyright deersoft 2015 - 2018 www.deersoft.de
#-----------------------------------------------------------------------------
from shutil import copy2, copytree, rmtree
from sys import platform
import logging
import os

def CopyFileTo( src, dest ):
  print ("Copy" + src + " to " + dest)
  if os.path.isdir(src):
      if os.path.exists(dest):
          rmtree(dest)
      copytree(src,dest)
  elif os.path.isfile(src):
      copy2(src,dest)
  return

# Get current dir Path
proj_path = os.path.dirname(os.path.realpath(__file__))


if platform == "linux" or platform == "linux2":
    print('Build on Linux')
    # linux
elif platform == "darwin":
    print('Build on OSX')
elif platform == "win32":
    print('Build on Windows')
    lib_xerces  = proj_path + '\\shared\\xerces\\build\\libs\\lib\\'
    lib_gdtf    = proj_path + '\\libs\\'

    # Copy Xerces Windows...
    CopyFileTo(lib_xerces + "xerces-c_3.lib" , lib_gdtf + "xerces-c_3.lib")