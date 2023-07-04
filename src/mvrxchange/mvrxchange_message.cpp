//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------namespace LightRightNetwork
#include "mvrxchange_prefix.h"
#include "json.h"
#include "mvrxchange_message.h"
#include "XmlFileHelper.h"

using namespace MVRxchangeNetwork;


MVRxchangePacket::MVRxchangePacket()
{
    fFlag       = kMVR_Package_Flag;
    fNumber     = 0;
    fCount      = 0;
    fType       = 0;
    fBodyLength = 0;
    fData       = new MVRxchangeDynamicBuffer();
    fData->GrowTo(30 * 1024 * 1024);

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
    return fData->GetData() + total_header_length;
}

char* MVRxchangePacket::GetBody()
{
    return fData->GetData() + total_header_length;
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
    memcpy(&fFlag, fData->GetData(), header_flag);
    if (fFlag != kMVR_Package_Flag) { return false; }

    memcpy(&fVersion,    GetData() + header_flag, header_version);
    memcpy(&fNumber,     GetData() + header_flag + header_version, header_number);
    memcpy(&fCount,      GetData() + header_flag + header_version + header_number, header_count);
    memcpy(&fType,       GetData() + header_flag + header_version + header_number + header_count, header_type);
    memcpy(&fBodyLength, GetData() + header_flag + header_version + header_number + header_count + header_type, header_payload_length);

    // Prepare Buffer
    fData->GrowTo(fBodyLength);

    return true;
}

void MVRxchangePacket::EncodeHeader()
{
    memcpy(GetData(),                                                                               &fFlag,                 header_flag);
    memcpy(GetData() + header_flag,                                                                 &fVersion,              header_version);
    memcpy(GetData() + header_flag + header_version,                                                &fNumber,               header_number);
    memcpy(GetData() + header_flag + header_version + header_number,                                &fCount,                header_count);
    memcpy(GetData() + header_flag + header_version + header_number + header_count,                 &fType,                 header_type);
    memcpy(GetData() + header_flag + header_version + header_number + header_count + header_type,   &fBodyLength,           header_payload_length);
}

void MVRxchangePacket::FromExternalMessage(const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    nlohmann::json payload = nlohmann::json::object();

    switch (in.Type)
    {
    case IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN_RET:
        payload["OK"]           = in.RetIsOK;
        payload["Message"]      = in.RetError;
        payload["Type"]         = "MVR_JOIN_RET";
        payload["provider"]     = in.JOIN.Provider;
        payload["stationName"]  = in.JOIN.StationName;
        payload["verMajor"]     = in.JOIN.VersionMajor;
        payload["verMinor"]     = in.JOIN.VersionMinor;
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN:
        payload["Type"]         = "MVR_JOIN";
        payload["provider"]     = in.JOIN.Provider;
        payload["stationName"]  = in.JOIN.StationName;
        payload["verMajor"]     = in.JOIN.VersionMajor;
        payload["verMinor"]     = in.JOIN.VersionMinor;
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT_RET:
        payload["OK"]               = in.RetIsOK;
        payload["Message"]          = in.RetError;
        payload["Type"]             = "MVR_COMMIT_RET";
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT:
        payload["Type"]             = "MVR_COMMIT";
        payload["FileSize"]         = in.COMMIT.FileSize;
        payload["Comment"]          = in.COMMIT.Comment;
        payload["FileUUID"]         = SceneData::GdtfConverter::ConvertUUID(VWUUID(in.COMMIT.FileUUID.a, in.COMMIT.FileUUID.b, in.COMMIT.FileUUID.c, in.COMMIT.FileUUID.d)).GetStdString();
        payload["StationUUID"]      = SceneData::GdtfConverter::ConvertUUID(VWUUID(in.COMMIT.StationUUID.a, in.COMMIT.StationUUID.b, in.COMMIT.StationUUID.c, in.COMMIT.StationUUID.d)).GetStdString();
        payload["verMinor"]         = in.COMMIT.VersionMinor;
        payload["verMajor"]         = in.COMMIT.VersionMajor;
        payload["ForStationsUUID"]  = nlohmann::json::array();
        for(const auto& e : in.COMMIT.ForStations)
        {
            payload["ForStationsUUID"].push_back(SceneData::GdtfConverter::ConvertUUID(VWUUID(e.a, e.b, e.c, e.d)).GetStdString());
        }
        break;    
    case IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST:
        payload["Type"]             = "MVR_REQUEST";
        payload["FileUUID"]         = SceneData::GdtfConverter::ConvertUUID(VWUUID(in.REQUEST.FileUUID.a, in.REQUEST.FileUUID.b, in.REQUEST.FileUUID.c, in.REQUEST.FileUUID.d)).GetStdString();
        payload["FromStationUUID"]  = nlohmann::json::array();
        for(const auto& e : in.REQUEST.FromStationUUID)
        {
            payload["FromStationUUID"].push_back(SceneData::GdtfConverter::ConvertUUID(VWUUID(e.a, e.b, e.c, e.d)).GetStdString());
        }
        break;
    case IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST_RET:
        payload["Type"]             = "MVR_REQUEST_RET";
        payload["OK"]               = in.RetIsOK;
        payload["Message"]          = in.RetError;

        break;
    default:
        break;
    }


    fFlag       = kMVR_Package_Flag;
    fNumber     = 1;
    fCount      = 1;

    if(in.Type == IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST_RET && in.RetIsOK)
    {
        IFileIdentifierPtr file (IID_FileIdentifier);
        file->Set(in.PathToFile.fBuffer);

        Uint64 size = 0;
        IRawOSFilePtr rawFile (IID_RawOSFile);
        rawFile->Open(file, true, false,true, false);
        rawFile->GetFileSize(fBodyLength);
        rawFile->Read(0, fBodyLength, GetBody());
        fData->GrowTo(fBodyLength + total_header_length);
        rawFile->Close();

        fType       = kMVR_Package_BUFFER_TYPE;
    }
    else
    {
        std::string s = payload.dump();
        fBodyLength = s.size();
        fType       = kMVR_Package_JSON_TYPE;

        fData->GrowTo(fBodyLength + total_header_length);
        memcpy(GetBody(), s.data(), fBodyLength);
    }

    EncodeHeader();
}

void MVRxchangePacket::ToExternalMessage(VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& in)
{
    if(fType == kMVR_Package_JSON_TYPE && fBodyLength > 0)
    {
        nlohmann::json payload = nlohmann::json::parse(this->GetBody(),this->GetBody() + fBodyLength,  nullptr, false, true);
        
        if(payload.type() ==  nlohmann::json::value_t::object)
        {
            if(payload["Type"] == "MVR_JOIN")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN;
                in.JOIN.VersionMajor= payload["verMajor"];
                in.JOIN.VersionMinor= payload["verMinor"];
                strcpy(in.JOIN.Provider, payload["provider"].get<std::string>().c_str());
                strcpy(in.JOIN.StationName, payload["stationName"].get<std::string>().c_str());
            }
            else if(payload["Type"] == "MVR_JOIN_RET")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN_RET;
                in.JOIN.VersionMajor= payload["verMajor"];
                in.JOIN.VersionMinor= payload["verMinor"];
                strcpy(in.JOIN.Provider, payload["provider"].get<std::string>().c_str());
                strcpy(in.JOIN.StationName, payload["stationName"].get<std::string>().c_str());

                in.RetIsOK = payload["OK"].get<bool>();
                strcpy(in.RetError, payload["Message"].get<std::string>().c_str());

            }
            else if(payload["Type"] == "MVR_COMMIT")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT;
                strcpy(in.COMMIT.Comment, payload["Comment"].get<std::string>().c_str());
                in.COMMIT.VersionMajor= payload["verMajor"];
                in.COMMIT.VersionMinor= payload["verMinor"];
                in.COMMIT.FileSize= payload["FileSize"];

                SceneData::GdtfConverter::ConvertUUID(payload["FileUUID"].get<std::string>(), in.COMMIT.FileUUID);
                SceneData::GdtfConverter::ConvertUUID(payload["StationUUID"].get<std::string>(), in.COMMIT.StationUUID);
                // TODO ForStationsUUID
            }
            else if(payload["Type"] == "MVR_COMMIT_RET")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_COMMIT_RET;
                in.RetIsOK = payload["OK"].get<bool>();
                strcpy(in.RetError, payload["Message"].get<std::string>().c_str());
            }
            else if(payload["Type"] == "MVR_REQUEST")
            {
                in.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST;
                SceneData::GdtfConverter::ConvertUUID(payload["FileUUID"].get<std::string>(), in.REQUEST.FileUUID);

                // TODO ForStationsUUID
            }
        }
    }
    else if(fType == kMVR_Package_BUFFER_TYPE && fBodyLength > 0)
    {
        // Nothing to do

    }
}
