//
// Copyright  Diehl Graphsoft, Inc. 2006.
// All Rights Reserved.
// 

#include "Prefix/StdAfx.h"	// Must be first non-comment line.  See StdHeaders.h for explanation.

#include "FolderIdentifier.h"
#include "FileIdentifier.h"
#include "UTranslateFiles.h"
//#include "Include/ApplicationFolders.h"
#include "FilingWrapper.h"

#include "FolderSpecifiers.h"


#if defined(_WINDOWS)
	#include <ShlObj.h>
#elif _LINUX
	#include <sys/stat.h>
	#include <dirent.h>
#endif


using namespace VectorworksMVR::Filing;

// ----------------------------------------------------------------------------------------------------
CFolderIdentifier::CFolderIdentifier()
{
	
}

CFolderIdentifier::~CFolderIdentifier()
{
	farrFolderHierarchy.clear();
}


VCOMError CFolderIdentifier::SetFullPath(const TXString& fullPath)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	farrFolderHierarchy.clear();
	if ( fullPath.IsEmpty() )
		return kVCOMError_Failed;

	// determine if the passed fullPath is windows (containing backward slash)
	// or posix so we would know how to split the path into it's subfolders
	bool	bIsWinPath		= false;
#ifdef _WINDOWS
	if ( fullPath.GetLength() >= 2 && fullPath[1] == ':' ) {
		bIsWinPath		= true;
	}
	else {
#else
	{
#endif
		ptrdiff_t	at			= fullPath.Find( '\\' ); 
		ptrdiff_t	at1			= fullPath.Find( '/' ); 
		if (	(at == -1 && at1 != -1)
			||	(at1 != -1 && at != -1 && at1 < at) )
		{
			bIsWinPath		= false;
		}
		else {
			bIsWinPath		= true;
		}
	}

	TXString	theFullPath	= fullPath;

#ifndef _WINDOWS
	{
		// cut off everything before '/' or or '\' from the path
		// Mac paths are in the posix form: /Folder1/Folder2/...
		char	firstCh	= theFullPath.GetAt( 0 );
		if ( firstCh != '/' && firstCh != '\\' && firstCh != ':' ) {
			int				at			= theFullPath.Find( '\\', 0 );
			int				at1			= theFullPath.Find( '/', 0 );
			if ( at < 0 )						at			= at1;
			else if ( at1 >= 0 && at1 < at )	at			= at1;

			if ( at >= 0 ) {
				TXString	path	= theFullPath.Mid( at );
				theFullPath			= path;
			}
		}
	}
#else
	// if it is a network path add one '\' to denote this
	if ( bIsWinPath ) {
		if ( theFullPath.GetLength() >= 2 && theFullPath.Left(2) == "\\\\" ) {
			farrFolderHierarchy.push_back( "\\" );
	
		}
	}
	else {
		if ( theFullPath.GetLength() >= 2 && theFullPath.Left(2) == "//" ) {
			farrFolderHierarchy.push_back( "\\" );
	
		}
	}
#endif

	theFullPath				+= bIsWinPath ? "\\" : "/";


	// ensure proper POSIX path files for in the root
	if ( ! bIsWinPath && theFullPath.GetLength() > 0 && theFullPath.GetAt(0) == '/' ) {
		if ( farrFolderHierarchy.size() == 0 ) {
			// put an empty holder so if we have files in root
			// the hierarchy will not be empty
			farrFolderHierarchy.push_back( "" );
		}
	}
	
	// prepare array folder hierarchy
	// we will process it later into farrFolderHierarchy
	// so we could remove any '..' in the path
	TXStringArray	arrFolderHierarchy;

	ptrdiff_t		start		= 0;

	VCOMError		error		= kVCOMError_Failed;
	while( true ) {
		ptrdiff_t				at;
		if ( bIsWinPath ) {
			at	= theFullPath.Find( '\\', start );
		}
		else {
			at	= theFullPath.Find( '/', start );
		}

		if ( at < 0 )	break;

		TXString		strPart		= theFullPath.Mid( start, at - start );
		start						= at + 1;

		if ( ! strPart.IsEmpty() ) {
			bool	bIsWinDevice	= false;
#ifdef _WINDOWS
			bIsWinDevice	= strPart.GetLength() == 2 && strPart[1] == ':';
#endif
			if ( ! bIsWinDevice ) {
				if ( ! bIsWinPath ) {
					// in posix paths ':' is used to represent '/' symbol
					strPart.Replace(":", "/");
				}
				
				CFolderIdentifier::ValidateName( strPart );
			}

			arrFolderHierarchy.push_back( strPart );
		}

		error				= kVCOMError_NoError;
	}

	if ( VCOM_SUCCEEDED( error ) ) {
		size_t	len		= arrFolderHierarchy.size(); 
		for(size_t i=0; i<len; i++) {
			const TXString&	pathPiece	= arrFolderHierarchy[ i ];
			if ( pathPiece != ".." ) {
				farrFolderHierarchy.push_back( pathPiece );
			}
			else {
				// we have relative path piece, move back in the folder hierarchy
				size_t	folderPiecesCnt	= farrFolderHierarchy.size();
				if ( folderPiecesCnt > 0 ) {
					farrFolderHierarchy.pop_back();
				}
			}
		}
	}

	return error;
}

TXString CFolderIdentifier::GetFullPath() const
{
	TXString	fullPath;

#ifdef _WINDOWS
	const char	kFolderSeparator			= '\\';
#else
	const char	kFolderSeparator			= '/';
	fullPath								= "/";
#endif

	size_t			count		= farrFolderHierarchy.size();
	for(size_t i=0; i<count; i++) {
		TXString		strPart	= farrFolderHierarchy.at( i );

#ifdef _WINDOWS
		bool	bIsWinDevice	= false;
		bIsWinDevice	= strPart.GetLength() == 2 && strPart[1] == ':';
#endif
		
		CFolderIdentifier::ConvertFoldername( strPart );

		if ( ! strPart.IsEmpty() ) {
			fullPath				+= strPart;
			fullPath				+= kFolderSeparator;
		}
	}

	return fullPath;
}

VCOMError CFolderIdentifier::Set(const TXString& fullPath)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fullPath.IsEmpty() )
		return kVCOMError_InvalidArg;

	return this->SetFullPath( fullPath );
}

				
VCOMError CFolderIdentifier::Set(EFolderSpecifier folderSpec, bool bUserFolder)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	FolderSpecifier innerFolderSpec	= bUserFolder ? -folderSpec : folderSpec;
	if ( innerFolderSpec == 0 )
		return kVCOMError_InvalidArg;

	VCOMError	error	= kVCOMError_Failed;
 	TFolderIdentifier	folder;
 	if ( GetFolderWithSpecifer( (EFolderSpecifier) innerFolderSpec, folder, true /*inCreateIfMissing*/ ) ) {
 #if GS_WIN
 		error	= this->SetFullPath( folder.GetFolderPath() );
 #else
         error   = this->SetFullPath( folder.GetPosixFolderPath());
 #endif
 	}

	return error;
}

VCOMError CFolderIdentifier::Set(EFolderSpecifier folderSpec, bool bUserFolder, const TXString& subFolderName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->Set( folderSpec, bUserFolder ) ) )
		return kVCOMError_Failed;

	TXString		fullPath	= this->GetFullPath();

	TXString		theSubFolderName	= subFolderName;
#ifdef _WINDOWS
	theSubFolderName.Replace( "/", "\\" );
#endif

	fullPath					+= theSubFolderName;

	return this->SetFullPath( fullPath );
}

VCOMError CFolderIdentifier::Set(IFolderIdentifier* pParentFolder, const TXString& folderName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( pParentFolder == NULL || folderName.IsEmpty() )
		return kVCOMError_InvalidArg;

	CFolderIdentifier*	pParent	= static_cast<CFolderIdentifier*>( pParentFolder );
	if ( pParent == NULL || pParent->farrFolderHierarchy.size() <= 0 )
		return kVCOMError_InvalidArg;

	TXString		fullPath	= pParent->GetFullPath();

	TXString		theFolderName	= folderName;
#ifdef _WINDOWS
	theFolderName.Replace( "/", "\\" );
#endif

	fullPath					+= theFolderName;
	
	return this->SetFullPath( fullPath );
}

VCOMError CFolderIdentifier::Clear()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	farrFolderHierarchy.clear();
	return kVCOMError_NoError;
}

VCOMError CFolderIdentifier::IsSet()
{
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	return farrFolderHierarchy.size() > 0 ? kVCOMError_NoError : kVCOMError_Failed;
}

VCOMError CFolderIdentifier::ExistsOnDisk(bool& outValue)
{
	outValue	= false;

	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_NotInitialized;

	TXString	fullPath	= this->GetFullPath();
    outValue				= TFolderIdentifier::ExistsOnDisk( fullPath ) == TFolderIdentifier::eFolderExists;

	return kVCOMError_NoError;
}

VCOMError CFolderIdentifier::GetFullPath(TXString& outPath)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_BadPathSpecified;

	outPath		= this->GetFullPath();

	return kVCOMError_NoError;
}

VCOMError CFolderIdentifier::GetName(TXString& outName)
{
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_BadPathSpecified;
	
	outName	= farrFolderHierarchy.at( farrFolderHierarchy.size() - 1 );

	CFolderIdentifier::ConvertFoldername( outName );

#ifndef _WINDOWS
	// the name is in posix format,
	// so we need to change ':' symbol to '/'
	outName.Replace( ":", "/" );
#endif

	return kVCOMError_NoError;
}

VCOMError CFolderIdentifier::GetParentFolder(IFolderIdentifier** ppOutParentFolderID)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_Failed;

	if ( ppOutParentFolderID == NULL )
		return kVCOMError_InvalidArg;

	if ( *ppOutParentFolderID ) {
		(*ppOutParentFolderID)->Release();
		*ppOutParentFolderID = NULL;
	}

	VCOMError	error	= ::VWQueryInterface( IID_FolderIdentifier, (IVWUnknown**) ppOutParentFolderID );
	if ( error != kVCOMError_NoError )
		return error;

	CFolderIdentifier*	pParentFolder	= static_cast<CFolderIdentifier*>( *ppOutParentFolderID );
	if ( pParentFolder == NULL )
		return kVCOMError_Failed;

	pParentFolder->farrFolderHierarchy.clear();

	size_t		len		= farrFolderHierarchy.size();
	for(size_t i=0; i<len-1; i++) {
		const TXString&	strPart		= farrFolderHierarchy.at( i );
		pParentFolder->farrFolderHierarchy.push_back( strPart );
	}

	return kVCOMError_NoError;
}

VCOMError CFolderIdentifier::GetAttributes(SAttributes& outAttributes)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_Failed;

	const TXString&		fullPath	= this->GetFullPath();
	if ( TFolderIdentifier::ExistsOnDisk( fullPath ) == TFolderIdentifier::eFolderDoesNotExists )
		return kVCOMError_FileNotFound;

	TFolderIdentifier	folderID;
	if ( ! folderID.SetByFullPath( fullPath ) )
		return kVCOMError_BadPathSpecified;

	VCOMError			error	= kVCOMError_Failed;
	StorageAttributes	attr;
	if ( folderID.GetFolderContextAttributes( attr ) ) {
		//Determine if the permission flags are valid.
		const bool		bPermissionFlagsAreValid = (attr & kStorageAttrPermFlagsValid) == kStorageAttrPermFlagsValid;
		
		//Determine if the file is read-only. In order for
		//a file to be read only, it must have file read
		//attributes and permissions, and it must not
		//have all file write attributes or permissions.
		const StorageAttributes	kReadMask		= kStorageAttrRead | (bPermissionFlagsAreValid ? kStorageAttrPermRead : 0);
		const StorageAttributes kWriteMask		= kStorageAttrWrite | (bPermissionFlagsAreValid ? kStorageAttrPermWrite : 0);

		outAttributes.fbReadOnly		= folderID.IsFolderReadOnly();
		outAttributes.fbHidden			= (attr & kStorageAttrHidden) == kStorageAttrHidden;
		outAttributes.fbSystem			= (attr & kStorageAttrSystem) == kStorageAttrSystem;
		outAttributes.fbTemporary		= (attr & kStorageAttrTemporary) == kStorageAttrTemporary;
		outAttributes.fbEncrypted		= (attr & kStorageAttrEncrypted) == kStorageAttrEncrypted;
		outAttributes.fbArchive			= (attr & kStorageAttrArchive) == kStorageAttrArchive;
		outAttributes.fbDirectory		= (attr & kStorageAttrDirectory) == kStorageAttrDirectory;
		outAttributes.fbCanRead			= (attr & kReadMask) == kReadMask;
		outAttributes.fbCanWrite		= (attr & kWriteMask) == kWriteMask;
		outAttributes.fbCanExecute		= bPermissionFlagsAreValid && (attr & kStorageAttrPermExecute);
		outAttributes.fbCanBrowse		= bPermissionFlagsAreValid && (attr & kStorageAttrPermBrowse);

		error	= kVCOMError_NoError;
	}

	return error;
}

VCOMError CFolderIdentifier::SetAttributes(const SAttributes& attributes)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_Failed;

	return kVCOMError_NotImplemented;
}

VCOMError CFolderIdentifier::GetAttributesTimeDateReference(EAttributesTimeReference ref, SAttributesDateTime& outData)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_Failed;

	const TXString&		fullPath	= this->GetFullPath();
	if ( TFolderIdentifier::ExistsOnDisk( fullPath ) == TFolderIdentifier::eFolderDoesNotExists )
		return kVCOMError_FileNotFound;

	TFolderIdentifier	folderID;
	if ( ! folderID.SetByFullPath( fullPath ) )
		return kVCOMError_BadPathSpecified;

	VCOMError	error	= kVCOMError_Failed;
	TXBaseStorageAccess*		storageAccess	= TStorageAccessFactory::CreateStorageAccess( folderID );
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
	}

	return error;
}

VCOMError CFolderIdentifier::SetAttributesTimeDateReference(EAttributesTimeReference ref, const SAttributesDateTime& data)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_Failed;

	return kVCOMError_NotImplemented;

}

#if defined(_WINDOWS)
bool CFolderIdentifier::EnumerateContentsHandler(IFolderContentListener* pListener, const CFolderIdentifier& folder, bool bReqursive, VCOMError& outError)
{
	outError		= kVCOMError_Failed;
	bool	bStop	= false;
	if ( pListener == NULL ) {
		outError	= kVCOMError_InvalidArg;
		bStop		= true;
	}
	else {
		outError						= kVCOMError_NoError;

		TXString	rootFolder			= folder.GetFullPath();
		TXString	searchFilter		= rootFolder + "*.*"; // all files
		
		WIN32_FIND_DATA	nextFindInfo;
		HANDLE			hFindContext	= ::FindFirstFile( (LPCTSTR) searchFilter, & nextFindInfo );
		Boolean			bMoreFiles		= hFindContext != INVALID_HANDLE_VALUE;
		while( bMoreFiles )		// this only prepares to retrieve the files
								// this actually retrieves the file info
		{
			bool		bIsDots		= false;
			if ( nextFindInfo.cFileName[0] == '.' ) {
				if (nextFindInfo.cFileName[1] == '\0' || 
					(nextFindInfo.cFileName[1] == '.' && nextFindInfo.cFileName[2] == '\0'))
				{
					bIsDots = true;
				}
			}

			if ( ! bIsDots ) {
				TXString	fullPath	= rootFolder;
				fullPath				+= nextFindInfo.cFileName;

				if ( nextFindInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
					IFolderIdentifier*	pFolderID	= NULL;
					VCOMError			error		= VWQueryInterface( IID_FolderIdentifier, (IVWUnknown**) & pFolderID );
					if ( error == kVCOMError_NoError ) {
						CFolderIdentifier*	pFolderInst	= static_cast<CFolderIdentifier*>( pFolderID );
						if ( pFolderInst ) {
							pFolderInst->SetFullPath( fullPath );

							EFolderContentListenerResult result = pListener->OnFolderContent( pFolderID );
							if ( result == eFolderContentListenerResult_StopNoError ) {
								outError		= kVCOMError_Failed;
								bStop			= true;
								break;
							}
							else if ( result == eFolderContentListenerResult_StopError ) {
								outError		= kVCOMError_NoError;
								bStop			= true;
								break;
							}
						}

						pFolderID->Release();
					}
					/*TODO
					// go to seach this folder if the use requires
					if ( bReqursive ) {
						CFolderIdentifier subFolder( fullPath );
						bStop	= this->EnumerateContentsHandler( pListener, subFolder, bReqursive, outError );
						if ( bStop ) {
							break;
						}
					}
					*/
				}
				else {
					IFileIdentifier*	pFileID		= NULL;
					VCOMError			error		= VWQueryInterface( IID_FileIdentifier, (IVWUnknown**) & pFileID );
					if ( error == kVCOMError_NoError ) {
						CFileIdentifier*	pFileInst	= static_cast<CFileIdentifier*>( pFileID );
						if ( pFileInst ) {
							pFileInst->SetFileFullPath( fullPath );

							EFolderContentListenerResult result = pListener->OnFileContent( pFileID );
							if ( result == eFolderContentListenerResult_StopNoError ) {
								outError		= kVCOMError_NoError;
								bStop			= true;
								break;
							}
							else if ( result == eFolderContentListenerResult_StopError ) {
								outError		= kVCOMError_Failed;
								bStop			= true;
								break;
							}
						}

						pFileID->Release();
					}
				}
			}

			// ok, next
			bMoreFiles	= 	::FindNextFile( hFindContext, & nextFindInfo );
		}

		::FindClose( hFindContext );
	}

	return bStop;
}
#elif _LINUX
bool CFolderIdentifier::EnumerateContentsHandler(IFolderContentListener* pListener, const CFolderIdentifier& folder, bool bReqursive, VCOMError& outError)
{
	// LINUX_IMPLEMENTATION - done
	outError		= kVCOMError_Failed;
	bool	bStop	= false;
	if ( pListener == NULL ) {
		outError	= kVCOMError_InvalidArg;
		bStop		= true;
	}
	else {
		outError						= kVCOMError_NoError;

		TXString	rootFolder			= folder.GetFullPath();

		DIR* dp = opendir( rootFolder.operator const char*() );
		if ( dp )
		{
			struct dirent* dirp = readdir( dp );
			while ( dirp )
			{
				bool		bIsDots		= false;
				if ( dirp->d_name[0] == '.' ) {
					if (dirp->d_name[1] == '\0' ||
						(dirp->d_name[1] == '.' && dirp->d_name[2] == '\0'))
					{
						bIsDots = true;
					}
				}

				if ( ! bIsDots ) {
					TXString	fullPath	= rootFolder;
					fullPath				+= dirp->d_name;

					struct stat sb;
					if ( stat(fullPath.GetCharPtr(), &sb) == 0 && S_ISDIR(sb.st_mode) )
					{
						IFolderIdentifier*	pFolderID	= NULL;
						VCOMError			error		= ::VWQueryInterface( IID_FolderIdentifier, (IVWUnknown**) & pFolderID );
						if ( error == kVCOMError_NoError ) {
							CFolderIdentifier*	pFolderInst	= static_cast<CFolderIdentifier*>( pFolderID );
							if ( pFolderInst ) {
								pFolderInst->SetFullPath( fullPath );

								EFolderContentListenerResult result = pListener->OnFolderContent( pFolderID );
								if ( result == eFolderContentListenerResult_StopNoError )
								{
									outError		= kVCOMError_Failed;
									bStop			= true;
									break;
								}
								else if ( result == eFolderContentListenerResult_StopError )
								{
									outError		= kVCOMError_NoError;
									bStop			= true;
									break;
								}
							}

							pFolderID->Release();
						}

						// go to seach this folder if the use requires
						/*
						TODO
						if ( bReqursive )
						{
							TFolderIdentifier subFolder( fullPath );
							bStop	= this->EnumerateContents( pListener, subFolder, bReqursive, outError );
							if ( bStop )
							{
								break;
							}
						}
						*/
					}
					else {
						IFileIdentifier*	pFileID		= NULL;
						VCOMError			error		= VWQueryInterface( IID_FileIdentifier, (IVWUnknown**) & pFileID );
						if ( error == kVCOMError_NoError ) {
							CFileIdentifier*	pFileInst	= static_cast<CFileIdentifier*>( pFileID );
							if ( pFileInst ) {
								pFileInst->SetFileFullPath( fullPath );

								EFolderContentListenerResult result = pListener->OnFileContent( pFileID );
								if ( result == eFolderContentListenerResult_StopNoError ) {
									outError		= kVCOMError_NoError;
									bStop			= true;
									break;
								}
								else if ( result == eFolderContentListenerResult_StopError ) {
									outError		= kVCOMError_Failed;
									bStop			= true;
									break;
								}
							}

							pFileID->Release();
						}
					}
				}
			}

			closedir( dp );
		}
	}

	return bStop;
}
#endif

VCOMError CFolderIdentifier::EnumerateContents(IFolderContentListener* pListener, bool bReqursive)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( pListener == NULL )
		return kVCOMError_InvalidArg;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_NotInitialized;

	const TXString&		fullPath	= this->GetFullPath();
    if ( TFolderIdentifier::ExistsOnDisk( fullPath ) == TFolderIdentifier::eFolderDoesNotExists )
		return kVCOMError_FileNotFound;

	TFolderIdentifier	folder;
	if ( ! folder.SetByFullPath( fullPath ) )
		return kVCOMError_BadPathSpecified;

	VCOMError		error	= kVCOMError_NoError;
	//if ( this->EnumerateContentsHandler( pListener, folder, bReqursive, error ) ) {
		//enumeration has been stopped!
		 //the enumeration return the 'error'
		// TODO
	//}
	
	return error;
}

namespace VectorworksMVR
{
	namespace Filing
	{
		class CCallbackFolderContentListener : public IFolderContentListener
		{
		public:
			CCallbackFolderContentListener(TFolderContentCallback_Folder folderCallback, TFolderContentCallback_File fileCallback)
				: fFolderCallback( folderCallback ), fFileCallback( fileCallback )
			{
			}

			virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFolderContent(IFolderIdentifier* folderID)
			{
				return fFolderCallback ? fFolderCallback( folderID ) : eFolderContentListenerResult_Continue;
			}

			virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFileContent(IFileIdentifier* fileID)
			{
				return fFileCallback ? fFileCallback( fileID ) : eFolderContentListenerResult_Continue;
			}

		private:
			TFolderContentCallback_Folder	fFolderCallback;
			TFolderContentCallback_File		fFileCallback;
		};
	}
}

VCOMError CFolderIdentifier::EnumerateContents(TFolderContentCallback_Folder folderCallback, TFolderContentCallback_File fileCallback, bool bReqursive)
{
	CCallbackFolderContentListener	listener( folderCallback, fileCallback );
	return this->EnumerateContents( & listener, bReqursive );
}

VCOMError CFolderIdentifier::CreateOnDisk()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_NotInitialized;

	const TXString&		fullPath	= this->GetFullPath();

	TFolderIdentifier	folderID;
	VCOMError			error	= kVCOMError_Failed;
	if ( folderID.CreateOnDisk( fullPath ) ) {
		error	= kVCOMError_NoError;
	}

	return error;
}

VCOMError CFolderIdentifier::DeleteOnDisk()
{
	typedef std::vector<IFolderIdentifier*>	TFolderIdentifiersArray;
	typedef std::vector<IFileIdentifier*> TFileIdentifierArray;

	// listener for the content
	// this listener deletes all files and stores the empty folders
	class CDeleteFolderContentListener : public IFolderContentListener
	{
	public:
				CDeleteFolderContentListener(TFileIdentifierArray* pArrFileIDs, TFolderIdentifiersArray* pArrFolderIDs)
		{
			fpArrFileIDs	= pArrFileIDs;
			fpArrFolderIDs	= pArrFolderIDs;
		}
	
		virtual	~CDeleteFolderContentListener()
		{
		}
	
		virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFolderContent(IFolderIdentifier* pFolderID)
		{
			if ( pFolderID ) {
				pFolderID->AddRef();
				fpArrFolderIDs->push_back( pFolderID );
	
				CDeleteFolderContentListener	contentDeleteListener( fpArrFileIDs, fpArrFolderIDs );
				pFolderID->EnumerateContents( & contentDeleteListener, false );
			}
			return eFolderContentListenerResult_Continue;
		}
		
		virtual EFolderContentListenerResult VCOM_CALLTYPE	OnFileContent(IFileIdentifier* pFileID)
		{
			if ( pFileID ) {
				pFileID->AddRef();
				fpArrFileIDs->push_back( pFileID );
			}
			return eFolderContentListenerResult_Continue;
		}
		
	private:
		TFileIdentifierArray*			fpArrFileIDs;
		TFolderIdentifiersArray*		fpArrFolderIDs;	
	};
	

	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_BadPathSpecified;

	TXString		fullPath	= this->GetFullPath();
    if ( TFolderIdentifier::ExistsOnDisk( fullPath ) == TFolderIdentifier::eFolderDoesNotExists )
		return kVCOMError_FileNotFound;

	// enumerate the content of this folder
	// delete all files and return impty folder IDs so they can be deleted later
	TFileIdentifierArray			arrFileIDs;
	TFolderIdentifiersArray			arrFolderIDs;
	CDeleteFolderContentListener	contentDeleteListener( & arrFileIDs, & arrFolderIDs );
	this->EnumerateContents( & contentDeleteListener, false );
	
	// delete the stored files.
	// This is needed to prevent problems during enumerating
	// and deleting during iterating the contents
	size_t		filesCnt		= arrFileIDs.size();
	for(size_t i=0; i<filesCnt; i++) {
		IFileIdentifier*	pFileID		= arrFileIDs[ i ];
		pFileID->DeleteOnDisk();
		pFileID->Release();
	}

	// delete the stored folders. This is needed to be done at the end
	// because on Mac deleting a folder will not continue to enumerate folders correctly
	// That's why we delete them at the end, after enumeration is finished
	size_t		foldersCnt		= arrFolderIDs.size();
	for(size_t i=0; i<foldersCnt; i++) {
		IFolderIdentifier* pFolderID	= arrFolderIDs[ i ];
		pFolderID->DeleteOnDisk();
		pFolderID->Release();
	}

	VCOMError			error	= kVCOMError_Failed;
#ifdef _WINDOWS
	// on windows TFolderIdentifier::DeleteOnDisk sometimes doesn't work
	// due to 'folder read only', which is nonsence. In windows there is no folder read only!
	// so we just try to delete the folder
	if ( ::RemoveDirectory( fullPath ) ) {
		error	= kVCOMError_NoError;
	}
#else
	TFolderIdentifier	folderID;
	if ( ! folderID.SetByFullPath( fullPath ) )
		return kVCOMError_BadPathSpecified;

	if ( folderID.DeleteOnDisk() ) {
		error	= kVCOMError_NoError;
	}
#endif

	return error;
}

VCOMError CFolderIdentifier::RevealInOS()
{
//	ASSERTN(kJWarshaw, fRefCnt > 0);

	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_BadPathSpecified;

	const TXString&		fullPath	= this->GetFullPath();
    if ( TFolderIdentifier::ExistsOnDisk( fullPath ) == TFolderIdentifier::eFolderDoesNotExists )
		return kVCOMError_FileNotFound;

	TFolderIdentifier	folderID;
	if ( ! folderID.SetByFullPath( fullPath ) )
		return kVCOMError_BadPathSpecified;

	VCOMError			error	= kVCOMError_Failed;
	if (folderID.RevealInOS()) {
		error = kVCOMError_NoError;
	}

	return error;
}

VCOMError CFolderIdentifier::DuplicateOnDisk(IFolderIdentifier * newFolder, bool overrideIfNecessary, TXString * displayProgressDialog)
{
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( farrFolderHierarchy.size() <= 0 )
		return kVCOMError_NotInitialized;

	const TXString&		fullPath	= this->GetFullPath();
    if ( TFolderIdentifier::ExistsOnDisk( fullPath ) == TFolderIdentifier::eFolderDoesNotExists )
		return kVCOMError_FileNotFound;

	TFolderIdentifier	folderID;
	if ( ! folderID.SetByFullPath( fullPath ) )
		return kVCOMError_BadPathSpecified;

	CFolderIdentifier*	pDestFolder	= static_cast<CFolderIdentifier*>( newFolder );
	const TXString newPath = pDestFolder->GetFullPath();
	TFolderIdentifier	destFolderID;
	
	VCOMError			error	= kVCOMError_Failed;
	TXString txMsg("This is a test");
	destFolderID.SetByFullPath(newPath);
	if (folderID.DuplicateOnDisk(destFolderID, overrideIfNecessary, displayProgressDialog)) {
		error = kVCOMError_NoError;
	}

	return error;
}
VCOMError CFolderIdentifier::FormatFoldername(TXString& formatName, Uint16 maxCharsWithoutSpace)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( VCOM_FAILED( this->IsSet() ) )
		return kVCOMError_NotInitialized;

	TXString	fullPath		= this->GetFullPath();
	formatName = ::FormatFilename( fullPath, DemoteTo<short>( kEveryone, maxCharsWithoutSpace ) );

	return kVCOMError_NoError;	
}

VCOMError CFolderIdentifier::ValidateName(TXString& outName) 
{
	ValidateFoldername(outName);
	return kVCOMError_NoError;	
}

/*static*/ void CFolderIdentifier::ValidateFoldername(TXString& outName)
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
	outName.Replace( "/", 	"%5C" );
	outName.Replace( ":", 	"%3A" );
#endif
}

// This function is for conversion from Windows to Mac only.
/*static*/ void CFolderIdentifier::ConvertFoldername(TXString& outName)
{
#ifdef _WINDOWS
#else
	// Mac allowes those symbols to be the in the name
	outName.Replace( "%2F",	"\\" );
	outName.Replace( "%2A",	"*" );
	outName.Replace( "%3F",	"?" );
	outName.Replace( "%22",	"\"" );
	outName.Replace( "%3C",	"<" );
	outName.Replace( "%3E",	">" );
	outName.Replace( "%7C",	"|" );
    outName.Replace( "%5C", ":" );
#endif
}

	
