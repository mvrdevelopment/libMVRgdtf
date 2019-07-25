#include "Prefix/StdAfx.h"

#include "ZIPFileBuffer.h"

#ifdef _LINUX
#include <unistd.h>
#include <stdio.h>
#endif

using namespace VectorworksMVR::Filing;

ZIPFileBuffer::ZIPFileBuffer() : fFile (IID_RawOSFile)
{
}

ZIPFileBuffer::~ZIPFileBuffer()
{
}

VCOMError ZIPFileBuffer::Open(VectorworksMVR::Filing::IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting)
{
	fFile->Open(pFileID, bReadable, bWritable, bRandomAccess, bTruncateExisting);
	return kVCOMError_NoError ;
}

VCOMError ZIPFileBuffer::Close()
{
	fFile->Close();
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::GetFileSize(Uint64& outValue)
{
	fFile->GetFileSize(outValue);
	// outValue = fZIPDataBufferSize;
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer)
{
	// fFile->Read(position, inoutSize, pOutBuffer);
	memcpy(pOutBuffer, fpZIPDataBuffer + position, inoutSize);
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Write(Uint64 position, Uint64 size, const void* pBuffer)
{
	fFile->Write(position, size, pBuffer);
	// // size_t bufferSize = 1048576; // 1MBytes * 1024 * 1024 = 1048576 Bytes
	// Uint8* tempBuffer = new Uint8[ fZIPDataBufferSize + size + 1];// + 1 ];
	// memcpy( tempBuffer,  fpZIPDataBuffer, fZIPDataBufferSize );
	// memcpy( tempBuffer + sizeof( Uint8 ) * fZIPDataBufferSize, pBuffer, size );
	// fZIPDataBufferSize += size;
	// delete [] fpZIPDataBuffer;

	// fpZIPDataBuffer = new Uint8[ fZIPDataBufferSize + 1 ];
	// memcpy( fpZIPDataBuffer, tempBuffer, fZIPDataBufferSize + 1);

	// if ( tempBuffer )
	// 	delete [] tempBuffer;

	return kVCOMError_NoError;
}

