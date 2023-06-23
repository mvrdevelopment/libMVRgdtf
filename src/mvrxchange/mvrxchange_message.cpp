//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------namespace LightRightNetwork
#include "mvrxchange_prefix.h"
#include "json.h"
using namespace MVRxchangeNetwork;


MVRxchangeMessage::MVRxchangeMessage()
{
    fFlag       = kMVR_Package_Flag;
    fNumber     = 0;
    fCount      = 0;
    fType       = 0;
    fBodyLength = 0;

    fReferenceCount = new size_t(1);
}

MVRxchangeMessage::MVRxchangeMessage(const MVRxchangeMessage& ref)
{
    fBodyLength = ref.fBodyLength;
    fData       = ref.fData;
    
    fReferenceCount = ref.fReferenceCount;
	
	// Increase reference Count by one
	(*fReferenceCount)++;
}


MVRxchangeMessage::~MVRxchangeMessage()
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

const char* MVRxchangeMessage::GetData() const
{
    return fData->GetData();
}

char* MVRxchangeMessage::GetData()
{
    return fData->GetData();
}

size_t MVRxchangeMessage::GetLength() const
{
    return total_header_length + fBodyLength;
}

const char* MVRxchangeMessage::GetBody() const
{
    return fData->GetData() + total_header_length; // XXX MS verify 
}

char* MVRxchangeMessage::GetBody()
{
    return fData->GetData() + total_header_length; // XXX MS verify 
}

size_t MVRxchangeMessage::GetBodyLength() const
{
    return fBodyLength;
}

void MVRxchangeMessage::SetBody(size_t length, char* buffer)
{
    fBodyLength = length;
    fData->GrowTo(total_header_length + length);
    memcpy(GetBody(), buffer, length);
}

bool MVRxchangeMessage::DecodeHeader()
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

void MVRxchangeMessage::EncodeHeader()
{
    memcpy(fData,                                                                               &fFlag,                 header_flag);
    memcpy(fData + header_flag,                                                                 &fVersion,              header_version);
    memcpy(fData + header_flag + header_version,                                                &fNumber,               header_number);
    memcpy(fData + header_flag + header_version + header_number,                                &fCount,                header_count);
    memcpy(fData + header_flag + header_version + header_number + header_count,                 &fType,                 header_type);
    memcpy(fData + header_flag + header_version + header_number + header_count + header_type,   &fBodyLength,           header_payload_length);
}

void MVRxchangeMessage::FromExternalMessage(const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    nlohmann::json payload = nlohmann::json::object();

    switch (in.Type)
    {
    case VectorworksMVR::IMVRxchangeService:::MVRxchangeMessageType::MVR_JOIN:
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

void MVRxchangeMessage::ToExternalMessage(VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    if(fType == kMVR_Package_JSON_TYPE)
    {
        nlohmann::json payload = nlohmann::json::parse(fData->GetData(), nullptr, false);

        if(payload.type() == nlohmann::json::type::object)
        {
            if(payload["type"] == "MVR_JOIN")
            {
                in.Type = VectorworksMVR::IMVRxchangeService:::MVRxchangeMessageType::MVR_JOIN;
                in.JOIN.Provider    = payload["provider"];
                in.JOIN.StationName = payload["stationName"];
                in.JOIN.VersionMajor= payload["verMajor"];
                in.JOIN.VersionMinor= payload["verMinor"];
            }
        }
    }
}