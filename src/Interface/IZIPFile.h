//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#pragma once

#include "IFileIdentifier.h"

#include <functional>
#include <string>
#include <vector>

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
		struct SZIPAddFileRequest
		{
			TXString			fPath;
			IZIPFileIOBuffer*	fBuffer	= nullptr;	// either fBuffer or fFile must be set
			IFileIdentifier*	fFile	= nullptr;
		};

		typedef std::function<void(size_t index, VCOMError error, IZIPFileIOBuffer& buffer)> TZIPGetFileCallback;

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

			// Batch API: data is read/compressed or inflated on worker threads, while the archive itself is
			// only modified on the calling thread. Each IFileIdentifier / IZIPFileIOBuffer passed in must be
			// a distinct object that is not used by anyone else during the call.

			// Adds all files in request order, equivalent to calling AddFile for every request.
			// outResults receives one error code per request.
			virtual VCOMError VCOM_CALLTYPE	AddFiles(const std::vector<SZIPAddFileRequest>& requests, std::vector<VCOMError>& outResults) = 0;

			// Returns the unique entry names in central directory order (duplicates are listed once, at their first position).
			virtual VCOMError VCOM_CALLTYPE	GetFileNames(std::vector<std::string>& outNames) = 0;

			// Extracts the given entries in parallel. callback(index, error, buffer) is invoked once per entry,
			// possibly from a worker thread and in any order. Errors for unsupported entries are reported on the
			// calling thread before extraction starts.
			virtual VCOMError VCOM_CALLTYPE	GetFiles(const std::vector<std::string>& names, const TZIPGetFileCallback& callback) = 0;
		};
		typedef VCOMPtr<IZIPFile>		IZIPFilePtr;
	}
}


