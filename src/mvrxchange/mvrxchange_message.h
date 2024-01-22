//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once

#include "mvrxchange_prefix.h"
#include "mvrxchange_dynamic_buffer.h"
#include "json.h"

namespace MVRxchangeNetwork
{
    class MVRxchangePacket
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
            MVRxchangePacket();
            MVRxchangePacket(const MVRxchangePacket& ref );
            MVRxchangePacket(const MVRxchangePacket* ref ) = delete;
            ~MVRxchangePacket();

            const char*     GetData() const;
            char*           GetData();
            size_t          GetLength() const;
            const char*     GetBody() const;
            char*           GetBody();
            size_t          GetBodyLength() const;
            void            SetBody(size_t length, char* buffer);
            bool            DecodeHeader();
            void            EncodeHeader();


            void            FromExternalMessage(const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage&);
            void            ToExternalMessage(VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage&);
#ifdef IS_UNITTEST
            void            FromString(const std::string& in);
            std::string     ToString();
#endif

        private:
            void            Internal_ToExternalMessage(const nlohmann::json& payload, VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage &in);


            uint32_t            fFlag;
            uint32_t            fVersion;
            uint32_t            fNumber;
            uint32_t            fCount;
            uint32_t            fType;
            uint64_t            fBodyLength;

            std::shared_ptr<MVRxchangeNetwork::MVRxchangeDynamicBuffer>  fData;
    };
    
    using MVRxchangePacketDeque = std::deque<MVRxchangePacket>;    
}