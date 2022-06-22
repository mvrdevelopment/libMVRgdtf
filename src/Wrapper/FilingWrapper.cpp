#include "Prefix/StdAfx.h"

#include "FilingWrapper.h"

#include <sys/stat.h>
#include <string>

#if defined(_WINDOWS)
# include <Shlobj.h>
# include <Shlwapi.h>
#elif _LINUX
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif GS_MAC
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

using namespace VectorworksMVR::Filing;

// ------------------------------------------------------------------------------------
TXBaseStorageAccess::TXBaseStorageAccess()
{
}

TXBaseStorageAccess::~TXBaseStorageAccess()
{
}

TXBaseStorageAccess::EStorageOperationError TXBaseStorageAccess::GetStorageElementTimeData(const EStorageTimeReference eStorageTimeReference, TDateTimeData& timeData) const
{
	DSTOP((kEveryone,"TXBaseStorageAccess::GetStorageElementTimeData()"));
	return eStorageInvalidParameter;
}

// ------------------------------------------------------------------------------------
TFolderIdentifier::TFolderIdentifier()
{
	fbIsSet = false;
}

TFolderIdentifier::TFolderIdentifier(const TXString& fullPath)
{
	SetByFullPath(fullPath);
}

TFolderIdentifier::~TFolderIdentifier()
{
}

bool TFolderIdentifier::IsSet() const
{
	return fbIsSet;
}

TXString TFolderIdentifier::GetFolderPath() const
{
	ASSERTN(kEveryone, fbIsSet);
	return fcsPath;
}

bool TFolderIdentifier::SetByFullPath(const TXString& fullPath)
{
	fbIsSet = true;
	fcsPath = fullPath;
	
#ifdef _WINDOWS
	if (!fcsPath.IsEmpty() && fcsPath.GetLast() != '\\')
	{
		fcsPath<< "\\";
	}
#else
	if (!fcsPath.IsEmpty() && fcsPath.GetLast() != '/')
	{
		fcsPath<< "/";
	}
#endif
	
	return true;
}

TXString TFolderIdentifier::GetPosixFolderPath() const
{
	ASSERTN(kEveryone, fbIsSet);
	return fcsPath;
}

bool TFolderIdentifier::GetFolderContextAttributes(StorageAttributes& folderAttributes) const
{
	DSTOP((kEveryone,"TFolderIdentifier::GetFolderContextAttributes()"));
	return false;
}

bool TFolderIdentifier::IsFolderReadOnly() const
{
	DSTOP((kEveryone,"TFolderIdentifier::IsFolderReadOnly()"));
	return false;
}

bool TFolderIdentifier::CreateOnDisk(const TXString& fullPath)
{
	bool result = false;

#ifdef GS_WIN
	result = CreateDirectory(fullPath, NULL) || ERROR_ALREADY_EXISTS == GetLastError();
#else
	// Get pointer
	const char * ptr = fullPath.GetCharPtr();
	
	// Create dir
	int createdDir =  mkdir(ptr, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	// Check if this was OK
	if (createdDir == 0) { result = true; }

#endif

	return result;
}

bool TFolderIdentifier::DeleteOnDisk()
{
	bool result = false;

#ifdef _WINDOWS
	if ( RemoveDirectory( fcsPath ) )
		result = true;
#elif _LINUX
	const char * ptr = fcsPath.GetCharPtr();
	remove(ptr);
	result = true;
#elif __APPLE__
	const char * ptr = fcsPath.GetCharPtr();
	rmdir(ptr);
	result = true;
#else
	// TODO
#endif
	return result;
}

bool TFolderIdentifier::DuplicateOnDisk(const TFolderIdentifier& newFolder, bool overrideIfNecessary, TXString* displayProgressDialog)
{
	DSTOP((kEveryone,"TFolderIdentifier::DuplicateOnDisk()"));
	return false;
}

bool TFolderIdentifier::RevealInOS()
{
	DSTOP((kEveryone,"TFolderIdentifier::RevealInOS()"));
	return false;
}

/*static*/ TFolderIdentifier::ExistenceState TFolderIdentifier::ExistsOnDisk(const TXString& fullPath)
{
	TFolderIdentifier::ExistenceState result = TFolderIdentifier::eFolderDoesNotExists;

#ifdef _WINDOWS
	if ( PathIsDirectory( fullPath ) )
		result = TFolderIdentifier::eFolderExists;
#elif _LINUX
	// LINUX_IMPLEMENTATION - done
	const char *	ptr			= fullPath.GetCharPtr();
	struct stat sb;
	if ( stat(ptr, &sb) == 0 && S_ISDIR(sb.st_mode) )
		result = TFolderIdentifier::eFolderExists;
#elif GS_MAC
	// Use mkdir on posix systems
	const char *	ptr			= fullPath.GetCharPtr();
	int				createdDir	=  mkdir(ptr, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	
	// check if this succeded
	if (createdDir == 0)
	{
		// remove the dir and return true
		rmdir(ptr);
	}
	else
	{
		// If this fails, there is some other problem
		result = TFolderIdentifier::eFolderExists;
	}
#endif
	
	return result;
}

// ------------------------------------------------------------------------------------
TFileIdentifier::TFileIdentifier()
{
	fbIsSet = false;
}

TFileIdentifier::TFileIdentifier(const TXString& fullPath)
{
	fbIsSet = false;
	this->SetByFullPath(fullPath);
}

TFileIdentifier::~TFileIdentifier()
{
}

bool TFileIdentifier::IsSet() const
{
	return fbIsSet;
}

bool TFileIdentifier::SetByFullPath(const TXString& fullPath)
{
	fcsPath = fullPath;
	fbIsSet = true;
	return true;
}

TXString TFileIdentifier::GetFileExtension()
{
	// Find from Right
	ptrdiff_t loc = fcsPath.ReverseFind('.');
	
	// Check if there is point
	if (loc == -1)
	{
		DSTOP((kEveryone,"No Extension found!"));
		return "";
	}
	// Otherwise return
	return fcsPath.Mid(loc + 1);
}

TXString TFileIdentifier::GetFileNameWithoutExtension()
{
	// Find from Right
	ptrdiff_t dotLoc	= fcsPath.ReverseFind('.');
#ifdef _WINDOWS
	ptrdiff_t slashLoc	= fcsPath.ReverseFind('\\');
#else
	ptrdiff_t slashLoc	= fcsPath.ReverseFind('/');
#endif
	
	// Check if there is point
	if (dotLoc == -1)
	{
		DSTOP((kEveryone,"No Extension found!"));
		dotLoc = fcsPath.GetLength();
	}
	// Check if there is a slash
	if (slashLoc == -1)
	{
		DSTOP((kEveryone,"No Slash found found!"));
		slashLoc = 0;
	}
	// If there is no slash, we need copy the next char
	else { slashLoc++;}
	
	// The dot lox needs to be bigger then the slashlock, so that there
	// Is at least one char that will be copied
	ASSERTN(kEveryone, dotLoc > slashLoc);
	ptrdiff_t length = dotLoc - slashLoc;

	return fcsPath.Mid(slashLoc, length);
}

TXString TFileIdentifier::GetPosixFilePath() const
{
	ASSERTN(kEveryone, fbIsSet);
	return fcsPath;
}

bool TFileIdentifier::GetFileContextAttributes(StorageAttributes& fileAttributes) const
{
	DSTOP((kEveryone,"TFileIdentifier::GetFileContextAttributes()"));
	return false;
}

bool TFileIdentifier::IsFileReadOnly()
{
	DSTOP((kEveryone,"TFileIdentifier::IsFileReadOnly()"));
	return false;
}

bool TFileIdentifier::ExistsOnDisk()
{
#ifdef _WINDOWS
    const wchar_t* path = fcsPath.GetWCharPtr();
#else
    const char* path = fcsPath.GetCharPtr();
#endif

    // Check if you can make a stream to the file
	std::ifstream stream (path);
	return stream.good();
}

bool TFileIdentifier::DeleteOnDisk()
{
	const char* path = fcsPath.GetCharPtr();
	return remove(path) != 0;
}

bool TFileIdentifier::DuplicateOnDisk(const TFileIdentifier& fileToDuplicateTo, bool overwriteIfNecessary, bool duplicatePermissions) const
{
	// You need to copy them begore this in a new object
	TXString txSourcePath	= this->GetPosixFilePath();
	TXString txDestPath		= fileToDuplicateTo.GetPosixFilePath();
	
	// Create the pointers to the path
	const char* sourcePath	= txSourcePath.GetCharPtr();
	const char* destPath	= txDestPath.GetCharPtr();
	
	// create the streams
	std::ifstream source	(sourcePath,	std::ios::binary);
	std::ofstream dest		(destPath,		std::ios::binary);
	
	// Create the iterators
	std::istreambuf_iterator<char> begin_source(source);
	std::istreambuf_iterator<char> end_source;
	std::ostreambuf_iterator<char> begin_dest(dest);
	
	// Do the copy
	copy(begin_source, end_source, begin_dest);
	
	// Close streams
	source.close();
	dest.close();
	
	// Return true
	return true;
}

bool TFileIdentifier::RenameOnDisk(const TXString& newName)
{
	DSTOP((kEveryone,"TFileIdentifier::RenameOnDisk()"));
	return false;
}

bool TFileIdentifier::LaunchInOS()
{
	DSTOP((kEveryone,"TFileIdentifier::LaunchInOS()"));
	return false;
}

bool TFileIdentifier::RevealInOS()
{
	DSTOP((kEveryone,"TFileIdentifier::RevealInOS()"));
	return false;
}

// ------------------------------------------------------------------------------------
/*static*/ TXBaseStorageAccess*	TStorageAccessFactory::CreateStorageAccess(const TFolderIdentifier&  baseStorageSpecIdentifier)
{
	DSTOP((kEveryone,"TStorageAccessFactory::CreateStorageAccess()"));
	return nullptr;
}

/*static*/ TXBaseStorageAccess*	TStorageAccessFactory::CreateStorageAccess(const TFileIdentifier&  baseStorageSpecIdentifier)
{
	DSTOP((kEveryone,"TStorageAccessFactory::CreateStorageAccess()"));
	return nullptr;
}

bool VectorworksMVR::Filing::GetFolderWithSpecifer(EFolderSpecifier inWhichFolder, TFolderIdentifier & outFolderID, bool inCreateIfMissing)
{
	// If you require the Spotlight Folder, you will get a path to a readable location on disk
	if ((Sint32)inWhichFolder == 302 || (Sint32)inWhichFolder == -302/*kSpotlightFolder*/)
	{
		TXString appdataPath;
		if (!VectorworksMVR::Filing::GetFolderAppDataPath(appdataPath))
		{
			return false;
		}

		outFolderID.SetByFullPath(appdataPath);	

		outFolderID.CreateOnDisk(outFolderID.GetPosixFolderPath());


		return true;
	}
	return false;
}

// ------------------------------------------------------------------------------------
bool VectorworksMVR::Filing::GetFolderAppDataPath(TXString& outPath)
{
	//--------------------------------------------------------
	// Implementation for Windows
#ifdef _WINDOWS
	// Beware, brain-compiled code ahead!
	wchar_t buffer[MAX_PATH];
	HWND hWnd = NULL;
	
	BOOL result = SHGetSpecialFolderPath(hWnd, buffer, CSIDL_LOCAL_APPDATA, false );
	
	if(!result) return false;
	outPath = TXString(buffer);
#elif _LINUX
	// LINUX_IMPLEMENTATION - done
	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	outPath = TXString(homedir);
#elif GS_MAC
	//--------------------------------------------------------
	//Implementation for OSX
	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	outPath = TXString(homedir);
	outPath += "/Library/Application Support/mvrexchange/"; 
#endif

	
	return true;
}
