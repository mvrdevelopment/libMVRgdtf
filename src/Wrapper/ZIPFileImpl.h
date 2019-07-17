/*
 *  ZIPFileImpl.h
 *  VectorWorks
 *
 *  Created by Yavor Simeonov on 12/05/10.
 *  Copyright 2010 Nemetschek North America, Inc. All rights reserved.
 *
 */

#pragma once

namespace VectorworksMVR
{
	namespace Filing
	{
		/*namespace ZIP
		{*/

	const Uint64 kLocalFileInfoSignature	= 0x04034b50L;
	const Uint64 kCentralDirSignature		= 0x02014b50L;
	const Uint64 kEndSignature				= 0x06054b50L;
	const Uint64 kExtraDataSignature		= 0x08074b50L;

		struct SZIPArchiveInfo
		{
			TXString fFileComment;

			Uint16 dwNumberOfThisDisk;
			Uint16 dwNumberOfCentralDirDisk;
			Uint16 dwNumberOfEntriesOnThisDisk;
			Uint16 dwTotalNumberOfEntries;
			Uint32 dwSizeOfCentralDir;
			Uint32 dwOffsetCentralDir;
			Uint16 dwStartingDiskNumber;
			Uint16 dwCommentLength;
		};

		typedef std::vector<VectorworksMVR::Filing::SZIPFileInfo> TZIPFileInfoArray;
		// ----------------------------------------------------------------------------------------------------
		class  CZIPFileIOBufferImpl : public IZIPFileIOBuffer
		{
		public:
			CZIPFileIOBufferImpl();
			virtual							~CZIPFileIOBufferImpl();

		public:
			virtual	VCOMError VCOM_CALLTYPE	GetDataSize(size_t& outSize);
			virtual VCOMError VCOM_CALLTYPE	CopyDataInto(void* pBuffer, size_t bufferSize);
			virtual	VCOMError VCOM_CALLTYPE AppendData( void* pBuffer, size_t bufferSize );
			virtual VCOMError VCOM_CALLTYPE	SetData(void* pBuffer, size_t bufferSize);

		private:
			Uint8*						fpZIPDataBuffer;
			size_t						fZIPDataBufferSize;

		};

		// ----------------------------------------------------------------------------------------------------

		class  CZIPFileImpl : public IZIPFile
		{
		public:
			CZIPFileImpl();
			virtual							~CZIPFileImpl();

		public:
			virtual uint32_t	VCOM_CALLTYPE	AddRef();
			virtual uint32_t	VCOM_CALLTYPE	Release();

		public:
			virtual VCOMError VCOM_CALLTYPE	OpenRead(IFileIdentifier* pFileID);
			virtual VCOMError VCOM_CALLTYPE	OpenWrite(IFileIdentifier* pFileID);
			virtual VCOMError VCOM_CALLTYPE	OpenNewWrite(IFileIdentifier* pFileID, bool compressFiles = true);
			virtual VCOMError VCOM_CALLTYPE	Close();

			virtual VCOMError VCOM_CALLTYPE	GetSize(Uint64& outValue);

			// 'path' uses '/' delimited string to identify a file or folder within the zip file
			// empty 'path' denotes the root folder of the zip file

			virtual VCOMError VCOM_CALLTYPE	GetNextFile(const TXString& path, TXString& outPath);
			virtual VCOMError VCOM_CALLTYPE	GetNextFile(const TXString& path, const TXString& extension, TXString& outPath);

			virtual VCOMError VCOM_CALLTYPE	GetFileInfo(const TXString& path, SZIPFileInfo& outInfo);

			virtual VCOMError VCOM_CALLTYPE	GetFile(const TXString& path, IZIPFileIOBuffer* outputBuffer);
			virtual VCOMError VCOM_CALLTYPE	GetFile(const TXString& path, IFileIdentifier* outputFile);

			virtual VCOMError VCOM_CALLTYPE	AddFile(const TXString& path, IZIPFileIOBuffer* inputBuffer);
			virtual VCOMError VCOM_CALLTYPE	AddFile(const TXString& path, IFileIdentifier* inputFile);

			virtual VCOMError VCOM_CALLTYPE	RemoveFile(const TXString& path);
			virtual VCOMError VCOM_CALLTYPE	MoveFile(const TXString& path);

		public:
			size_t	Deflate( void* pData, size_t dataSize, void* outData );
			bool	Inflate( void* pData, size_t dataSize, IZIPFileIOBuffer* outBuffer );
		public:

			bool	Write( IZIPFileIOBuffer* inputBuffer, IFileIdentifier* pFileID );
			void	WriteLong( Uint32 toWrite, Uint64& currentWritePosition );
			void	WriteShort( Uint16 toWrite, Uint64& currentWritePosition );
			void	WriteToFile( void* toWrite, Uint64& currentWritePosition, Uint64 size );

			bool	Read( IZIPFileIOBuffer* outputBuffer, IFileIdentifier* pFileID );
			void	ReadLong( Uint32& outRead, Uint32& currentReadPosition );
			void	ReadShort( Uint16& outRead, Uint32& currentreadPosition );
			void	ReadFromFile( Uint32& currentReadPosition, Uint64& inOutReadSize, void* toRead );

			void	WriteLocalFileHeader( SZIPFileInfo* fileInfo, Uint64& currentWritePosition );
			void	WriteCentralDirectoryHeader( SZIPArchiveInfo* zipArchiveInfo, TZIPFileInfoArray* fileInfoArray, Uint64& currentWritePosition );
			void	WriteCentralDirectoryHeader( SZIPArchiveInfo* zipArchiveInfo, SZIPFileInfo* fileInfo, Uint64& currentWritePosition );
			void	WriteEndHeader( SZIPArchiveInfo* zipArchiveInfo, Uint64& currentWritePosition );

			void	GetCentralDirPosition( Uint32& outPosition );
			void	GetEndOfCentralDirPosition( Uint32& outPosition );
			void	GetFileCentralHeaderPosition( const TXString& path, Uint32& outPosition );
			void	GetFileLocalHeaderPosition( const TXString& path, Uint32& outPosition );
			
			void	GetZipArchiveInfo( SZIPArchiveInfo* zipArchiveInfo );
			void	GetDosDateAndTime( Uint16& dosDate, Uint16& dosTime);
	
		private:
			uint32_t							fRefCnt;

			bool							fbOpenedWrite;
			bool							fbCompressFiles;

			VCOMPtr<IRawOSFile>				fpOpenedFile;
			VCOMPtr<IFileIdentifier>		fpOpenedFileID;

			TXString						fOpenedFileFullPath;
			TXString						fFolderPath;

		private:
			static VCOMError				fLastError;

		};
	}
}
/*}*/


