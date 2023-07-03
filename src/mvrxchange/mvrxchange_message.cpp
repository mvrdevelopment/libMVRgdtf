//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------namespace LightRightNetwork
#include "mvrxchange_prefix.h"
#include "json.h"
#include "mvrxchange_message.h"

using namespace MVRxchangeNetwork;


MVRxchangePacket::MVRxchangePacket()
{
    fFlag       = kMVR_Package_Flag;
    fNumber     = 0;
    fCount      = 0;
    fType       = 0;
    fBodyLength = 0;
    fData       = new MVRxchangeDynamicBuffer();

    fReferenceCount = new size_t(1);
}

MVRxchangePacket::MVRxchangePacket(const MVRxchangePacket& ref)
{
    fBodyLength = ref.fBodyLength;
    fData       = ref.fData;
    
    fReferenceCount = ref.fReferenceCount;
	
	// Increase reference Count by one
	(*fReferenceCount)++;
}


MVRxchangePacket::~MVRxchangePacket()
{
    (*fReferenceCount)--;
    if (*fReferenceCount == 0)
	{
		// Release pointer
		delete fData;
		
		// Release reference pointer
		delete fReferenceCount;
	}
   
}

const char* MVRxchangePacket::GetData() const
{
    return fData->GetData();
}

char* MVRxchangePacket::GetData()
{
    return fData->GetData();
}

size_t MVRxchangePacket::GetLength() const
{
    return total_header_length + fBodyLength;
}

const char* MVRxchangePacket::GetBody() const
{
    return fData->GetData() + total_header_length; // XXX MS verify 
}

char* MVRxchangePacket::GetBody()
{
    return fData->GetData() + total_header_length; // XXX MS verify 
}

size_t MVRxchangePacket::GetBodyLength() const
{
    return fBodyLength;
}

void MVRxchangePacket::SetBody(size_t length, char* buffer)
{
    fBodyLength = length;
    fData->GrowTo(total_header_length + length);
    memcpy(GetBody(), buffer, length);
}

bool MVRxchangePacket::DecodeHeader()
{
    memcpy(&fFlag, fData, header_flag);
    if (fFlag != kMVR_Package_Flag) { return false; }

    memcpy(&fVersion,    fData + header_flag, header_version);
    memcpy(&fNumber,     fData + header_flag + header_version, header_number);
    memcpy(&fCount,      fData + header_flag + header_version + header_number, header_count);
    memcpy(&fType,       fData + header_flag + header_version + header_number + header_count, header_type);
    memcpy(&fBodyLength, fData + header_flag + header_version + header_number + header_type, header_payload_length);

    // Prepare Buffer
    fData->GrowTo(fBodyLength);

    return true;
}

void MVRxchangePacket::EncodeHeader()
{
    memcpy(fData,                                                                               &fFlag,                 header_flag);
    memcpy(fData + header_flag,                                                                 &fVersion,              header_version);
    memcpy(fData + header_flag + header_version,                                                &fNumber,               header_number);
    memcpy(fData + header_flag + header_version + header_number,                                &fCount,                header_count);
    memcpy(fData + header_flag + header_version + header_number + header_count,                 &fType,                 header_type);
    memcpy(fData + header_flag + header_version + header_number + header_count + header_type,   &fBodyLength,           header_payload_length);
}

void MVRxchangePacket::FromExternalMessage(const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    nlohmann::json payload = nlohmann::json::object();

    switch (in.Type)
    {
    case IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN:
        payload["type"]         = "MVR_JOIN";
        payload["provider"]     = in.JOIN.Provider;
        payload["stationName"]  = in.JOIN.StationName;
        payload["verMajor"]     = in.JOIN.VersionMajor;
        payload["verMinor"]     = in.JOIN.VersionMinor;
        break;
    
    default:
        break;
    }

    std::string s = payload.dump();

    fFlag       = kMVR_Package_Flag;
    fNumber     = 1;
    fCount      = 1;
    fType       = kMVR_Package_JSON_TYPE;
    fBodyLength = s.size();

    fData->GrowTo(fBodyLength);
    fData->FromBuffer(s.data(), s.size());

}

void MVRxchangePacket::ToExternalMessage(VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    if(fType == kMVR_Package_JSON_TYPE && fBodyLength > 0)
    {
        nlohmann::json payload = nlohmann::json::parse(fData->GetData(), nullptr, false);
        
        if(payload.type() ==  nlohmann::json::value_t::object)
        {
            if(payload["type"] == "MVR_JOIN")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN;
                in.JOIN.VersionMajor= payload["verMajor"];
                in.JOIN.VersionMinor= payload["verMinor"];
                strcpy(in.JOIN.Provider, payload["provider"].get<std::string>().c_str());
                strcpy(in.JOIN.StationName, payload["stationName"].get<std::string>().c_str());
            }
        }
    }
}
