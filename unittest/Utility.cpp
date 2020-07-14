//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Utility.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#if defined(_WINDOWS)
# include <Shlobj.h>
# include <Shlwapi.h>
#include <locale>
#include <codecvt>
#elif GS_LIN
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif GS_MAC
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif


std::string UnitTestUtil::GetTestResourceFolder()
{
	std::string str = (GITPATH);
#ifdef _WINDOWS
	std::replace( str.begin(), str.end(), '/', '\\'); 
#endif
	str += kSeparator;
	str += "unittest";
	str += kSeparator;
	str += "files";
    return str;
}

bool UnitTestUtil::GetFolderAppDataLocal(std::string& outPath)
{
	//--------------------------------------------------------
	// Implementation for Windows
#ifdef _WINDOWS
    
    // Leave this empty for now
	// Beware, brain-compiled code ahead!
	wchar_t buffer[MAX_PATH];
	HWND hWnd = NULL;
	
	BOOL result = SHGetSpecialFolderPath(hWnd, buffer, CSIDL_LOCAL_APPDATA, false );
	
	if(!result) return false;
    std::wstring ws(buffer);
	outPath = std::string(ws.begin(), ws.end());
    
#elif _LINUX
	// LINUX_IMPLEMENTATION - done
	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	outPath = std::string(homedir);
#elif GS_MAC
	//Implementation for OSX
		struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	outPath = std::string(homedir);
#endif	    

	return true;
}

bool UnitTestUtil::FileExists(std::string stdfullPath)
{
#ifdef _WINDOWS
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(stdfullPath);
 	 const wchar_t* path = wide.c_str();
#else
    const char*    path = stdfullPath.c_str();
#endif
    std::ifstream f(path);
    return f.good();
}
