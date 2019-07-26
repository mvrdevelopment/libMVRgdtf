#include "Prefix/StdAfx.h"

#include "ZIPFileBuffer.h"

#ifdef _LINUX
#include <unistd.h>
#include <stdio.h>
#endif

using namespace VectorworksMVR::Filing;

ZIPFileBuffer::ZIPFileBuffer()
{
	fpZIPFileBuffer		= NULL;
	fZIPFileBufferSize	= 0;
}

ZIPFileBuffer::~ZIPFileBuffer()
{
	if (fpZIPFileBuffer)
		delete[] fpZIPFileBuffer;
	fpZIPFileBuffer = NULL;
}

VCOMError ZIPFileBuffer::Open(VectorworksMVR::Filing::IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting)
{
	// prepare file
	IRawOSFilePtr file(IID_RawOSFile);

	// open file
	file->Open(pFileID, bReadable, bWritable, bRandomAccess, bTruncateExisting);

	// get filesize
	Uint64 bufferSize;
	file->GetFileSize(bufferSize);

	// load in buffer
	Uint64 position = 0;
	Uint64 inoutSize = 1;
	file->Read(position, inoutSize, (void*)fpZIPFileBuffer);

	// close file
	file->Close();

	return kVCOMError_NoError ;
}

VCOMError ZIPFileBuffer::Close()
{
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::GetFileSize(Uint64& outValue)
{
	outValue = fZIPFileBufferSize;
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer)
{
	memcpy(pOutBuffer, fpZIPFileBuffer, inoutSize);
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Write(Uint64 position, Uint64 size, const void* pBuffer)
{
	//fFile->Write(position, size, pBuffer);
	// size_t bufferSize = 1048576; // 1MBytes * 1024 * 1024 = 1048576 Bytes
	Uint8* tempBuffer = new Uint8[fZIPFileBufferSize + size + 1];
	memcpy(tempBuffer, fpZIPFileBuffer, fZIPFileBufferSize);
	memcpy(tempBuffer + sizeof(Uint8) * fZIPFileBufferSize, pBuffer, size);
	fZIPFileBufferSize += size;
	delete[] fpZIPFileBuffer;

	fpZIPFileBuffer = new Uint8[fZIPFileBufferSize + 1];
	memcpy(fpZIPFileBuffer, tempBuffer, fZIPFileBufferSize + 1);

	if (tempBuffer)
		delete[] tempBuffer;

	return kVCOMError_NoError;
}

