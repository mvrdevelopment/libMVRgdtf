#pragma once

#include "FolderSpecifiers.h"

namespace VectorworksMVR
{
	namespace Filing
	{

typedef Uint32	StorageAttributes;
//General Access
const StorageAttributes kStorageAttrRead				= 0x00000001;
const StorageAttributes	kStorageAttrWrite				= 0x00000001 << 1;
const StorageAttributes kStorageAttrExecute				= 0x00000001 << 2;
//System Attributes
const StorageAttributes kStorageAttrHidden				= 0x00000001 << 3;
const StorageAttributes kStorageAttrSystem				= 0x00000001 << 4;
const StorageAttributes kStorageAttrTemporary			= 0x00000001 << 5;
//Security Attributes
const StorageAttributes kStorageAttrEncrypted			= 0x00000001 << 6;
const StorageAttributes kStorageAttrPermRead			= 0x00000001 << 7;
const StorageAttributes kStorageAttrPermWrite			= 0x00000001 << 8;
const StorageAttributes kStorageAttrPermExecute			= 0x00000001 << 9;
const StorageAttributes kStorageAttrPermBrowse			= 0x00000001 << 10;
//Type Attributes
const StorageAttributes kStorageAttrArchive				= 0x00000001 << 11;
const StorageAttributes kStorageAttrDirectory			= 0x00000001 << 12;
//Flags
const StorageAttributes	kStorageAttrPermFlagsValid		= 0x00000001 << 24;		//Permissions flags are valid if set.


// ------------------------------------------------------------------------------------
struct TDateTimeData
{
	Uint32	fYear;
	Uint32	fMonth;
	Uint32	fDay;
	Uint32	fHour;
	Uint32	fMinute;
	Uint32	fSecond;
};

// ------------------------------------------------------------------------------------
class TXBaseStorageAccess
{
public:
			TXBaseStorageAccess();
	virtual ~TXBaseStorageAccess();

	//Storage element activity time specifiers
	typedef enum {
		eStorageTimeCreated,
		eStorageTimeLastAccessed,
		eStorageTimeLastWritten,
		eStorageTimeLastBackup
	} EStorageTimeReference;

	enum EStorageOperationError : short {
		eStorageSuccess,
		eStorageInvalidParameter,					//Error in routine parameter list
	};

	EStorageOperationError GetStorageElementTimeData(const EStorageTimeReference eStorageTimeReference, TDateTimeData& timeData) const;
};

// ------------------------------------------------------------------------------------
class TFolderIdentifier
{
public:
			TFolderIdentifier();
			TFolderIdentifier(const TXString& fullPath);
	virtual ~TFolderIdentifier();

	bool		IsSet() const;

	TXString	GetFolderPath() const;
	bool		SetByFullPath(const TXString& fullPath);
	TXString	GetPosixFolderPath() const;

	bool		GetFolderContextAttributes(StorageAttributes& folderAttributes) const;
	bool		IsFolderReadOnly() const;

	bool		CreateOnDisk(const TXString& fullPath);
	bool		DeleteOnDisk();
	bool		DuplicateOnDisk(const TFolderIdentifier& newFolder, bool overrideIfNecessary = false, TXString* displayProgressDialog = NULL);
	bool		RevealInOS();

	enum ExistenceState
	{
		eFolderExists = 0,
		eFolderDoesNotExists,
	};

	static ExistenceState ExistsOnDisk(const TXString& fullPath);
	
	
private:
	TXString	fcsPath;
	bool		fbIsSet;
};

// ------------------------------------------------------------------------------------
class TFileIdentifier
{
public:
			TFileIdentifier();
			TFileIdentifier(const TXString& fullPath);
	virtual	~TFileIdentifier();

	bool		IsSet() const;

	bool		SetByFullPath(const TXString& fullPath);
	TXString	GetFileExtension();
	TXString	GetFileNameWithoutExtension();
	TXString	GetPosixFilePath() const;

	bool		GetFileContextAttributes(StorageAttributes& fileAttributes) const;
	bool		IsFileReadOnly();

	bool		ExistsOnDisk();
	bool		DeleteOnDisk();
	bool		RenameOnDisk(const TXString& newName);
	bool		DuplicateOnDisk(const TFileIdentifier& fileToDuplicateTo, bool overwriteIfNecessary = false, bool duplicatePermissions = true) const;
	bool		LaunchInOS();
	bool		RevealInOS();
	
private:
	TXString	fcsPath;
	bool		fbIsSet;
};

// ------------------------------------------------------------------------------------
class TStorageAccessFactory
{
public:
	//Implemented in File.X.cpp
	static TXBaseStorageAccess*	CreateStorageAccess(const TFolderIdentifier&  baseStorageSpecIdentifier);
	static TXBaseStorageAccess*	CreateStorageAccess(const TFileIdentifier&  baseStorageSpecIdentifier);

private:
	//Private constructor/destructor - enforces static class.
	TStorageAccessFactory() {}
	~TStorageAccessFactory() {}
};

// ------------------------------------------------------------------------------------
bool GetFolderWithSpecifer(EFolderSpecifier inWhichFolder, TFolderIdentifier& outFolderID,  bool inCreateIfMissing = false);


bool GetFolderAppDataPath(TXString& outPath);
	}
}