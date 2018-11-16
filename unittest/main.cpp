//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include <iostream>
#include "Include/VectorworksMVR.h"
#include "Unittest.h"
#include "MvrUnittest.h"

#if defined(_WINDOWS)
# include <Shlobj.h>
# include <Shlwapi.h>
#elif GS_LIN
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif GS_MAC
#include <stdio.h> 
#endif

using namespace VectorworksMVR;					

void WriteMVR();
bool GetFolderAppDataPath(std::string& outPath);

int main(int argc, char* argv[])
{
	// Get Current dir
	std::string base;
	GetFolderAppDataPath(base);

	MvrUnittest mvrTest(base);
	bool mvrOK = mvrTest.RunTest();

	return (mvrOK == true);
}

bool GetFolderAppDataPath(std::string& outPath)
{
	//--------------------------------------------------------
	// Implementation for Windows
#ifdef _WINDOWS
    /*
    // Leave this empty for now
	// Beware, brain-compiled code ahead!
	wchar_t buffer[MAX_PATH];
	HWND hWnd = NULL;
	
	BOOL result = SHGetSpecialFolderPath(hWnd, buffer, CSIDL_LOCAL_APPDATA, false );
	
	if(!result) return false;
    std::wstring ws(buffer);
	outPath = std::string(ws.begin(), ws.end());
    */
#elif _LINUX
	// LINUX_IMPLEMENTATION - done
	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	outPath = std::string(homedir);
#elif GS_MAC
	//Implementation for OSX
	const char *homeDir = getenv("HOME");
	outPath = std::string(homeDir);
#endif
	
	return true;
}
