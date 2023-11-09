#include <iostream>
#include <thread>
#include "Include/VectorworksMVR.h"
#include <sys/stat.h>
#include "Prefix/StdAfx.h"

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

using MSG_TYPE = VectorworksMVR::IMVRxchangeService::MVR_COMMIT_MESSAGE;

#define EXAMPLE_FILE_PATH "./example_file.mvr"

struct GlobalData
{
    MvrUUID thisStationUUID;
};

std::vector<MSG_TYPE> PseudoFiles(GlobalData &data)
{

    VectorworksMVR::VWFC::Tools::VWUUID uuid;
    uuid.New();

    std::vector<MSG_TYPE> out;

    MSG_TYPE t;
    strcpy(t.Comment, "Example File 1");
    t.FileSize = 1024;
    t.StationUUID = data.thisStationUUID;
    t.FileUUID = VectorworksMVR::MvrUUID(1, 2, 3, 4); // Should be based on file in production environment
    t.VersionMajor = 5;                               // MVR Version
    t.VersionMinor = 1;                               // MVR Version

    out.push_back(t);

    return out;
}

VectorworksMVR::IMVRxchangeServicePtr service(VectorworksMVR::IID_IMVRxchangeService);

using MsgType = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType;
VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage onMsg(const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage &args, void *context)
{
    GlobalData &data = *((GlobalData *)context);

    VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage out;

    switch (args.Type)
    {
        case MsgType::MVR_UNDEFINED:        std::cout << "New Message: " << "MVR_UNDEFINED"         << std::endl;
        case MsgType::MVR_JOIN:             std::cout << "New Message: " << "MVR_JOIN"              << std::endl;
        case MsgType::MVR_LEAVE:            std::cout << "New Message: " << "MVR_LEAVE"             << std::endl;
        case MsgType::MVR_COMMIT:           std::cout << "New Message: " << "MVR_COMMIT"            << std::endl;
        case MsgType::MVR_REQUEST:          std::cout << "New Message: " << "MVR_REQUEST"           << std::endl;
        case MsgType::MVR_JOIN_RET:         std::cout << "New Message: " << "MVR_JOIN_RET"          << std::endl;
        case MsgType::MVR_LEAVE_RET:        std::cout << "New Message: " << "MVR_LEAVE_RET"         << std::endl;
        case MsgType::MVR_COMMIT_RET:       std::cout << "New Message: " << "MVR_COMMIT_RET"        << std::endl;
        case MsgType::MVR_REQUEST_RET:      std::cout << "New Message: " << "MVR_REQUEST_RET"       << std::endl;
        case MsgType::MVR_NEW_SESSION_HOST: std::cout << "New Message: " << "MVR_NEW_SESSION_HOST"  << std::endl;
    }

    // On join
    if (args.Type == MsgType::MVR_JOIN)
    {
        out.Type = MsgType::MVR_JOIN_RET;
        out.JOIN.Files = PseudoFiles(data); // Return available Files to new Client

        std::cout << "New Client: " << args.JOIN.Provider << " -> " << args.JOIN.StationName << std::endl;
    }
    else if (args.Type == MsgType::MVR_JOIN_RET)
    {
        std::cout << "Available Files on station " << args.JOIN.Provider << " -> " << args.JOIN.StationName << ":" << std::endl;
        for (auto &it : args.JOIN.Files)
        {
            VectorworksMVR::VWFC::Tools::VWUUID uuid(it.FileUUID.a, it.FileUUID.b, it.FileUUID.c, it.FileUUID.d);
            std::cout << uuid.ToString(true).GetStdString() << "  " << it.Comment << std::endl;
        }
        // Ret types are not handled in any other way, so no need to set any properties of "out" object;
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
            strcpy(out.PathToFile, "/home/marka/Dokumente/DEV/libMVRgdtf/gdtf_share_test/Bigger Test.mvr");
            out.REQUEST.FileUUID = VectorworksMVR::MvrUUID(5, 6, 7, 8);
            out.RetIsOK = true;
            std::cout << "Returned requested file" << std::endl;
        }
        else
        {
            out.RetIsOK = false;
            strcpy(out.RetError, "Unable to find requested file");
            std::cout << "Unable to find requested file" << std::endl;
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
    {
        VectorworksMVR::VWFC::Tools::VWUUID stationUUID; // Using VW UUID implementation, but others can be used as well
        stationUUID.New();                               // Create new Station UUID, this UUID should be stable between restarts in production environments
        MvrUUID uuid;
        stationUUID.GetUUID(uuid.a, uuid.b, uuid.c, uuid.d);
        mainData.thisStationUUID = uuid;
    }

    VectorworksMVR::IMVRxchangeService::OnMessageArgs a;
    a.Callback = &onMsg;
    a.Context = &mainData; // This is obviously not copied, so make sure it stays in scope
    service->OnMessage(a);

    VectorworksMVR::IMVRxchangeService::ConnectToLocalServiceArgs args; // Initial Data
    std::string pa("Production Assist - ");
    std::string Provider = "Unittest";
    std::string StationName = "Linux2";
    std::string Service = "Test";

    strcpy(args.Service, Service.c_str());
    strcpy(args.StationName, StationName.c_str());
    strcpy(args.Provider, Provider.c_str());

    args.VersionMajor = 5;
    args.VersionMinor = 1;
    args.StationUUID = mainData.thisStationUUID;
    args.InitialFiles = PseudoFiles(mainData);

    // Start service and sub-thread
    service->ConnectToLocalService(args);

    // MVR XChange is running in a new thread, so other stuff can be done here as well
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}