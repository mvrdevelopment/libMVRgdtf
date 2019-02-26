//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include <string>

#ifdef _WINDOWS
#define kSeparator  '\\'
#else
#define kSeparator  '/'
#endif

class UnitTestUtil 
{

public:
    static std::string GetTestResourceFolder();
    static bool        GetFolderAppDataLocal(std::string & outPath);

    static bool         FileExists(std::string fullPath);
};

