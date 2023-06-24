//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

namespace MVRxchangeNetwork
{
    class MVRxchangeDynamicBuffer
    {
        public:
        MVRxchangeDynamicBuffer();
        MVRxchangeDynamicBuffer(const MVRxchangeDynamicBuffer& copy);
        MVRxchangeDynamicBuffer& operator=(const MVRxchangeDynamicBuffer&);
        ~MVRxchangeDynamicBuffer();

        public:
        void                    FromBuffer(const char* data, size_t length);
        void                    FromBuffer(const MVRxchangeDynamicBuffer& );

        void                    Reserve(size_t size);
        void                    GrowTo(size_t size);
        void                    Append(size_t size, const void* pBuffer);
        void                    DisposeBuffer();
        const size_t&           Length() const;
        char*                   GetData() const;

        private:
        char*           fBuffer;
        size_t          fBufferSize;
        size_t          fAllocatedMemory;
        size_t*	        fReferenceCount;
    };

}
