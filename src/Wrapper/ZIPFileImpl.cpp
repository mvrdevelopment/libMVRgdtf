#include "Prefix/StdAfx.h"

#include "ZIPFileImpl.h"

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wattributes"
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#ifdef GCC7_ERROR
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#endif

#ifdef DONT_INCLUDE_MINI_ZIP
#define MINIZ_HEADER_FILE_ONLY 1
#endif

#include "Minizip/Source/miniz.c"
#pragma GCC diagnostic pop


#include "TDQuickDraw.h"

#include "GDTFManager.h"

//using namespace ZIP;
using namespace VectorworksMVR::Filing;

/*static*/ VCOMError	CZIPFileImpl::fLastError;

#if GS_MAC
	const Sint32 kYearOffset = 76;
#else
	const Sint32 kYearOffset = 10;
#endif

#define	SETUP_CBP		gCBP = fCBP;

const int				kShortLength				= 2;
const int				kLongLength					= 4;

const int				kLocalFileHeaderLength		= 30;
const int				kCentralFileHeaderLength	= 46;
//const int				kEndHeaderLength			= 22;

const int				kMinimumZipFileSize			= 22;
const int				kMaxWBITS					= 15;	

CZIPFileIOBufferImpl::CZIPFileIOBufferImpl()
{
	fpZIPDataBuffer = NULL;
	fZIPDataBufferSize = 0;
}
	
CZIPFileIOBufferImpl::~CZIPFileIOBufferImpl()
{
	if ( fpZIPDataBuffer )
		delete [] fpZIPDataBuffer;
	fpZIPDataBuffer = NULL;
}


VCOMError CZIPFileIOBufferImpl::GetDataSize(size_t& outSize)
{
	outSize = fZIPDataBufferSize;
	return kVCOMError_NoError;
}

VCOMError CZIPFileIOBufferImpl::CopyDataInto(void* pDestinationBuffer, size_t bufferSize)
{
	if ( !fpZIPDataBuffer )
		return kVCOMError_NotInitialized;
		
	memcpy( pDestinationBuffer, fpZIPDataBuffer, (bufferSize >= fZIPDataBufferSize)? fZIPDataBufferSize : bufferSize );

	return kVCOMError_NoError;
}

VCOMError CZIPFileIOBufferImpl::AppendData(void* pBuffer, size_t bufferSize)
{
	if ( fpZIPDataBuffer )
	{
		Uint8* tempBuffer = new Uint8[ fZIPDataBufferSize + bufferSize + 1 ];
		memcpy( tempBuffer,  fpZIPDataBuffer, fZIPDataBufferSize );
		memcpy( tempBuffer + sizeof( Uint8 ) * fZIPDataBufferSize, pBuffer, bufferSize );
		fZIPDataBufferSize += bufferSize;
		delete [] fpZIPDataBuffer;

		fpZIPDataBuffer = new Uint8[ fZIPDataBufferSize + 1 ];
		memcpy( fpZIPDataBuffer, tempBuffer, fZIPDataBufferSize + 1);

		if ( tempBuffer )
			delete [] tempBuffer;
	}
	else 
	{
		this->SetData( pBuffer, bufferSize );
	}
	
	return kVCOMError_NoError;
}

VCOMError CZIPFileIOBufferImpl::SetData(void* pBuffer, size_t bufferSize)
{

	if ( fpZIPDataBuffer )
		delete [] fpZIPDataBuffer;

	fZIPDataBufferSize	= bufferSize;
	fpZIPDataBuffer		= new Uint8[ fZIPDataBufferSize + 1 ];
	memcpy( fpZIPDataBuffer, pBuffer, fZIPDataBufferSize );

	return kVCOMError_NoError;
}

// ----------------------------------------------------------------------------------------------------
CZIPFileImpl::CZIPFileImpl()
{
	fpOpenedFile			= NULL;
	fpOpenedFileID			= NULL;

	fbOpenedWrite			= false;
	fbCompressFiles			= true;

	fFolderPath				= "";
	fOpenedFileFullPath		= "";

}

CZIPFileImpl::~CZIPFileImpl()
{
	if(fpOpenedFile)
	{
		delete fpOpenedFile;
		fpOpenedFile = nullptr;
	}
}

VCOMError CZIPFileImpl::OpenRead(IFileIdentifier* pFileID)
{
	if ( fpOpenedFile )
	{
		fpOpenedFile->Close();
		delete fpOpenedFile;
	}

	fbOpenedWrite		= false;

	fpOpenedFile = new ZIPFileBuffer();
	fpOpenedFile->Open( pFileID, true );
	fpOpenedFileID = pFileID;

	IFolderIdentifierPtr pFolderID( IID_FolderIdentifier );
	pFileID->GetFolder( &pFolderID );
	pFolderID->GetFullPath( fFolderPath );
	pFileID->GetFileFullPath( fOpenedFileFullPath );

	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::OpenRead(const char* buffer, size_t length)
{
	if ( fpOpenedFile )
	{
		fpOpenedFile->Close();
		delete fpOpenedFile;
	}

	fbOpenedWrite		= false;

	fpOpenedFile = new ZIPFileBuffer();
	fpOpenedFile->Open( buffer,length );

	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::OpenWrite(IFileIdentifier* pFileID)
{
	if ( fpOpenedFile )
	{
		fpOpenedFile->Close();
		delete fpOpenedFile;
	}

	fbOpenedWrite	= true;
	fbCompressFiles = true;

	fpOpenedFile = new ZIPFileBuffer();
	fpOpenedFile->Open( pFileID, false );
	fpOpenedFileID = pFileID;

	IFolderIdentifierPtr pFolderID( IID_FolderIdentifier );
	pFileID->GetFolder( &pFolderID );
	pFolderID->GetFullPath( fFolderPath );
	pFileID->GetFileFullPath(fOpenedFileFullPath);
	
	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::OpenNewWrite(IFileIdentifier* pFileID, bool compressFiles)
{
	if ( fpOpenedFile )
	{
		fpOpenedFile->Close();
		delete fpOpenedFile;
	}

	fbOpenedWrite	= true;
	fbCompressFiles	= compressFiles;

	fpOpenedFile = new ZIPFileBuffer();
	fpOpenedFile->Open( pFileID, false );
	fpOpenedFileID = pFileID;

	IFolderIdentifierPtr pFolderID( IID_FolderIdentifier );
	pFileID->GetFolder( &pFolderID );
	pFolderID->GetFullPath( fFolderPath );
	pFileID->GetFileFullPath(fOpenedFileFullPath);
	
	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::Close()
{
	if ( fpOpenedFile )
	{
		fpOpenedFile->Close();
		fbOpenedWrite		= false;
		fOpenedFileFullPath = "";
		fFolderPath			= "";
	}
	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::ToBuffer(char*& p, size_t& inLength)
{
	fpOpenedFile->Copy(p, inLength);
	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::GetSize(Uint64& outValue)
{
	if ( fpOpenedFile )
	{
		fpOpenedFile->GetFileSize( outValue );
	}
	else 
	{
		outValue = 0;
	}
	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::GetNextFile(const std::string& path, std::string& outPath)
{
	VCOMError err = kVCOMError_NoError;
	// first find the refernced file

	Uint32 currentReadPosition;
	this->GetCentralDirPosition( currentReadPosition );
	if ( !currentReadPosition )
		return kVCOMError_Failed;
	
	if ( path != "" )
	{
		this->GetFileCentralHeaderPosition( path, currentReadPosition );
		currentReadPosition += ( 6 * kShortLength ) + ( 4 * kLongLength );

		Uint16 fileNameLength = 0;
		Uint16 extraFieldLength = 0;
		Uint16 fileCommentLength = 0;
		this->ReadShort( fileNameLength, currentReadPosition );
		this->ReadShort( extraFieldLength, currentReadPosition );
		this->ReadShort( fileCommentLength, currentReadPosition );

		currentReadPosition += ( 2 * kShortLength ) + ( 2 * kLongLength ) + fileNameLength + extraFieldLength + fileCommentLength;
	}

	Uint32 signature;
	this->ReadLong( signature, currentReadPosition );
	if ( signature != kCentralDirSignature )
		err =  kVCOMError_False;

	if ( err == kVCOMError_NoError )
	{
		Uint16 fileNameLength = 0;
		currentReadPosition += ( 6 * kShortLength ) + ( 3 * kLongLength ); // the file name length will be found here
		this->ReadShort( fileNameLength, currentReadPosition );
		currentReadPosition += ( 4 * kShortLength ) + ( 2 * kLongLength ); // the file name will be found here
		Uint64 inOutReadSize = (Uint64)fileNameLength;
		this->ReadFromFile( currentReadPosition, inOutReadSize, (void*) fReadFileName );

		if ( ( (size_t)inOutReadSize == fileNameLength ) &&  0 != strcmp(fReadFileName, ""))
		{
			outPath  = std::string( fReadFileName, fileNameLength );
		}
		else 
		{
			err = kVCOMError_Failed;
		}
	}

	return err;
}

VCOMError CZIPFileImpl::GetNextFile(const std::string& path, const std::string& extension, std::string& outPath)
{
	VCOMError err = kVCOMError_NoError;
	bool bFound = false;
	std::string currentFile = path;
	while ( bFound )
	{
		std::string nextFile;
		err = this->GetNextFile( currentFile, nextFile );
		if ( err != kVCOMError_NoError )
			break;

		TXString foundExtension = "";
		IFileIdentifierPtr pFileID( IID_FileIdentifier );
		pFileID->Set( outPath );
		pFileID->GetFileExtension( foundExtension );
	
		if ( extension == foundExtension )
		{	
			outPath = currentFile;
			bFound = true;
		}
		currentFile = nextFile;
		if ( currentFile == "" )
			break;
	}
	if ( !bFound )
		err = kVCOMError_Failed;

	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::GetFileInfo(const std::string& path, SZIPFileInfo& outInfo)
{
	VCOMError err = kVCOMError_NoError;

	if (!fpOpenedFile)
		return kVCOMError_NotInitialized;

	Uint32 currentReadPosition = 0;
	this->GetFileCentralHeaderPosition( path, currentReadPosition );

	
	Uint16 fileNameLength		= 0;
	Uint16 extraFieldLength		= 0;
	Uint16 fileCommentLength	= 0;
	Uint16 dummy;
	Uint32 signature;

	this->ReadLong( signature, currentReadPosition );
	if ( signature != kCentralDirSignature )
		return kVCOMError_False;

	if ( err == kVCOMError_NoError ) 
	{
		this->ReadShort( (Uint16&)outInfo.dwVersion, currentReadPosition );
		this->ReadShort( (Uint16&)outInfo.dwVersion, currentReadPosition );
		this->ReadShort( (Uint16&)outInfo.dwFlags, currentReadPosition );
		this->ReadShort( (Uint16&)outInfo.dwCompressionMethod, currentReadPosition );
		this->ReadShort( (Uint16&)outInfo.dwDosTime, currentReadPosition );
		this->ReadShort( (Uint16&)outInfo.dwDosDate, currentReadPosition );
		this->ReadLong( outInfo.dwCRC, currentReadPosition );
		this->ReadLong( outInfo.dwCompressedSize, currentReadPosition );
		this->ReadLong( outInfo.dwUncompressedSize, currentReadPosition );
		this->ReadShort( fileNameLength, currentReadPosition );
		this->ReadShort( extraFieldLength, currentReadPosition );
		this->ReadShort( fileCommentLength, currentReadPosition );
		this->ReadShort( dummy, currentReadPosition );
		this->ReadShort( (Uint16&)outInfo.dwInternalAttrib, currentReadPosition );
		this->ReadLong( outInfo.dwExternalAttrib, currentReadPosition );
		this->ReadLong( outInfo.dwOffsetOfLocalHeader, currentReadPosition ); 

		char* fileName = new char[fileNameLength];
		char* fileComment = new char[fileCommentLength];

		Uint64 inOutReadSize = (Uint64)fileNameLength;
		this->ReadFromFile( currentReadPosition, inOutReadSize, (void*)fileName );
		if ( inOutReadSize != fileNameLength )
			err = kVCOMError_Failed;

		currentReadPosition += extraFieldLength;
		inOutReadSize = (Uint64)fileCommentLength;
		this->ReadFromFile( currentReadPosition, inOutReadSize, (void*)fileComment );

		if ( inOutReadSize != fileCommentLength )
			err = kVCOMError_Failed;

		if ( fileName )
		{
			outInfo.fFileName = TXString( fileName, fileNameLength );
		}

		if ( fileComment )
		{
			outInfo.fComment = TXString( fileComment, fileCommentLength );
		}

		if ( fileComment )
			delete [] fileComment;
		if ( fileName )
			delete [] fileName;
	}
	
	return err;
}

VCOMError CZIPFileImpl::GetFile(const std::string& path, IZIPFileIOBuffer* outputBuffer)
{
	VCOMError err = kVCOMError_NoError;
	if ( fpOpenedFile == NULL )
		return kVCOMError_NotInitialized;
	
	SZIPFileInfo fileInfo;
	this->GetFileInfo( path, fileInfo );
	
	Uint32 currentReadPosition = fileInfo.dwOffsetOfLocalHeader;
	currentReadPosition += ( 5 * kShortLength ) + ( 4 * kLongLength ); // start of variable data

	Uint16 fileNameLength = 0;
	Uint16 extraFieldLength = 0;

	this->ReadShort( fileNameLength, currentReadPosition );
	this->ReadShort( extraFieldLength, currentReadPosition );

	currentReadPosition += fileNameLength + extraFieldLength;

	// read the raw data
	char* readData = new char[ fileInfo.dwCompressedSize ]; 
	Uint64 inOutReadSize = (Uint64)fileInfo.dwCompressedSize;
	this->ReadFromFile( currentReadPosition, inOutReadSize, (void*)readData ); 
	
	if ( fileInfo.dwCompressionMethod == 12  /* bzip2 */)
	{
		SceneData::GdtfFixture::AddError(GdtfParsingError(GdtfDefines::EGdtfParsingError::eFileWithUnsupportedEncodingInZip)); 
		err = kVCOMError_Failed;
	}
	else if(fileInfo.dwCompressionMethod == 0 /* No compression */)
	{
		err = outputBuffer->SetData( (void*)readData, fileInfo.dwCompressedSize ); 
	}
	else
	{
		// inflate the data if it is compressed
		bool bOk = this->Inflate( (void*)readData, fileInfo.dwCompressedSize, outputBuffer ); 
		if ( !bOk )
			err = kVCOMError_Failed;
	}

	if ( readData )
		delete [] readData;
					
	return err;
}

VCOMError CZIPFileImpl::GetFile(const std::string& path, IFileIdentifier* outputFile)
{
	TXString fullFilePath = fFolderPath;;
	fullFilePath += path;
	outputFile->Set( fullFilePath );

	CZIPFileIOBufferImpl inOutBuffer;
	VCOMError err = this->GetFile( path, &inOutBuffer );

	if ( err != kVCOMError_NoError || !this->Write(&inOutBuffer, outputFile ) )
		return kVCOMError_Failed;

	return err;
}

VCOMError CZIPFileImpl::AddFile(const TXString& inPath, IZIPFileIOBuffer* inputBuffer)
{
	TXString path = inPath;
	path.Replace("\\", "/");
	VCOMError err = kVCOMError_NoError;
	if ( !fpOpenedFile || !fbOpenedWrite )
		return kVCOMError_NotInitialized;

	Uint32 existingPosition = 0;
	this->GetFileCentralHeaderPosition( path.GetStdString(), existingPosition );
	
	if ( existingPosition ) // we don't add the file if a file with the same name already exists
		err =  kVCOMError_InvalidArg;

	if ( err == kVCOMError_NoError )
	{
		Uint32 centralDirPosition = 0;
		Uint32 endSignaturePosition = 0;
		Uint32 currentReadPosition = 0;
		Uint64 fileSize = 0;

		this->GetSize( fileSize );
		this->GetCentralDirPosition( centralDirPosition );
		this->GetEndOfCentralDirPosition( endSignaturePosition );

		if ( fileSize && centralDirPosition && endSignaturePosition )
		{
			char* readData1 = new char[(size_t)centralDirPosition ]; 
			char* readData2 = new char[(size_t)( endSignaturePosition - centralDirPosition )]; 
		
			Uint64 inOutReadSize = (Uint64)centralDirPosition;
			this->ReadFromFile( currentReadPosition, inOutReadSize, (void*)readData1 );

			inOutReadSize = endSignaturePosition - centralDirPosition;
			currentReadPosition = centralDirPosition;
			this->ReadFromFile( currentReadPosition, inOutReadSize, readData2 );
	
			SZIPFileInfo zipFileInfo;
			SZIPArchiveInfo zipArchiveInfo;
			this->GetZipArchiveInfo( &zipArchiveInfo );
		
			size_t uncompressedSize = 0;
			inputBuffer->GetDataSize( uncompressedSize );
			Uint8* deflateBuffer = new Uint8[ uncompressedSize ];
			inputBuffer->CopyDataInto( (void*)deflateBuffer, uncompressedSize );

			Uint16 compressionMethod = 0;
			size_t compressedSize = 0;
			Bytef* outData = nullptr;

			if ( fbCompressFiles )
			{
				size_t bufferSize = (size_t)( ( (double)uncompressedSize )*((double)((double)11/(double)10)) + 13);
				outData = new Bytef[bufferSize];
		
				compressedSize = this->Deflate( deflateBuffer, uncompressedSize, (void*)outData ) - kShortLength;
				outData += kShortLength;

				compressionMethod = 8; // Deflate
			}
			else
			{
				compressedSize = uncompressedSize;
				outData = new Bytef[compressedSize];

				memcpy( (void*)outData, (void*)deflateBuffer, compressedSize );
			}

			if ( !compressedSize )
				err = kVCOMError_Failed;

			zipFileInfo.bFolder = (uncompressedSize)?false:true;
			zipFileInfo.fFileName = path;
			zipFileInfo.fComment = "";
			zipFileInfo.dwCompressedSize = (Uint32)compressedSize; 
			zipFileInfo.dwUncompressedSize = (Uint32)uncompressedSize; 
			zipFileInfo.dwCompressionMethod = compressionMethod;
			zipFileInfo.dwFlags = 0;
			zipFileInfo.dwExternalAttrib = 0;
			zipFileInfo.dwInternalAttrib = 0;
			zipFileInfo.dwOffsetOfLocalHeader = (Uint32)centralDirPosition;
			zipFileInfo.dwVersion = 20;
			zipFileInfo.dwVersionNeeded = 20;
			zipFileInfo.dwCRC = crc32(0L, Z_NULL, 0);
			zipFileInfo.dwCRC = crc32( zipFileInfo.dwCRC, deflateBuffer, uncompressedSize  ); 
			this->GetDosDateAndTime( zipFileInfo.dwDosDate, zipFileInfo.dwDosTime );
	
			zipArchiveInfo.dwNumberOfEntriesOnThisDisk++;
			zipArchiveInfo.dwTotalNumberOfEntries++;
			zipArchiveInfo.dwOffsetCentralDir = centralDirPosition + (Uint32)compressedSize + (Uint32)zipFileInfo.fFileName.GetEncodingLength(ETXEncoding::eUTF8) + kLocalFileHeaderLength; 
			zipArchiveInfo.dwSizeOfCentralDir += kCentralFileHeaderLength + (Uint32)zipFileInfo.fFileName.GetEncodingLength(ETXEncoding::eUTF8); 

			Uint64 currentWritePosition = 0;
			fpOpenedFile->CleanBuffer();
			this->WriteToFile( (void*)readData1, currentWritePosition,  centralDirPosition );
			this->WriteLocalFileHeader( &zipFileInfo, currentWritePosition);
			this->WriteToFile( (void*)outData, currentWritePosition, compressedSize );
			this->WriteToFile( (void*)readData2, currentWritePosition,  ( endSignaturePosition - centralDirPosition ) );
			this->WriteCentralDirectoryHeader( &zipArchiveInfo, &zipFileInfo, currentWritePosition);
			this->WriteEndHeader( &zipArchiveInfo, currentWritePosition );
			
			if ( fbCompressFiles )
				outData -= kShortLength;

			if ( readData1 )
				delete [] readData1;
			if ( readData2 )
				delete [] readData2;
			if ( deflateBuffer )
				delete [] deflateBuffer;
			if ( outData )
				delete [] outData;
		}
		else
		{
			SZIPFileInfo zipFileInfo;
			SZIPArchiveInfo zipArchiveInfo;

			size_t uncompressedSize = 0;
			inputBuffer->GetDataSize( uncompressedSize );
			Uint8* deflateBuffer = new Uint8[ uncompressedSize ];
			inputBuffer->CopyDataInto( (void*)deflateBuffer, uncompressedSize );

			Uint16 compressionMethod = 0;
			size_t compressedSize = 0;
			Bytef* outData = nullptr;

			if ( fbCompressFiles )
			{
				size_t bufferSize = (size_t)( ( (double)uncompressedSize )*((double)((double)11/(double)10)) + 13);
				outData = new Bytef[bufferSize];
				
				compressedSize = this->Deflate( deflateBuffer, uncompressedSize, (void*)outData ) - kShortLength;
				outData += kShortLength;

				compressionMethod = 8; // Deflate
			}
			else
			{
				compressedSize = uncompressedSize;
				outData = new Bytef[compressedSize];

				memcpy( (void*)outData, (void*)deflateBuffer, compressedSize );
			}

			if ( !compressedSize )
				err = kVCOMError_Failed;
		
			zipFileInfo.bFolder = (uncompressedSize)?false:true;
			zipFileInfo.fFileName = path;
			zipFileInfo.fComment = "";
			zipFileInfo.dwCompressedSize =(Uint32) compressedSize; 
			zipFileInfo.dwUncompressedSize = (Uint32)uncompressedSize; 
			zipFileInfo.dwCompressionMethod = compressionMethod;
			zipFileInfo.dwDosTime = 0;
			zipFileInfo.dwDosDate = 0;
			zipFileInfo.dwFlags = 0;
			zipFileInfo.dwExternalAttrib = 0;
			zipFileInfo.dwInternalAttrib = 0;
			zipFileInfo.dwOffsetOfLocalHeader = 0;
			zipFileInfo.dwVersion = 20;
			zipFileInfo.dwVersionNeeded = 20;
			this->GetDosDateAndTime( zipFileInfo.dwDosDate, zipFileInfo.dwDosTime );
			
			zipArchiveInfo.dwCommentLength = 0;
			zipArchiveInfo.dwNumberOfCentralDirDisk = 0;
			zipArchiveInfo.dwNumberOfEntriesOnThisDisk = 1;
			zipArchiveInfo.dwNumberOfThisDisk = 0;
			zipArchiveInfo.dwOffsetCentralDir = 30 + (Uint32)zipFileInfo.fFileName.GetEncodingLength(ETXEncoding::eUTF8) + (Uint32)compressedSize; 
			zipArchiveInfo.dwSizeOfCentralDir = 46 + (Uint32)zipFileInfo.fFileName.GetEncodingLength(ETXEncoding::eUTF8); 
			zipArchiveInfo.dwStartingDiskNumber = 0;
			zipArchiveInfo.dwTotalNumberOfEntries = 1;
			zipArchiveInfo.fFileComment = "";
			zipFileInfo.dwCRC = crc32(0L, Z_NULL, 0);
			zipFileInfo.dwCRC = crc32( zipFileInfo.dwCRC, deflateBuffer, uncompressedSize  ); 
		
			Uint64 currentWritePosition = 0;
			this->Close();
			this->OpenNewWrite( fpOpenedFileID, fbCompressFiles );
			this->WriteLocalFileHeader( &zipFileInfo, currentWritePosition );
			this->WriteToFile( outData, currentWritePosition, compressedSize );
			this->WriteCentralDirectoryHeader( &zipArchiveInfo, &zipFileInfo, currentWritePosition );
			this->WriteEndHeader( &zipArchiveInfo, currentWritePosition );

			if ( fbCompressFiles )
				outData -= kShortLength;

			if ( deflateBuffer )
				delete[] deflateBuffer;
			if ( outData )
				delete[] outData;
		}
	}
	return err;
}

VCOMError CZIPFileImpl::AddFile(const TXString& path, IFileIdentifier* inputFile)
{
	CZIPFileIOBufferImpl inOutBuffer;
	this->Read(&inOutBuffer, inputFile);
	VCOMError err = this->AddFile( path, &inOutBuffer );		
	return err;	
}

VCOMError CZIPFileImpl::RemoveFile(const TXString& path)
{
	VCOMError err = kVCOMError_NoError;
	if ( !fpOpenedFile )
		return kVCOMError_NotInitialized;

	Uint32 centralFileHeaderPosition = 0;
	Uint32 localFileHeaderPosition = 0;
	this->GetFileCentralHeaderPosition( path.GetStdString(), centralFileHeaderPosition );

	if ( !centralFileHeaderPosition )
		err =  kVCOMError_Failed;

	if ( err == kVCOMError_NoError )
	{
		this->GetFileLocalHeaderPosition( path.GetStdString(), localFileHeaderPosition );
	
	
		Uint32 compressedSize = 0;
		Uint16 fileNameLength = 0;
		Uint16 extraFieldLength = 0;
		Uint16 fileCommentLength = 0;
		Uint32 currentReadPosition = 0;
		Uint32 removedLocalDataSize = 0;
		Uint32 removedCentralDataSize = 0;

		currentReadPosition = localFileHeaderPosition + ( 5 * kShortLength ) + ( 2 * kLongLength ); // here is the compressed size
		this->ReadLong( compressedSize, currentReadPosition );
		currentReadPosition += kLongLength;	// we skip the uncompressed size
		this->ReadShort( fileNameLength, currentReadPosition );
		this->ReadShort( extraFieldLength, currentReadPosition );
		removedLocalDataSize = kLocalFileHeaderLength + fileNameLength + extraFieldLength + compressedSize;

		currentReadPosition  = centralFileHeaderPosition + ( 6 * kShortLength ) + ( 4 * kLongLength ); // here is the file name length (in the central directory)
		this->ReadShort( fileNameLength, currentReadPosition );
		this->ReadShort( extraFieldLength, currentReadPosition );
		this->ReadShort( fileCommentLength, currentReadPosition );
		removedCentralDataSize	= kCentralFileHeaderLength + fileNameLength + extraFieldLength + fileCommentLength;

		SZIPArchiveInfo zipArchiveInfo;
		this->GetZipArchiveInfo( &zipArchiveInfo );
	
		TZIPFileInfoArray arrFileInfos;
		std::string currentFile = "";
		this->GetNextFile( std::string(""), currentFile );
		bool bFound = false;
		for ( Uint16 filesCounter = 0; filesCounter < zipArchiveInfo.dwTotalNumberOfEntries; filesCounter++ )
		{
			std::string nextFile;
			this->GetNextFile( currentFile, nextFile ); 
			SZIPFileInfo currentFileInfo;
			this->GetFileInfo( currentFile, currentFileInfo );
			if ( bFound )
			{
				currentFileInfo.dwOffsetOfLocalHeader -= removedLocalDataSize;
			}
			if ( currentFile == path )
				bFound = true;
			else
				arrFileInfos.push_back( currentFileInfo );

			if ( nextFile == "" )
				break;
			currentFile = nextFile;
		}
		zipArchiveInfo.dwOffsetCentralDir -= removedLocalDataSize;
		zipArchiveInfo.dwSizeOfCentralDir -= removedCentralDataSize;
		zipArchiveInfo.dwNumberOfEntriesOnThisDisk--;
		zipArchiveInfo.dwTotalNumberOfEntries--;
	
		char* readData1 = new char[(size_t)localFileHeaderPosition]; 
		char* readData2 = new char[(size_t)centralFileHeaderPosition - localFileHeaderPosition - removedLocalDataSize]; 
		Uint64 readSize1 = (Uint64)localFileHeaderPosition;
		Uint64 readSize2 = (Uint64)( centralFileHeaderPosition - localFileHeaderPosition - removedLocalDataSize);

		fpOpenedFile->Read( 0, readSize1, (void*)readData1 );
		fpOpenedFile->Read( localFileHeaderPosition + removedLocalDataSize, readSize2, (void*)readData2 );
	
		fpOpenedFile->Close();
		fpOpenedFile->Open( fpOpenedFileID, false );
	
		Uint64 currentWritePosition = 0;
		this->WriteToFile( (void*)readData1, currentWritePosition, readSize1 );
		this->WriteToFile( (void*)readData2, currentWritePosition, readSize2 );
		this->WriteCentralDirectoryHeader( &zipArchiveInfo, &arrFileInfos, currentWritePosition );
		this->WriteEndHeader( &zipArchiveInfo, currentWritePosition );

		fpOpenedFile->Close();
	
		if ( fbOpenedWrite )
		{
			fpOpenedFile->Open( fpOpenedFileID, false );
		}
		else 
		{
			fpOpenedFile->Open( fpOpenedFileID, true );
		}
	
		if ( readData1 )
			delete [] readData1;
		if ( readData2 )
			delete [] readData2;
	}

	return kVCOMError_NoError;
}

VCOMError CZIPFileImpl::MoveFile(const TXString& path)
{
	if ( !fpOpenedFile )
	 return kVCOMError_NotInitialized;
		
	IFileIdentifierPtr pMovedFile( IID_FileIdentifier );
	pMovedFile->Set( path );
	fpOpenedFile->Close();
	fpOpenedFileID->DuplicateOnDisk( pMovedFile, true );
	fpOpenedFileID->DeleteOnDisk();
	fpOpenedFileID = pMovedFile;

	if ( fbOpenedWrite )
	{
		fpOpenedFile->Open( pMovedFile, false );	
	}
	else
	{
		fpOpenedFile->Open( pMovedFile, true );
	}

	return kVCOMError_NoError;
}

//typedef uLong (*check_func) (uLong check, const Byte *buf, uInt len);

bool CZIPFileImpl::Inflate( void* pData, size_t dataSize, IZIPFileIOBuffer* outBuffer )
{
	mz_streamp streamToInflate = new z_stream;
	streamToInflate->zalloc = (alloc_func)0;
	streamToInflate->zfree = (free_func)0;
	streamToInflate->opaque = (voidpf)0;
	int err = inflateInit2( streamToInflate, -kMaxWBITS );
	if (err)
		return false;
	
	streamToInflate->next_in = (Uint8*)pData;
	streamToInflate->avail_in = (unsigned int)dataSize; 
	streamToInflate->total_in = 0;
	streamToInflate->data_type = 0;
	
	CZIPFileIOBufferImpl zipBuffer;
	bool bOk = false;
	bool bFinished = false;

	Uint8* inflateBuffer = new Uint8[ dataSize ];
	while ( !bFinished )
	{
		streamToInflate->next_out = inflateBuffer;
		streamToInflate->avail_out = (unsigned int)dataSize; 
		int result = inflate( streamToInflate, Z_NO_FLUSH  );
		zipBuffer.AppendData( inflateBuffer, ( dataSize - streamToInflate->avail_out ) );
		bOk = result == Z_STREAM_END;
		bool bError = result < 0;
		if ( bError || bOk )
		{
			bFinished = true;
			bOk = bOk && !bError;
		}
	}
	if ( bOk )
	{
		zipBuffer.GetDataSize( dataSize  );
		Uint8* tempBuffer = new Uint8[ dataSize ];
		zipBuffer.CopyDataInto( tempBuffer, dataSize );
		outBuffer->SetData( tempBuffer, dataSize );

		if ( tempBuffer )
			delete [] tempBuffer;
	}

	if ( inflateBuffer )
		delete [] inflateBuffer;

	mz_inflateEnd(streamToInflate);

	if ( streamToInflate ) 
		delete streamToInflate;

	return bOk ;
}

size_t CZIPFileImpl::Deflate( void* pData, size_t dataSize, void* outData )
{
	mz_streamp streamToDeflate = new z_stream;
	streamToDeflate->zalloc = (alloc_func)0;
	streamToDeflate->zfree = (free_func)0;
	streamToDeflate->opaque = (voidpf)0;
	size_t outSize = 0;

	int err = deflateInit( streamToDeflate, 8 );
	if (err)
		return outSize;

	streamToDeflate->next_in =  (Bytef*)pData;
	streamToDeflate->avail_in =(unsigned int) dataSize; 
	streamToDeflate->total_in = 0;
	

	bool bOk = false;
	bool bFinished = false;

	size_t availableSize = (size_t)( (double)((double)dataSize * ((double)11/(double)10)) + 13 );
	while ( !bFinished )
	{
		streamToDeflate->next_out = (Bytef*)outData;
		streamToDeflate->avail_out =(unsigned int) availableSize; 
		int result = deflate( streamToDeflate, Z_FINISH  );
		bOk = result == Z_STREAM_END || result == Z_OK;
		bool bError = result < 0;
		if ( bError || bOk )
		{
			outSize = streamToDeflate->total_out;
			bFinished = true;
			bOk = bOk && !bError;
		}
	}

	mz_deflateEnd( streamToDeflate );

	if ( streamToDeflate ) 
		delete streamToDeflate;

	// skip extended adler-32
	return outSize-4;
}

bool CZIPFileImpl::Write( IZIPFileIOBuffer* inputBuffer, IFileIdentifier* pFileID )
{
	bool bOk = false;
	if ( pFileID )
	{
		IRawOSFilePtr pFile( IID_RawOSFile );
		if ( pFile && VCOM_SUCCEEDED( pFile->Open( pFileID, true, true, true, true ) ) )
		{
			size_t dataSize;
			inputBuffer->GetDataSize( dataSize );
			char* writeData = new char[dataSize];
			inputBuffer->CopyDataInto( writeData, dataSize );
			pFile->Write( 0, (Uint64)dataSize, (void*)writeData );
			pFile->Close();
			
			bOk = true;
			
			if ( writeData )
				delete [] writeData;
		}
	}
	return bOk;
}

void CZIPFileImpl::WriteLong( Uint32 toWrite, Uint64& currentWritePosition) 
{
	if ( fpOpenedFile && fbOpenedWrite )
	{
		Uint8* bufToWrite = new Uint8[4];
		bufToWrite[0] = (Uint8)( ( toWrite & 0xFFFF ) & 0xFF );
		bufToWrite[1] = (Uint8)( ( toWrite & 0xFFFF ) >> 8 );
		bufToWrite[2] = (Uint8)( ( toWrite >> 16 ) & 0xFF );
		bufToWrite[3] = (Uint8)( ( toWrite >> 16 ) >> 8 );

		fpOpenedFile->Write( currentWritePosition, kLongLength, (void*)bufToWrite );

		currentWritePosition += kLongLength;

		if ( bufToWrite )
			delete [] bufToWrite;
	}
}

void CZIPFileImpl::WriteShort( Uint16 toWrite, Uint64& currentWritePosition )
{
	if ( fpOpenedFile && fbOpenedWrite )
	{
		Uint8* bufToWrite = new Uint8[2];
		bufToWrite[0] = (Uint8)( ( toWrite ) & 0xFF );
		bufToWrite[1] = (Uint8)( ( toWrite ) >> 8 );
	
		fpOpenedFile->Write( currentWritePosition, kShortLength, (void*)bufToWrite );

		currentWritePosition += kShortLength;

		if ( bufToWrite )
			delete [] bufToWrite;
	}
}

void CZIPFileImpl::WriteToFile( void* toWrite, Uint64& currentWritePosition, Uint64 size )
{
	if ( fpOpenedFile && fbOpenedWrite )
	{
		fpOpenedFile->Write( currentWritePosition, size, toWrite );
		currentWritePosition += size;
	}
}

bool CZIPFileImpl::Read( IZIPFileIOBuffer* outputBuffer, IFileIdentifier* pFileID )
{
	bool bOk = false;
	if ( pFileID )
	{
		IRawOSFilePtr pFile( IID_RawOSFile );
		if ( pFile && VCOM_SUCCEEDED( pFile->Open( pFileID, true, false, true, false ) ) )
		{
			Uint64 fileSize;
			pFile->GetFileSize( fileSize );

			char* readData = new char[(size_t)fileSize];
			pFile->Read( 0, fileSize, readData );
			outputBuffer->SetData( (void*)readData, (size_t)fileSize );
			bOk = true;

			if ( readData )
				delete [] readData;
		pFile->Close();
		}
	}
	return bOk;
}

void CZIPFileImpl::ReadLong( Uint32& outRead, Uint32& currentReadPosition )
{
	if ( fpOpenedFile )
	{
		Uint64 length = 0;
		this->fpOpenedFile->GetFileSize(length);

		if(currentReadPosition >= length)
		{
			outRead = 0;
		}
		else
		{
			Uint64 size = sizeof(Uint32);
			fpOpenedFile->Read( currentReadPosition, size, (void*)&outRead );
			currentReadPosition +=sizeof(Uint32);
		}
	}
}

void CZIPFileImpl::ReadShort( Uint16& outRead, Uint32& currentReadPosition )
{
	if ( fpOpenedFile )
	{
		Uint64 length = 0;
		this->fpOpenedFile->GetFileSize(length);

		if(currentReadPosition >= length)
		{
			outRead = 0;
		}
		else
		{
			Uint64 size = sizeof(Uint16);
			fpOpenedFile->Read( currentReadPosition, size, (void*)&outRead );
			currentReadPosition +=sizeof(Uint16);
		}
	}
}

void CZIPFileImpl::ReadFromFile( Uint32& currentReadPosition, Uint64& inOutReadSize, void* toRead )
{
	if ( fpOpenedFile )
	{
		fpOpenedFile->Read( currentReadPosition, inOutReadSize, toRead );
		currentReadPosition += (Uint32)inOutReadSize;
	}
}

void CZIPFileImpl::WriteLocalFileHeader( SZIPFileInfo* fileInfo, Uint64& currentWritePosition )
{
	this->WriteLong( kLocalFileInfoSignature, currentWritePosition );
	this->WriteShort( fileInfo->dwVersion, currentWritePosition );
	this->WriteShort( fileInfo->dwFlags, currentWritePosition );
	this->WriteShort( fileInfo->dwCompressionMethod, currentWritePosition );
	this->WriteShort( fileInfo->dwDosTime, currentWritePosition );
	this->WriteShort( fileInfo->dwDosDate, currentWritePosition );
	this->WriteLong( fileInfo->dwCRC, currentWritePosition );
	this->WriteLong( fileInfo->dwCompressedSize, currentWritePosition );
	this->WriteLong( fileInfo->dwUncompressedSize, currentWritePosition );
	this->WriteShort( (Uint16)fileInfo->fFileName.GetEncodingLength(ETXEncoding::eUTF8), currentWritePosition );
	this->WriteShort( 0, currentWritePosition );
	this->WriteToFile( (void*)(const char*)fileInfo->fFileName, currentWritePosition, fileInfo->fFileName.GetEncodingLength(ETXEncoding::eUTF8));
}

void CZIPFileImpl::WriteCentralDirectoryHeader( SZIPArchiveInfo* zipArchiveInfo, TZIPFileInfoArray* fileInfoArray, Uint64& currentWritePosition )
{
	size_t numberOfFiles = fileInfoArray->size();
	for ( size_t fileInfoCounter = 0; fileInfoCounter < numberOfFiles; fileInfoCounter++ )
	{
		SZIPFileInfo currentFileInfo = fileInfoArray->at( fileInfoCounter );
		
		this->WriteLong( kCentralDirSignature, currentWritePosition );
		this->WriteShort( currentFileInfo.dwVersion, currentWritePosition );
		this->WriteShort( currentFileInfo.dwVersion, currentWritePosition );
		this->WriteShort( currentFileInfo.dwFlags, currentWritePosition );
		this->WriteShort( currentFileInfo.dwCompressionMethod, currentWritePosition );
		this->WriteShort( currentFileInfo.dwDosTime, currentWritePosition );
		this->WriteShort( currentFileInfo.dwDosDate, currentWritePosition );
		this->WriteLong( currentFileInfo.dwCRC, currentWritePosition );
		this->WriteLong( currentFileInfo.dwCompressedSize, currentWritePosition );
		this->WriteLong( currentFileInfo.dwUncompressedSize, currentWritePosition );
		this->WriteShort((Uint16) currentFileInfo.fFileName.GetEncodingLength(ETXEncoding::eUTF8), currentWritePosition );
		this->WriteShort( 0, currentWritePosition );
		this->WriteShort((Uint16) currentFileInfo.fComment.GetEncodingLength(ETXEncoding::eUTF8), currentWritePosition );
		this->WriteShort( zipArchiveInfo->dwStartingDiskNumber, currentWritePosition );
		this->WriteShort( currentFileInfo.dwInternalAttrib, currentWritePosition );
		this->WriteLong( currentFileInfo.dwExternalAttrib, currentWritePosition );
		this->WriteLong( currentFileInfo.dwOffsetOfLocalHeader, currentWritePosition );
		this->WriteToFile( (void*)(const char *)currentFileInfo.fFileName, currentWritePosition, currentFileInfo.fFileName.GetEncodingLength(ETXEncoding::eUTF8));
		this->WriteToFile( (void*)(const char *)zipArchiveInfo->fFileComment, currentWritePosition, zipArchiveInfo->dwCommentLength );
	}
}

void CZIPFileImpl::WriteCentralDirectoryHeader( SZIPArchiveInfo* zipArchiveInfo, SZIPFileInfo* zipFileInfo, Uint64& currentWritePosition )
{
	
	this->WriteLong( kCentralDirSignature, currentWritePosition );
	this->WriteShort( zipFileInfo->dwVersion, currentWritePosition );
	this->WriteShort( zipFileInfo->dwVersion, currentWritePosition );
	this->WriteShort( zipFileInfo->dwFlags, currentWritePosition );
	this->WriteShort( zipFileInfo->dwCompressionMethod, currentWritePosition );
	this->WriteShort( zipFileInfo->dwDosTime, currentWritePosition );
	this->WriteShort( zipFileInfo->dwDosDate, currentWritePosition );
	this->WriteLong( zipFileInfo->dwCRC, currentWritePosition );
	this->WriteLong( zipFileInfo->dwCompressedSize, currentWritePosition );
	this->WriteLong( zipFileInfo->dwUncompressedSize, currentWritePosition );
	this->WriteShort( (Uint16)zipFileInfo->fFileName.GetEncodingLength(ETXEncoding::eUTF8), currentWritePosition );
	this->WriteShort( 0, currentWritePosition );
	this->WriteShort((Uint16) zipFileInfo->fComment.GetEncodingLength(ETXEncoding::eUTF8), currentWritePosition );
	this->WriteShort( zipArchiveInfo->dwStartingDiskNumber, currentWritePosition );
	this->WriteShort( zipFileInfo->dwInternalAttrib, currentWritePosition );
	this->WriteLong( zipFileInfo->dwExternalAttrib, currentWritePosition );
	this->WriteLong( zipFileInfo->dwOffsetOfLocalHeader, currentWritePosition );
	this->WriteToFile( (void*)(const char *)zipFileInfo->fFileName, currentWritePosition, zipFileInfo->fFileName.GetEncodingLength(ETXEncoding::eUTF8));
	this->WriteToFile( (void*)(const char *)zipArchiveInfo->fFileComment, currentWritePosition, zipArchiveInfo->dwCommentLength );
	
}

void CZIPFileImpl::WriteEndHeader( SZIPArchiveInfo* zipArchiveInfo, Uint64& currentWritePosition )
{
	this->WriteLong( kEndSignature, currentWritePosition );
	this->WriteShort( zipArchiveInfo->dwNumberOfThisDisk, currentWritePosition );
	this->WriteShort( zipArchiveInfo->dwNumberOfCentralDirDisk, currentWritePosition );
	this->WriteShort( zipArchiveInfo->dwNumberOfEntriesOnThisDisk, currentWritePosition );
	this->WriteShort( zipArchiveInfo->dwTotalNumberOfEntries, currentWritePosition );
	this->WriteLong( zipArchiveInfo->dwSizeOfCentralDir, currentWritePosition );
	this->WriteLong( zipArchiveInfo->dwOffsetCentralDir, currentWritePosition );
	this->WriteShort( zipArchiveInfo->dwCommentLength, currentWritePosition );
	this->WriteToFile( (void *)(const char *)zipArchiveInfo->fFileComment, currentWritePosition, zipArchiveInfo->dwCommentLength );
}

void CZIPFileImpl::GetCentralDirPosition( Uint32& outPosition )
{
	// find the end header and get the offset to the central header
	// read backwards because the central dir is more likely to be at the end of the file

	outPosition = 0;
	if ( fpOpenedFile )
	{
		Uint64 fileSize = 0;
		this->GetSize( fileSize );
		if ( fileSize < kMinimumZipFileSize ) // minimum zip file format size
			return;
		for ( Uint32 readBytes = (Uint32)fileSize - kLongLength - 1; readBytes > 0; readBytes-- )
		{
			Uint32 currentLongValue;
			Uint32 currentReadPos = readBytes;
			this->ReadLong( currentLongValue, currentReadPos );
			if ( (currentReadPos > readBytes) && currentLongValue == kEndSignature )
			{
				readBytes += (4 * kShortLength ) + ( 2 * kLongLength ); // offset of the central position data
				this->ReadLong( currentLongValue, readBytes); 
				outPosition = currentLongValue;
				break;
			}
		}
	}
}

void CZIPFileImpl::GetEndOfCentralDirPosition( Uint32& outPosition )
{
	outPosition = 0;
	if ( fpOpenedFile )
	{
		Uint64 fileSize = 0;
		this->GetSize( fileSize );
		if ( fileSize < kMinimumZipFileSize ) 
			return;
		for ( Uint32 readBytes = (Uint32)fileSize - kLongLength - 1; readBytes > 0; readBytes-- )
		{
			Uint32 currentLongValue = 0;
			Uint32 currentReadPosition = readBytes;
			this->ReadLong( currentLongValue, currentReadPosition );
			if ( (currentReadPosition > readBytes) && currentLongValue == kEndSignature )
			{
				
				outPosition = currentReadPosition - kLongLength;
				break;
			}
		}
	}
}

void CZIPFileImpl::GetFileLocalHeaderPosition( const std::string& path, Uint32& outPosition )
{
	if ( !fpOpenedFile )
		return;

	outPosition					= 0;
	Uint32 currentReadPosition	= 0;
	this->GetCentralDirPosition( currentReadPosition );
	if ( !currentReadPosition || path == "" )
		return;

	bool bFound = false;
	bool bError = false;
	while ( !bFound && !bError)
	{
		Uint32 signature;
		this->ReadLong( signature, currentReadPosition );
		if ( signature != kCentralDirSignature )
			bError = true;

		currentReadPosition += ( 6 * kShortLength ) + (3 * kLongLength); // start of variable length data ( file name, extra field and comment lengths )

		Uint16 fileNameLength		= 0;
		Uint16 extraFieldLength		= 0;
		Uint16 fileCommentLength	= 0;
		Uint32 localHeaderOffset	= 0;
		this->ReadShort( fileNameLength, currentReadPosition );
		this->ReadShort( extraFieldLength, currentReadPosition );
		this->ReadShort( fileCommentLength, currentReadPosition );

		currentReadPosition += ( 2 * kLongLength );							// start of variable data
	
		this->ReadLong( localHeaderOffset, currentReadPosition );
		Uint64 inOutReadSize = (Uint64)fileNameLength;
		this->ReadFromFile( currentReadPosition, inOutReadSize, fReadFileName );

		if ( inOutReadSize != fileNameLength )
		{
			bError = true;
			return;
		}

		if (((size_t)path.size() == fileNameLength ) &&  0 == memcmp(fReadFileName, path.c_str(), fileNameLength))
		{
			outPosition = localHeaderOffset;
			bFound = true;
		}

		currentReadPosition += extraFieldLength + fileCommentLength;
	}
}

void CZIPFileImpl::GetFileCentralHeaderPosition( const std::string& path, Uint32& outPosition )
{
	if ( !fpOpenedFile )
		return;

	outPosition					= 0;
	Uint32 currentReadPosition	= 0;
	this->GetCentralDirPosition( currentReadPosition );
	if (  !currentReadPosition || path.empty() )
		return;

	bool bFound = false;
	bool bError = false;
	while ( !bFound && !bError )
	{
		Uint32 startOffset = (Uint32)currentReadPosition;
		Uint32 signature;
		this->ReadLong( signature, currentReadPosition );
		if ( signature != kCentralDirSignature )
			bError = true;

		currentReadPosition += ( 6 * kShortLength ) + ( 3 * kLongLength ); // start of variable length data ( file name, extra field and comment lengths )
		Uint16 fileNameLength		= 0;
		Uint16 extraFieldLength		= 0;
		Uint16 fileCommentLength	= 0;
		Uint32 localHeaderOffset	= 0;
		this->ReadShort( fileNameLength, currentReadPosition );
		this->ReadShort( extraFieldLength, currentReadPosition );
		this->ReadShort( fileCommentLength, currentReadPosition );

		currentReadPosition += ( 2 * kLongLength );

		// start of variable data

		this->ReadLong( localHeaderOffset, currentReadPosition );
		Uint64 inOutReadSize = (Uint64)fileNameLength;
		this->ReadFromFile( currentReadPosition, inOutReadSize, fReadFileName );
		
		if ( inOutReadSize != fileNameLength )
		{
			bError = true;
		}

		if (((size_t)path.size() == fileNameLength ) &&  0 == memcmp(fReadFileName, path.c_str(), fileNameLength))
		{
			bFound = true;
			outPosition = startOffset;
		}

		currentReadPosition += extraFieldLength + fileCommentLength;
	}
}

void CZIPFileImpl::GetZipArchiveInfo( SZIPArchiveInfo* zipArchiveInfo )
{
	Uint32 endOfCentralDirPosition = 0;
	this->GetEndOfCentralDirPosition( endOfCentralDirPosition );

	if ( endOfCentralDirPosition )
	{
		Uint32 currentReadPosition = endOfCentralDirPosition;
		Uint32 longValue;
		this->ReadLong( longValue, currentReadPosition );
		if ( longValue != kEndSignature )
			return;

		this->ReadShort( zipArchiveInfo->dwNumberOfThisDisk, currentReadPosition );
		this->ReadShort( zipArchiveInfo->dwNumberOfCentralDirDisk, currentReadPosition );
		this->ReadShort( zipArchiveInfo->dwNumberOfEntriesOnThisDisk, currentReadPosition );
		this->ReadShort( zipArchiveInfo->dwTotalNumberOfEntries, currentReadPosition );
		this->ReadLong( zipArchiveInfo->dwSizeOfCentralDir, currentReadPosition );
		this->ReadLong( zipArchiveInfo->dwOffsetCentralDir, currentReadPosition );
		this->ReadShort( zipArchiveInfo->dwCommentLength, currentReadPosition );

		zipArchiveInfo->dwStartingDiskNumber = zipArchiveInfo->dwNumberOfCentralDirDisk;
		char* fileComment = new char[ zipArchiveInfo->dwCommentLength ];
		Uint64 inOutReadSize = (Uint64)zipArchiveInfo->dwCommentLength;
		this->ReadFromFile( currentReadPosition, inOutReadSize, fileComment );

		if ( inOutReadSize && inOutReadSize == (Uint64)zipArchiveInfo->dwCommentLength )
		{
			zipArchiveInfo->fFileComment = TXString( fileComment, (size_t)zipArchiveInfo->dwCommentLength);
		}

		if ( fileComment )
			delete [] fileComment;
	}
}

void CZIPFileImpl::GetDosDateAndTime( Uint16& dosDate, Uint16& dosTime )
{
	const Sint32 kYearInSeconds = 365 * 24 * 60 * 60;
	const Sint32 kDayInSeconds = 24 * 60 * 60;
	const Sint32 kHourInSeconds = 60 * 60;
	const Sint32 kMinuteInSeconds = 60;

	Sint32 year, month, day, hour, minute, second, dayNumber;
	Sint32 time = GetTimeStamp();
	year	= time / kYearInSeconds;
	dayNumber		= ( time - year * kYearInSeconds - ( year / 4 ) * kDayInSeconds ) / kDayInSeconds; // add leap years' days
	if ( dayNumber <= 31 )
	{
		day = dayNumber;
		month = 0;
	}
	else if ( dayNumber <= 59 )
	{
		day = dayNumber - 31;
		month = 1;
	}
	else if ( dayNumber <= 90 )
	{
		day = dayNumber - 59;
		month = 2;
	}
	else if ( dayNumber <= 120 )
	{
		day = dayNumber - 90;
		month = 3;
	}
	else if ( dayNumber <= 151 )
	{
		day = dayNumber - 120;
		month = 4;
	}
	else if ( dayNumber <= 181 )
	{
		day = dayNumber - 151;
		month = 5;
	}
	else if ( dayNumber <= 212 )
	{
		day = dayNumber - 181;
		month = 6;
	}
	else if ( dayNumber <= 243 )
	{
		day = dayNumber - 212;
		month = 7;
	}
	else if ( dayNumber <= 273 )
	{
		day = dayNumber - 243;
		month = 8;
	}
	else if ( dayNumber <= 304 )
	{
		day = dayNumber - 273;
		month = 9;
	}
	else if ( dayNumber <= 334 )
	{
		day = dayNumber - 304;
		month = 10;
	}
	else 
	{
		day = dayNumber - 334;
		month = 11;
	}
	
	hour = ( time - year * kYearInSeconds - ( ( year / 4 ) + dayNumber) * kDayInSeconds ) / kHourInSeconds;
	minute = ( time - year * kYearInSeconds - ( ( year / 4 ) + dayNumber ) * kDayInSeconds - hour * kHourInSeconds ) / kMinuteInSeconds;
	second = ( time - year * kYearInSeconds - ( ( year / 4 ) + dayNumber ) * kDayInSeconds - hour * kHourInSeconds - minute * kMinuteInSeconds );
	month++; day++; second++;

	dosTime = (Uint16)( second&31 ); dosTime += (Uint16)( (minute&63) << 5); dosTime += (Uint16)( (hour&31) << 11);
	dosDate = (Uint16)( day&31 ); dosDate += (Uint16)( (month&15) << 5); dosDate += (Uint16)(( (year - kYearOffset )&127 ) << 9);

}
