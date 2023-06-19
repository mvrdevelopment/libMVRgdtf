//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------namespace LightRightNetwork
#include "mvrxchange_prefix.h"
namespace MVRxchangeNetwork
{
    class MVRxchangeMessage
    {
        private:
            enum { header_flag            = sizeof(uint32_t) };
            enum { header_version         = sizeof(uint32_t) };
            enum { header_number          = sizeof(uint32_t) };
            enum { header_count           = sizeof(uint32_t) };
            enum { header_type            = sizeof(uint32_t) };
            enum { header_payload_length  = sizeof(uint64_t) };
        public:
            enum { total_header_length      = header_flag + header_version + header_number + header_count + header_type + header_payload_length };

        public:
            MVRxchangeMessage();
            MVRxchangeMessage(const MVRxchangeMessage& ref );
            MVRxchangeMessage(const MVRxchangeMessage* ref ) = delete;
            ~MVRxchangeMessage();

            const char*     GetData() const;
            char*           GetData();
            size_t          GetLength() const;
            const char*     GetBody() const;
            char*           GetBody();
            size_t          GetBodyLength() const;
            void            SetBody(size_t length, char* buffer);
            bool            DecodeHeader();
            void            EncodeHeader();

        private:
            size_t*		        fReferenceCount;
            char*               fdata;
            size_t              fBodyLength;
    };
    typedef std::deque<MVRxchangeMessage>     LRNetMessageQueue;
}