//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------
#include "mvrxchange_prefix.h"
#include "mvrxchange_dynamic_buffer.h"

using namespace MVRxchangeNetwork;
 
const size_t k_5_MegaByte = 5 * 1024;


MVRxchangeDynamicBuffer::MVRxchangeDynamicBuffer()
{
    fReferenceCount = new size_t(1);

    fBuffer             = nullptr;
    fBufferSize         = 0;
    fAllocatedMemory    = 0;
}

MVRxchangeDynamicBuffer::MVRxchangeDynamicBuffer(const MVRxchangeDynamicBuffer& copy)
{
    fBufferSize         = copy.fBufferSize;
    fBuffer             = copy.fBuffer;
    fAllocatedMemory    = copy.fBufferSize;

	// Increase reference Count by one
    fReferenceCount = copy.fReferenceCount;
	(*fReferenceCount)++;
}

MVRxchangeDynamicBuffer& MVRxchangeDynamicBuffer::operator=(const MVRxchangeDynamicBuffer& copy)
{
    DisposeBuffer();
    fBufferSize         = copy.fBufferSize;
    fBuffer             = copy.fBuffer;
    fAllocatedMemory    = copy.fBufferSize;

	// Increase reference Count by one
    fReferenceCount = copy.fReferenceCount;
	(*fReferenceCount)++;
    return *this;
}


MVRxchangeDynamicBuffer::~MVRxchangeDynamicBuffer()
{
	// Decrease refence count
	(*fReferenceCount)--;
	
	// If this is the last matrix
	if (*fReferenceCount == 0)
	{
		// Release pointer
		DisposeBuffer();
		
		// Release reference pointer
		delete fReferenceCount;
	}
}

void MVRxchangeDynamicBuffer::DisposeBuffer()
{
    if(fBuffer)
    {
        delete [] fBuffer;
    }
    fBuffer          = nullptr;
    fBufferSize      = 0;
    fAllocatedMemory = 0;
}

void MVRxchangeDynamicBuffer::FromBuffer(const MVRxchangeDynamicBuffer& buffer)
{
    FromBuffer(buffer.GetData(), buffer.Length());
}

void MVRxchangeDynamicBuffer::FromBuffer(const char* data, size_t length)
{
    if(length == 0) { return; }
    DisposeBuffer();
    fBufferSize  = length;
    fBuffer      = new char[length];
    memcpy(fBuffer, data, fBufferSize);    
    fAllocatedMemory  = fBufferSize;
}

void MVRxchangeDynamicBuffer::Append(size_t size, const void* pBuffer)
{
    if(size == 0) { return; }
    // Check how much memory we need
	size_t needToAllocate = fBufferSize + size;

	// When we already have enought memory, just copy
	if (fAllocatedMemory >= needToAllocate)
	{
		memcpy(fBuffer + fBufferSize, pBuffer, size);
		fBufferSize += size;
	}
	// Otherwise allocate more mempry
	else
	{
		// Calculate the new needed buffer
		fAllocatedMemory = needToAllocate + k_5_MegaByte;

		// Create new Buffer
		char* tempBuffer = new char[fAllocatedMemory];
		if(fBuffer)
		{
			memcpy(tempBuffer, fBuffer, fBufferSize);
			delete[] fBuffer;
		}
		memcpy(tempBuffer + sizeof(Uint8) * fBufferSize, pBuffer, size);

		// Set the new Buffer size
		fBufferSize = fBufferSize + (size_t)size;

		// Set the new Buffer
		fBuffer = tempBuffer;

	}

}


void MVRxchangeDynamicBuffer::GrowTo(size_t size)
{
    // Check how much memory we need
	size_t needToAllocate = size + 1;

	// When we already have enought memory, just copy
	if (fAllocatedMemory < needToAllocate)
	{
		// Calculate the new needed buffer
		fAllocatedMemory = needToAllocate;

		// Create new Buffer
		char* tempBuffer = new char[fAllocatedMemory];
		if(fBuffer)
		{
			memcpy(tempBuffer, fBuffer, fBufferSize);
			delete[] fBuffer;
		}

		// Set the new Buffer size
		fBufferSize = fBufferSize + (size_t)size;

		// Set the new Buffer
		fBuffer = tempBuffer;

	}

}

void MVRxchangeDynamicBuffer::Reserve(size_t size)
{
    // Check how much memory we need
    size_t needToAllocate = size + 1;

    // When we already have enought memory, just copy
    if (fAllocatedMemory < needToAllocate)
    {
        // Calculate the new needed buffer
        fAllocatedMemory = needToAllocate;

        // Create new Buffer
        char* tempBuffer = new char[fAllocatedMemory];
        if(fBuffer)
        {
            memcpy(tempBuffer, fBuffer, fBufferSize);
            delete[] fBuffer;
            fBufferSize = fBufferSize + (size_t)size;
        }

        // Set the new Buffer size

        // Set the new Buffer
        fBuffer = tempBuffer;

    }

}

const size_t& MVRxchangeDynamicBuffer::Length() const
{
    return fBufferSize;
}

char* MVRxchangeDynamicBuffer::GetData() const
{
    return fBuffer;
}
