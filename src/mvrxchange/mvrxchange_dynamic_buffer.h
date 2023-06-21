//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------

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
        void                    FromBuffer(const IFileBuffer& );

        void                    Reserve(Uint64 size);
        void                    GrowTo(Uint64 size);
        void                    Append(Uint64 size, const void* pBuffer);
        void                    DisposeBuffer();
        const Uint64&           Length() const;
        char*                   Data() const;

        private:
        char*           fBuffer;
        Uint64          fBufferSize;
        Uint64          fAllocatedMemory;
        size_t*	        fReferenceCount;



    };

}
