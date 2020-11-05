//
// Copyright (c) Diehl Graphsoft, Inc. 2006.
// All Rights Reserved.
// 
#include "FileIdentifier.h"
#include "FolderIdentifier.h"
#include "UTranslateFiles.h"
#include "FilingWrapper.h"
#include <sys/stat.h>

using namespace VectorworksMVR::Filing;

// ----------------------------------------------------------------------------------------------------
CFileIdentifier::CFileIdentifier()
{
	fFolderID.AddRef();
}

CFileIdentifier::~CFileIdentifier()
{

}

TXString  CFileIdentifier::GetFileFullPath() const
{
	TXString	fullName	= fFolderID.GetFullPath();

	TXString	theFileName	= fFileName;
	CFileIdentifier::ConvertFilename( theFileName );

	fullName				+= theFileName;
	return fullName;
}

VCOMError CFileIdentifier::SetFileFullPath(const TXString& fileFullName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	VCOMError	err	= kVCOMError_Failed;

	// determine if the passed fullPath is windows (containing backward slash)
	// or posix so we would know how to split the path into it's subfolders
	bool	bIsWinPath		= false;
#ifdef _WINDOWS
	if ( fileFullName.GetLength() == 2 && fileFullName[1] == ':' ) {
		bIsWinPath		= true;
	}
	else {
#else
	{
#endif
		ptrdiff_t	at			= fileFullName.Find( '\\' ); 
		ptrdiff_t	at1			= fileFullName.Find( '/' ); 
		if (	(at == -1 && at1 != -1)
			||	(at1 != -1 && at != -1 && at1 < at) )
		{
			bIsWinPath		= false;
		}
		else {
			bIsWinPath		= true;
		}
	}

	ptrdiff_t			at	= 0;
	if ( bIsWinPath ) {
		at = fileFullName.ReverseFind( '\\' );
	}
	else {
		at	= fileFullName.ReverseFind( '/' );
	}

	if ( at >= 0 ) {
		TXString	fullPath	= fileFullName.Left( at );
		fFileName				= fileFullName.Mid( at + 1 );

		if ( ! bIsWinPath && fullPath.IsEmpty() ) {
			fFolderID.SetFullPath( "/" );
		}
		else {
			fFolderID.SetFullPath( fullPath );
		}

		if ( ! bIsWinPath ) {
			// in posix paths ':' is used to represent '/' symbol
			fFileName.Replace(":", "/");
		}

		CFileIdentifier::ValidateName( fFileName );

		err						= kVCOMError_NoError;
	}
	else {
		fFolderID.SetFullPath( fileFullName );
	}

	return err;
}

VCOMError CFileIdentifier::Set(const TXString& fullPath)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fullPath.IsEmpty() )
		return kVCOMError_InvalidArg;

	return this->SetFileFullPath( fullPath );
}

VCOMError CFileIdentifier::Set(EFolderSpecifier folderSpec, bool bUserFolder, const TXString& fileName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fileName.IsEmpty() )
		return kVCOMError_InvalidArg;

	CFolderIdentifier	folderID;
	// fakely increase the ref count so it works localy
	folderID.AddRef();
	if ( VCOM_FAILED( folderID.Set( folderSpec, bUserFolder ) ) )
		return kVCOMError_Failed;

	TXString	fileFullPath	= folderID.GetFullPath();

	TXString	theFileName		= fileName;

	// remove all slashes from the beginning
	while ( theFileName.GetLength() > 0 && theFileName[0] == '/' ) {
		theFileName	= theFileName.Mid( 1 );
	}

#ifdef _WINDOWS
	// the file name may contain relative path
	theFileName.Replace( "/", "\\" );
#endif

	fileFullPath				+= theFileName;

	return this->SetFileFullPath( fileFullPath );
}

VCOMError CFileIdentifier::Set(IFolderIdentifier* pFolderID, const TXString& fileName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( pFolderID == NULL || fileName.IsEmpty() )
		return kVCOMError_InvalidArg;

	CFolderIdentifier*	pTheFolder	= static_cast<CFolderIdentifier*>( pFolderID );
	if ( pTheFolder == NULL )
		return kVCOMError_InvalidArg;

	TXString	fullPath;
	if ( VCOM_FAILED( pTheFolder->GetFullPath( fullPath ) ) )
		return kVCOMError_BadPathSpecified;

	TXString	theFileName		= fileName;

	// remove all slashes from the beginning
	while ( theFileName.GetLength() > 0 && theFileName[0] == '/' ) {
		theFileName	= theFileName.Mid( 1 );
	}

#ifdef _WINDOWS
	// the file name may contain relative path
	theFileName.Replace( "/", "\\" );
#endif

	fullPath				+= theFileName;

	return this->SetFileFullPath( fullPath );
}

VCOMError CFileIdentifier::Clear()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( fFolderID.Clear() ) )
		return kVCOMError_Failed;

	fFileName.Clear();
	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::IsSet()
{
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( fFolderID.IsSet() ) )
		return kVCOMError_Failed;

	return (! fFileName.IsEmpty()) ? kVCOMError_NoError : kVCOMError_Failed;
}

VCOMError CFileIdentifier::ExistsOnDisk(bool& outValue)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath	= this->GetFileFullPath();
	
	TFileIdentifier	fileID;
	if ( ! fileID.SetByFullPath( fullPath ) )
		return kVCOMError_Failed;

	outValue	= fileID.ExistsOnDisk();

	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::GetFileFullPath(TXString& outPath)
{
	ASSERTN( kEveryone, fRefCnt > 0 );

	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	outPath	= this->GetFileFullPath();

	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::GetFileName(TXString& outName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	outName = fFileName;
	
	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::GetFileSize (size_t& outSize)
{
	TXString fullPath	= this->GetFileFullPath();
	VCOMError result	= kVCOMError_NoError;
	bool fileExist		= false;

#if GS_MAC
	// the name is in posix format,
	// so we need to change ':' symbol to '/'
	fullPath.Replace(":", "/");
#endif
	
	this->ExistsOnDisk ( fileExist );

	if ( fileExist == false )
	{
		result = kVCOMError_Failed;
	}
	else
	{
		struct stat st;
		if ( stat ( fullPath, &st ) != 0 )
		{
			result = kVCOMError_Failed;
		}
		else
		{
			outSize = st.st_size;
		}
	}

	return result;
}

VCOMError CFileIdentifier::SetFileName(const TXString& name)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;
	if ( name.IsEmpty() )
		return kVCOMError_InvalidArg;

	VCOMError		error		= kVCOMError_NoError;

	fFileName		= name;
	CFileIdentifier::ValidateName( fFileName );

	return error;
}

VCOMError CFileIdentifier::GetFileExtension(TXString& outExtension)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString fullPath = this->GetFileFullPath();
	TFileIdentifier tFileID(fullPath);
	
	outExtension = tFileID.GetFileExtension();

	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::SetFileExtension(const TXString& extension)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;
	if ( extension.IsEmpty() )
		return kVCOMError_InvalidArg;

	ptrdiff_t		at		= fFileName.ReverseFind( '.' );
	if ( at >= 0 ) {
		TXString	name	= fFileName.Left( at );
		fFileName			= name;
	}

	fFileName			+= '.';
	if ( extension.GetAt( 0 ) != '.' ) {
		fFileName			+= extension;
	}

	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::GetFileNameWithoutExtension(TXString& outName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString fullPath = this->GetFileFullPath();
	TFileIdentifier tFileID(fullPath);
	
	outName	= tFileID.GetFileNameWithoutExtension();
	CFileIdentifier::ConvertFilename( outName );

	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::GetFolder(IFolderIdentifier** ppOutParentFolderID)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	if ( ppOutParentFolderID == NULL )
		return kVCOMError_InvalidArg;

	if ( *ppOutParentFolderID ) {
		(*ppOutParentFolderID)->Release();
		*ppOutParentFolderID = NULL;
	}

	
	VCOMError	error	= VWQueryInterface( IID_FolderIdentifier, (IVWUnknown**) ppOutParentFolderID );
	if ( error != kVCOMError_NoError ) 
		return kVCOMError_Failed;

	CFolderIdentifier*	pParentFolder	= static_cast<CFolderIdentifier*>( *ppOutParentFolderID );
	if ( pParentFolder == NULL )
		return kVCOMError_Failed;

	TXString	fullPath		= fFolderID.GetFullPath();
	pParentFolder->SetFullPath( fullPath );

	return kVCOMError_NoError;
}

VCOMError CFileIdentifier::GetAttributes(SAttributes& outAttributes)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFileFullPath();

	TFileIdentifier	fileID;
	if ( ! fileID.SetByFullPath( fullPath ) )
		return kVCOMError_Failed;

	VCOMError			error	= kVCOMError_Failed;
	StorageAttributes	attr;
	if ( fileID.GetFileContextAttributes( attr ) ) {
		//Determine if the permission flags are valid.
		const bool		bPermissionFlagsAreValid = (attr & kStorageAttrPermFlagsValid) == kStorageAttrPermFlagsValid;
		
		//Determine if the file is read-only. In order for
		//a file to be read only, it must have file read
		//attributes and permissions, and it must not
		//have all file write attributes or permissions.
		const StorageAttributes	kReadMask		= kStorageAttrRead | (bPermissionFlagsAreValid ? kStorageAttrPermRead : 0);
		const StorageAttributes kWriteMask		= kStorageAttrWrite | (bPermissionFlagsAreValid ? kStorageAttrPermWrite : 0);

		outAttributes.fbReadOnly		= fileID.IsFileReadOnly();
		outAttributes.fbHidden			= (attr & kStorageAttrHidden) == kStorageAttrHidden;
		outAttributes.fbSystem			= (attr & kStorageAttrSystem) == kStorageAttrSystem;
		outAttributes.fbTemporary		= (attr & kStorageAttrTemporary) == kStorageAttrTemporary;
		outAttributes.fbEncrypted		= (attr & kStorageAttrEncrypted) == kStorageAttrEncrypted;
		outAttributes.fbArchive			= (attr & kStorageAttrArchive) == kStorageAttrArchive;
		outAttributes.fbDirectory		= (attr & kStorageAttrDirectory) == kStorageAttrDirectory;
		outAttributes.fbCanRead			= (attr & kReadMask) == kReadMask;
		outAttributes.fbCanWrite		= (attr & kWriteMask) == kWriteMask;
		outAttributes.fbCanExecute		= bPermissionFlagsAreValid == (attr & kStorageAttrPermExecute);
		outAttributes.fbCanBrowse		= bPermissionFlagsAreValid == (attr & kStorageAttrPermBrowse);

		error	= kVCOMError_NoError;
	}

	return error;
}

VCOMError CFileIdentifier::SetAttributes(const SAttributes& attributes)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	return kVCOMError_NotImplemented;
}

VCOMError CFileIdentifier::GetAttributesTimeDateReference(EAttributesTimeReference ref, SAttributesDateTime& outData)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFileFullPath();

	TFileIdentifier	fileID;
	if ( ! fileID.SetByFullPath( fullPath ) )
		return kVCOMError_Failed;

	VCOMError	error	= kVCOMError_Failed;
	TXBaseStorageAccess*		storageAccess	= TStorageAccessFactory::CreateStorageAccess( fileID );
	if ( storageAccess )
	{
		TXBaseStorageAccess::EStorageTimeReference	storageTimeRef;
		switch ( ref )
		{
			case eAttributesTimeReference_Created:			storageTimeRef = TXBaseStorageAccess::eStorageTimeCreated;		break;
			case eAttributesTimeReference_LastAccessed:		storageTimeRef = TXBaseStorageAccess::eStorageTimeLastAccessed; break;
			case eAttributesTimeReference_LastWritten:		storageTimeRef = TXBaseStorageAccess::eStorageTimeLastWritten;	break;
			case eAttributesTimeReference_LastBackup:		storageTimeRef = TXBaseStorageAccess::eStorageTimeLastBackup;	break;
			default:										storageTimeRef = TXBaseStorageAccess::eStorageTimeCreated;		break;
		}

		TDateTimeData	storateTimeData;
		if ( storageAccess->GetStorageElementTimeData( storageTimeRef, storateTimeData ) == TXBaseStorageAccess::eStorageSuccess )
		{
			outData.fYear		= storateTimeData.fYear;
			outData.fMonth		= storateTimeData.fMonth;
			outData.fDay		= storateTimeData.fDay;
			outData.fHour		= storateTimeData.fHour;
			outData.fMinute		= storateTimeData.fMinute;
			outData.fSecond		= storateTimeData.fSecond;

			error	= kVCOMError_NoError;
		}
		
		delete storageAccess;
	}

	return error;
}

VCOMError CFileIdentifier::SetAttributesTimeDateReference(EAttributesTimeReference ref, const SAttributesDateTime& data)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	return kVCOMError_NotImplemented;
}

VCOMError CFileIdentifier::DeleteOnDisk()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFileFullPath();

	TFileIdentifier	fileID;
	if ( ! fileID.SetByFullPath( fullPath ) )
		return kVCOMError_Failed;

	VCOMError			error	= kVCOMError_Failed;
	if ( fileID.ExistsOnDisk() ) {
		if ( fileID.DeleteOnDisk() ) {
			error	= kVCOMError_NoError;
		}
	}
	else {
			error	= kVCOMError_NoError;
	}

	return error;
}

VCOMError CFileIdentifier::RenameOnDisk(const TXString& newName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFileFullPath();

	TFileIdentifier	fileID;
	if ( ! fileID.SetByFullPath( fullPath ) )
		return kVCOMError_Failed;

	TXString		theNewName	= newName;
	
#if GS_MAC
	// posfix path ':' symbol represents '/' symbol
	theNewName.Replace(":", "/");
#endif

	CFileIdentifier::ValidateFilename( theNewName );
	CFileIdentifier::ConvertFilename( theNewName );
	
#ifndef _WINDOWS
	// renaing requires the name to contain '/' instead of ':' that will become slash
	theNewName.Replace(":", "/");
#endif

	VCOMError			error	= kVCOMError_Failed;
	if ( fileID.RenameOnDisk( theNewName ) ) {
		error		= kVCOMError_NoError;

		fFileName	= newName;
#ifndef _WINDOWS
		// posfix path ':' symbol represents '/' symbol
		fFileName.Replace(":", "/");
#endif
		CFileIdentifier::ValidateName( fFileName );
	}

	return error;
}

VCOMError CFileIdentifier::DuplicateOnDisk(IFileIdentifier *pDestFileID, bool bOverwrite)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	CFileIdentifier	*destinationFile = static_cast<CFileIdentifier*>( pDestFileID );
	if ( destinationFile == NULL )
		return kVCOMError_InvalidArg;

	TXString					destinationPath		= destinationFile->GetFileFullPath();
	TXString					sourePath			= this->GetFileFullPath();
	TFileIdentifier				soureFileID;
	TFileIdentifier				destinationFileID;
	
	if ( !soureFileID.SetByFullPath( sourePath ) || 
		 !destinationFileID.SetByFullPath( destinationPath ) )
		return kVCOMError_Failed;

	VCOMError			error	= kVCOMError_Failed;
	if ( soureFileID.DuplicateOnDisk( destinationFileID, bOverwrite ) ) {
		error	= kVCOMError_NoError;
	}

	return error;
}

VCOMError CFileIdentifier::LaunchInOS()
{ 
//	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFileFullPath();

	TFileIdentifier	fileID;
	if ( ! fileID.SetByFullPath( fullPath ) )
		return kVCOMError_Failed;

	VCOMError			error	= kVCOMError_Failed;
	if ( fileID.LaunchInOS() ) {
		error	= kVCOMError_NoError;
	}

	return error;
}

VCOMError CFileIdentifier::RevealInOS()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFileFullPath();

	TFileIdentifier	fileID;
	if ( ! fileID.SetByFullPath( fullPath ) )
		return kVCOMError_Failed;

	return fileID.RevealInOS();
}

VCOMError CFileIdentifier::FormatFilename(TXString& formatName, Uint16 maxCharsWithoutSpace)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFileFullPath();
	formatName = ::FormatFilename( fullPath, DemoteTo<short>( kEveryone, maxCharsWithoutSpace ) );

	return kVCOMError_NoError;	
}

VCOMError CFileIdentifier::ValidateName(TXString& outName) 
{
	ValidateFilename(outName);
	return kVCOMError_NoError;	
}

/*static*/ void CFileIdentifier::ValidateFilename(TXString& outName)
{
	// validate OS file name
#ifdef _WINDOWS
	// Windows doesn't accept symbols
	// \ / : * ? " < > |
	outName.Replace( "\\", 	"%2F" );
	outName.Replace( "/", 	"%5C" );
	outName.Replace( ":", 	"%3A" );
	outName.Replace( "*", 	"%2A" );
	outName.Replace( "?", 	"%3F" );
	outName.Replace( "\"",	"%22" );
	outName.Replace( "<", 	"%3C" );
	outName.Replace( ">", 	"%3E" );
	outName.Replace( "|", 	"%7C" );
#else
	// Mac doesnt accept symbols
	// / :
	outName.Replace("/", "%5C");
	outName.Replace(":", "%3A");
#endif
}

/*static*/ void CFileIdentifier::ConvertFilename(TXString& outName)
{
#ifdef _WINDOWS
#else
	// Mac allowes those symbols to be the in the name
	outName.Replace("%2F",	"\\");
	outName.Replace("%2A",	"*"	);
	outName.Replace("%3F",	"?"	);
	outName.Replace("%22",	"\"");
	outName.Replace("%3C",	"<"	);
	outName.Replace("%3E",	">" );
	outName.Replace("%7C",	"|" );
	
	outName.Replace("%5C",  ":" );
#endif
}

