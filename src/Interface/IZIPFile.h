//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

#include "IFileIdentifier.h"

namespace VectorworksMVR
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		struct SZIPFileInfo
		{
			TXString	fFileName;
			TXString	fComment;
		
			Uint16		dwVersion;  
			Uint32		dwVersionNeeded;
			Uint16		dwFlags;	 
			Uint16		dwCompressionMethod; 
			Uint16		dwDosTime;
			Uint16		dwDosDate;	
			Uint32		dwCRC;   
			Uint32		dwCompressedSize; 
			Uint32		dwUncompressedSize;
			Uint16		dwInternalAttrib; 
			Uint32		dwExternalAttrib; 
			Uint32		dwOffsetOfLocalHeader;
			bool		bFolder;
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IZIPFileIOBuffer
		{
		public:
			virtual							~IZIPFileIOBuffer()		{}

			virtual	VCOMError VCOM_CALLTYPE	GetDataSize(size_t& outSize) = 0;
			virtual VCOMError VCOM_CALLTYPE	CopyDataInto(void* pBuffer, size_t bufferSize) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetData(void* pBuffer, size_t bufferSize) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {3D7D62FB-4D99-40F2-8E87-9994DF64ED5D}
		static const VWIID IID_ZIPFile = { 0x3d7d62fb, 0x4d99, 0x40f2, { 0x8e, 0x87, 0x99, 0x94, 0xdf, 0x64, 0xed, 0x5d } };

		class DYNAMIC_ATTRIBUTE IZIPFile : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	OpenRead(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	OpenRead(const char* buffer, size_t length) = 0;
			virtual VCOMError VCOM_CALLTYPE	OpenWrite(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	OpenNewWrite(IFileIdentifier* pFileID, bool compressFiles = true) = 0;
			virtual VCOMError VCOM_CALLTYPE	Close() = 0;
			virtual VCOMError VCOM_CALLTYPE	ToBuffer(char*& p, size_t& lengt) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetSize(Uint64& outValue) = 0;

			// 'path' uses '/' delimited string to identify a file or folder within the zip file
			// empty 'path' denotes the root folder of the zip file

			virtual VCOMError VCOM_CALLTYPE	GetNextFile(const std::string& path, std::string& outPath) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetNextFile(const std::string& path, const std::string& extension, std::string& outPath) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetFileInfo(const std::string& path, SZIPFileInfo& outInfo) = 0;

			virtual VCOMError VCOM_CALLTYPE	GetFile(const std::string& path, IZIPFileIOBuffer* outputBuffer) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFile(const std::string& path, IFileIdentifier* outputFile) = 0;

			virtual VCOMError VCOM_CALLTYPE	AddFile(const TXString& path, IZIPFileIOBuffer* inputBuffer) = 0;
			virtual VCOMError VCOM_CALLTYPE	AddFile(const TXString& path, IFileIdentifier* inputFile) = 0;

			virtual VCOMError VCOM_CALLTYPE	RemoveFile(const TXString& path) = 0;
			//virtual VCOMError VCOM_CALLTYPE	MoveFile(const TXString& path) = 0;
		};
		typedef VCOMPtr<IZIPFile>		IZIPFilePtr;
	}
}


