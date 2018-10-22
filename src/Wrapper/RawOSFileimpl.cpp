#include "Prefix/StdAfx.h"

#include "RawOSFileimpl.h"

CRawOSFileImpl::CRawOSFileImpl()
	: fTheFile( nullptr )
{
}

CRawOSFileImpl::~CRawOSFileImpl()
{
}

VCOMError CRawOSFileImpl::Open(VectorWorks::Filing::IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting)
{
	if ( pFileID == nullptr )
		return kVCOMError_InvalidArg;

	TXString	filePath;
	pFileID->GetFileFullPath( filePath );

	     if ( bReadable == true  && bWritable == false )		fTheFile = std::fopen( filePath, "rb" );
	else if ( bReadable == false && bWritable == true  )		fTheFile = std::fopen( filePath, bTruncateExisting ? "ab" : "wb" );
	else if ( bReadable == true  && bWritable == true  )		fTheFile = std::fopen( filePath, bTruncateExisting ? "wb+" : "ab+" );

	return fTheFile ? kVCOMError_NoError : kVCOMError_Failed;;
}

VCOMError CRawOSFileImpl::Close()
{
	if ( fTheFile )
	{
		std::fclose( fTheFile );
		fTheFile = NULL;
	}

	return kVCOMError_NoError;
}

VCOMError CRawOSFileImpl::GetFileSize(Uint64& outValue)
{
	if ( fTheFile == nullptr )
		return kVCOMError_NotInitialized;

	VCOMError result = kVCOMError_Failed;

	// get the position of the end
	// we dont care about chaning the position as this class requires possition when reading/writing
	if ( std::fseek( fTheFile, 0, SEEK_END ) == 0 )
	{
		outValue = std::ftell( fTheFile );
		result = kVCOMError_NoError;
	}

	return result;
}

VCOMError CRawOSFileImpl::Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer)
{
	if ( fTheFile == nullptr )
		return kVCOMError_NotInitialized;

	VCOMError result = kVCOMError_Failed;
	if ( std::fseek( fTheFile, DemoteTo<long>(kEveryone, position), SEEK_SET ) == 0 )
	{

		Uint64 read = std::fread( pOutBuffer, 1, inoutSize, fTheFile );
		ASSERTN(kEveryone, read == inoutSize);

		inoutSize = read;
		return kVCOMError_NoError;
		
	}

	return result;
}

VCOMError CRawOSFileImpl::Write(Uint64 position, Uint64 size, const void* pBuffer)
{
	if ( fTheFile == nullptr )
		return kVCOMError_NotInitialized;

	VCOMError result = kVCOMError_Failed;
	if ( std::fseek( fTheFile, DemoteTo<long>(kEveryone, position), SEEK_SET ) == 0 )
	{
		size_t written = std::fwrite( pBuffer, 1, size, fTheFile );
		if ( written == size )
			result = kVCOMError_NoError;
	}

	return result;
}

