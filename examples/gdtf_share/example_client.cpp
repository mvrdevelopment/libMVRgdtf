#include <iostream>
#include <thread>
#include "Include/VectorworksMVR.h"
#include "Prefix/StdAfx.h"

using MSG_TYPE = VectorworksMVR::IMVRxchangeService::MVR_COMMIT_MESSAGE;

struct GlobalData
{
    VectorworksMVR::IMVRxchangeService::ConnectToLocalServiceArgs  connArgs;
};

std::vector<MSG_TYPE> PseudoFiles(GlobalData &data)
{

    VectorworksMVR::VWFC::Tools::VWUUID uuid;
    uuid.New();

    std::vector<MSG_TYPE> out;

    MSG_TYPE t;
    strcpy(t.Comment, "Example File 1");
    t.FileSize = 1024;                                  // Should have correct file size
    t.StationUUID = data.connArgs.StationUUID;
    t.FileUUID = VectorworksMVR::MvrUUID(1, 2, 3, 4);   // Should be based on file in production environment
    t.VersionMajor = 5;                                 // MVR Version
    t.VersionMinor = 1;                                 // MVR Version

    out.push_back(t);

    return out;
}

VectorworksMVR::IMVRxchangeServicePtr service(VectorworksMVR::IID_IMVRxchangeService);

using MsgType = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType;
VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage onMsg(const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage &args, void *context)
{
    // The connection is still open during this callback, so
    // - you cannot use Send_message here
    // - this function should conclude as fast as possible, otherwise there will be a timeout

    GlobalData &data = *((GlobalData *)context);

    VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage out;

    switch (args.Type)
    {
        case MsgType::MVR_UNDEFINED:        std::cout << "New Message: " << "MVR_UNDEFINED"         << std::endl; break;
        case MsgType::MVR_JOIN:             std::cout << "New Message: " << "MVR_JOIN"              << std::endl; break;
        case MsgType::MVR_LEAVE:            std::cout << "New Message: " << "MVR_LEAVE"             << std::endl; break;
        case MsgType::MVR_COMMIT:           std::cout << "New Message: " << "MVR_COMMIT"            << std::endl; break;
        case MsgType::MVR_REQUEST:          std::cout << "New Message: " << "MVR_REQUEST"           << std::endl; break;
        case MsgType::MVR_JOIN_RET:         std::cout << "New Message: " << "MVR_JOIN_RET"          << std::endl; break;
        case MsgType::MVR_LEAVE_RET:        std::cout << "New Message: " << "MVR_LEAVE_RET"         << std::endl; break;
        case MsgType::MVR_COMMIT_RET:       std::cout << "New Message: " << "MVR_COMMIT_RET"        << std::endl; break;
        case MsgType::MVR_REQUEST_RET:      std::cout << "New Message: " << "MVR_REQUEST_RET"       << std::endl; break;
        case MsgType::MVR_NEW_SESSION_HOST: std::cout << "New Message: " << "MVR_NEW_SESSION_HOST"  << std::endl; break;
    }

    // Proper error handling needed
    // If args.Type == MsgType::MVR_UNDEFINED && args.RetIsOK == false -> Could not parse json object at all
    // If args.Type != MsgType::MVR_UNDEFINED && args.RetIsOK == false -> Partial json parsing succeeded
    // args.RetError specifies the error in more detail
    if(!args.RetIsOK)
    {
        std::cerr << args.RetError.fBuffer << std::endl;
        return out;
    }

    // On join
    if (args.Type == MsgType::MVR_JOIN)
    {
        out.Type = MsgType::MVR_JOIN_RET;
        out.JOIN.Commits = PseudoFiles(data); // Return available Files to new Client
        strcpy(out.JOIN.StationName, data.connArgs.StationName);
        strcpy(out.JOIN.Provider, data.connArgs.Provider);
        out.JOIN.StationUUID = data.connArgs.StationUUID;
        out.JOIN.VersionMajor = data.connArgs.VersionMajor;
        out.JOIN.VersionMinor = data.connArgs.VersionMinor;

        std::cout << "New Client: " << args.JOIN.Provider << " -> " << args.JOIN.StationName << std::endl;
        std::cout << "Available Files on station " << args.JOIN.Provider << " -> " << args.JOIN.StationName << ":" << std::endl;
        for (auto &it : args.JOIN.Commits)
        {
            VectorworksMVR::VWFC::Tools::VWUUID uuid(it.FileUUID.a, it.FileUUID.b, it.FileUUID.c, it.FileUUID.d);
            std::cout << uuid.ToString(true).GetStdString() << "  " << it.Comment << std::endl;
        }
    }
    else if (args.Type == MsgType::MVR_JOIN_RET)
    {
        std::cout << "Available Files on station " << args.JOIN.Provider << " -> " << args.JOIN.StationName << ":" << std::endl;
        for (auto &it : args.JOIN.Commits)
        {
            VectorworksMVR::VWFC::Tools::VWUUID uuid(it.FileUUID.a, it.FileUUID.b, it.FileUUID.c, it.FileUUID.d);
            std::cout << uuid.ToString(true).GetStdString() << "  " << it.Comment << std::endl;
        }
        // _RET types are not handled in any other way, so no need to set any properties of "out" object;
    }
    else if(args.Type == MsgType::MVR_LEAVE)
    {
        out.Type = MsgType::MVR_LEAVE_RET;
        VectorworksMVR::VWFC::Tools::VWUUID station(args.LEAVE.FromStationUUID.a, args.LEAVE.FromStationUUID.b, args.LEAVE.FromStationUUID.c, args.LEAVE.FromStationUUID.d);
        std::cout << "Station left: " << station.ToString(true).GetStdString() << std::endl;
    }
    else if (args.Type == MsgType::MVR_REQUEST)
    {
        out.Type = MsgType::MVR_REQUEST_RET;

        if(args.REQUEST.FileUUID == VectorworksMVR::MvrUUID(1, 2, 3, 4))
        {
            // found file
            // Buffers as well as File Paths can be sent ussing either (.BufferToFile and .BufferToFileLength) or (.PathToFile)
            out.REQUEST.FileUUID = VectorworksMVR::MvrUUID(1, 2, 3, 4);
            out.RetIsOK = true;

            // Random data -> NOT A VALID MVR FILE; Use you own Test File for testing
            // Housekeeping is done by the lib, so no need to call delete[] on BufferToFile
            out.BufferToFile = new char[1024]; 
            out.BufferToFileLength = 1024;

            std::cout << "Returned requested file" << std::endl;
        }
        else
        {
            out.RetIsOK = false;
            strcpy(out.RetError, "Unable to find requested file");
            std::cout << "Unable to find requested file" << std::endl;
        }
    }
    else if (args.Type == MsgType::MVR_REQUEST_RET)
    {
        if(args.RetIsOK)
        {
            std::cout << "Other station could not find requested file";
        }
        else
        {
            // While files can be sent using the path or a buffer, 
            // received files can only be read using the .BufferToFile and .BufferToFileLength. 
            // Data is not stored on disk in any way by the lib
            std::cout << "Got file requested file with size " << args.BufferToFileLength << std::endl;
            
            // Memory of BufferToFile is available till the end of this callback, 
            // so it must be copied out before that. e.g.
            // memcpy(__dest__, args.BufferToFile, args.BufferToFileLength);

            // Discarding file for now
        }
    }
    else if(args.Type == MsgType::MVR_COMMIT)
    {
        out.Type = MsgType::MVR_COMMIT_RET;

        VectorworksMVR::VWFC::Tools::VWUUID station(args.COMMIT.StationUUID.a, args.COMMIT.StationUUID.b, args.COMMIT.StationUUID.c, args.COMMIT.StationUUID.d);
        VectorworksMVR::VWFC::Tools::VWUUID file(args.COMMIT.FileUUID.a, args.COMMIT.FileUUID.b, args.COMMIT.FileUUID.c, args.COMMIT.FileUUID.d);

        std::cout << "New file available on station " << station.ToString(true).GetStdString() << " -> " << file.ToString(true).GetStdString() << std::endl;
        // It is the users responsibility to match the UUIDS to stations and files.
    }
    else if(args.Type == MsgType::MVR_NEW_SESSION_HOST)
    {
        // Not implemented
    }

    return out;
}

int main()
{
    // Polling available stations
    std::cout << "Starting MVRXChange Service" << std::endl;
    size_t count = 0;
    service->QueryLocalServices(count);
    std::cout << "Found (" << count << ") XChange Stations" << std::endl;
    for(size_t i = 0; i < count; i++)
    {
        VectorworksMVR::IMVRxchangeService::ConnectToLocalServiceArgs args;
        service->GetLocalServiceAt(i, args);
        std::cout << args.Service << " | " << args.Provider << " -> " << args.StationName << std::endl;
    }

    GlobalData mainData;

    VectorworksMVR::IMVRxchangeService::ConnectToLocalServiceArgs args; // Initial Data
    std::string pa("Production Assist - ");
    std::string Provider = "Unittest";
    std::string StationName = "Linux2";
    std::string Service = "Test";

    // Be aware that this implementation uses a fixed sized buffer for strings of 1024 bytes, so the max strlen is 1023 bytes
    strcpy(args.Service, Service.c_str());
    strcpy(args.StationName, StationName.c_str());
    strcpy(args.Provider, Provider.c_str());

    args.VersionMajor = 5;
    args.VersionMinor = 1;
    {
        VectorworksMVR::VWFC::Tools::VWUUID stationUUID; // Using VW UUID implementation, but others can be used as well
        stationUUID.New();                               // Create new Station UUID, this UUID should be stable between restarts in production environments
        MvrUUID uuid;
        stationUUID.GetUUID(uuid.a, uuid.b, uuid.c, uuid.d);
        args.StationUUID = uuid;
    }
    args.InitialFiles = PseudoFiles(mainData);  // File list sent on initial JOIN command, done by the lib

    mainData.connArgs = args;

    VectorworksMVR::IMVRxchangeService::OnMessageArgs a;
    a.Callback = &onMsg;
    a.Context = &mainData; // This is obviously not copied, so make sure it stays in scope
    service->OnMessage(a);

    // Start service and sub-thread
    service->ConnectToLocalService(mainData.connArgs);


    /*

    // Request example
    // Be aware that this library is meant to be used with (asynchronous) user input, 
    // so a request should only be done when required by such

        VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage newMsg;
        newMsg.Type = MsgType::MVR_REQUEST;
        newMsg.REQUEST.FileUUID         = args.JOIN.Files[0].FileUUID;

        // By default, requests are sent to all stations and every station will answer either with the requested file or with an error
        // To filter, which stations should get the request "FromStationUUID" can be set in the REQUEST
        //newMsg.REQUEST.FromStationUUID  = {...};

        // this is thread safe
        service->Send_message(VectorworksMVR::IMVRxchangeService::SendMessageArgs{newMsg});

    */


    // MVR XChange is running in a new thread, so other stuff can be done here as well
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}