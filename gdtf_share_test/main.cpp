#include <iostream>
#include <thread>
#include "Include/VectorworksMVR.h"

int main()
{
    VectorworksMVR::IMVRxchangeServicePtr service(VectorworksMVR::IID_IMVRxchangeService);
    VectorworksMVR::IMVRxchangeService::OnMessageArgs onMessage;

    service->OnMessage(onMessage);

    VectorworksMVR::IMVRxchangeService::ConnectToLocalServiceArgs args;

    std::string pa ("Production Assist - "); 
    std::string Provider       = "Unittest";
    std::string StationName    = "Linux";
    std::string Service        = "Unittest_1";
    VectorworksMVR::MvrUUID uuid(1,2,3,4);

    strcpy(args.Service, Service.c_str());
    strcpy(args.StationName, StationName.c_str());
    strcpy(args.Provider, Provider.c_str());

    args.VersionMajor = 1;
    args.VersionMinor = 1;
    args.StationUUID = uuid;

    service->ConnectToLocalService(args); 
    VectorworksMVR::IMVRxchangeService::OnMessageArgs a{
        [](const VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage& args, void* context){
            VectorworksMVR::IMVRxchangeService::IMVRxchangeMessage out;
            return out;
        },
        nullptr
    };

    service->OnMessage(a);

    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}