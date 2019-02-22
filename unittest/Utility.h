//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include <string>

class UnitTestUtil 
{

public:
    static std::string GetSysSeparator();
    static std::string GetTestResourceFolder();
    static bool        GetFolderAppDataPath(std::string & outPath);

    static bool FileExists(std::string fullPath);

    static void print_Ascii_BUG ();
    static void print_Ascii_DEER();
};

