#include "Prefix/StdAfx.h"

#include "ZIPFileBuffer.h"

#ifdef _LINUX
#include <unistd.h>
#include <stdio.h>
#endif

using namespace VectorworksMVR::Filing;

ZIPFileBuffer::ZIPFileBuffer()
{
	IRawOSFilePtr file (IID_RawOSFile);
}

ZIPFileBuffer::~ZIPFileBuffer()
{
}

VCOMError ZIPFileBuffer::Open(VectorworksMVR::Filing::IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting)
{
	file->Open(pFileID, true, true, false, false);
	return kVCOMError_NoError ;
}

VCOMError ZIPFileBuffer::Close()
{
	file->Close();
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::GetFileSize(Uint64& outValue)
{
	outValue = fZIPDataBufferSize;
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer)
{
	memcpy(pOutBuffer, fpZIPDataBuffer + position, inoutSize);

	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Write(Uint64 position, Uint64 size, const void* pBuffer)
{
	// size_t bufferSize = 1048576; // 1MBytes * 1024 * 1024 = 1048576 Bytes
	Uint8* tempBuffer = new Uint8[ fZIPDataBufferSize + size + 1];// + 1 ];
	memcpy( tempBuffer,  fpZIPDataBuffer, fZIPDataBufferSize );
	memcpy( tempBuffer + sizeof( Uint8 ) * fZIPDataBufferSize, pBuffer, size );
	fZIPDataBufferSize += size;
	delete [] fpZIPDataBuffer;

	fpZIPDataBuffer = new Uint8[ fZIPDataBufferSize + 1 ];
	memcpy( fpZIPDataBuffer, tempBuffer, fZIPDataBufferSize + 1);

	if ( tempBuffer )
		delete [] tempBuffer;

	return kVCOMError_NoError;
}

