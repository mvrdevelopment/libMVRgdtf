//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "ZIPFileBuffer.h"

using namespace VectorworksMVR::Filing;

const size_t k_5_MegaByte = 5 * 1024;

ZIPFileBuffer::ZIPFileBuffer()
{
	fpZIPFileBuffer		 = nullptr;
	fZIPFileBufferSize	 = 0;
	fAllocatedMemorySize = 0;
}

ZIPFileBuffer::~ZIPFileBuffer()
{
	if (fpZIPFileBuffer)
	{
		delete[] fpZIPFileBuffer;
	}
		
	fpZIPFileBuffer = nullptr;
}

VCOMError ZIPFileBuffer::Open(VectorworksMVR::Filing::IFileIdentifier* pFileID, bool openForRead)
{
	fOpenForRead   = openForRead;
	fpOpenedFileID = pFileID;

	if (fOpenForRead)
	{
		// prepare file
		IRawOSFilePtr file(IID_RawOSFile);

		// open file
		file->Open(pFileID, true, false, false, false);

		// get filesize
		file->GetFileSize(fZIPFileBufferSize);
		// load in buffer
		fpZIPFileBuffer      = new Uint8[fZIPFileBufferSize];
		fAllocatedMemorySize = fZIPFileBufferSize;
		file->Read(0, fZIPFileBufferSize, fpZIPFileBuffer);

		// close file
		file->Close();
	}

	return kVCOMError_NoError ;
}

VCOMError ZIPFileBuffer::Open(const char* buffer, size_t length)
{
	fOpenForRead   = true;

	if (fOpenForRead)
	{
		fZIPFileBufferSize = length;
		fpZIPFileBuffer      = new Uint8[fZIPFileBufferSize];
		fAllocatedMemorySize = fZIPFileBufferSize;
		memcpy(fpZIPFileBuffer, buffer, fZIPFileBufferSize);
	}

	return kVCOMError_NoError ;
}

VCOMError ZIPFileBuffer::Close()
{
	if (!fOpenForRead && fpZIPFileBuffer)
	{
		// prepare file
		IRawOSFilePtr file(IID_RawOSFile);

		// open file
		file->Open(fpOpenedFileID, false, true, false, false);

		file->Write(0, fZIPFileBufferSize, fpZIPFileBuffer);

		// close file
		file->Close();
	}

	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::GetFileSize(Uint64& outValue)
{
	outValue = fZIPFileBufferSize;
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer)
{
	memcpy(pOutBuffer, fpZIPFileBuffer + position, (size_t)inoutSize);
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Write(Uint64 position, Uint64 size, const void* pBuffer)
{
	// Check how much memory we need
	size_t needToAllocate = fZIPFileBufferSize + size;

	// When we already have enought memory, just copy
	if (fAllocatedMemorySize >= needToAllocate)
	{
		memcpy(fpZIPFileBuffer + fZIPFileBufferSize, pBuffer, size);
		fZIPFileBufferSize += size;
	}
	// Otherwise allocate more mempry
	else
	{
		// Calculate the new needed buffer
		fAllocatedMemorySize = needToAllocate + k_5_MegaByte;

		// Create new Buffer
		Uint8* tempBuffer = new Uint8[fAllocatedMemorySize];
		if(fpZIPFileBuffer)
		{
			memcpy(tempBuffer, fpZIPFileBuffer, fZIPFileBufferSize);
			delete[] fpZIPFileBuffer;
		}
		memcpy(tempBuffer + sizeof(Uint8) * fZIPFileBufferSize, pBuffer, size);

		// Set the new Buffer size
		fZIPFileBufferSize = fZIPFileBufferSize + (size_t)size;

		// Set the new Buffer
		fpZIPFileBuffer = tempBuffer;

	}

	return kVCOMError_NoError;
}

VCOMError VectorworksMVR::Filing::ZIPFileBuffer::CleanBuffer()
{
	if(fpZIPFileBuffer)
	{
		delete[] fpZIPFileBuffer;
	}
	fpZIPFileBuffer		= nullptr;
	fZIPFileBufferSize	= 0;
	fAllocatedMemorySize= 0;
	return kVCOMError_NoError;
}


void ZIPFileBuffer::Copy(char*& p, size_t& inLength)
{	
	inLength = fZIPFileBufferSize;
	p = new char[fZIPFileBufferSize];
	memcpy(p, fpZIPFileBuffer, inLength);
}