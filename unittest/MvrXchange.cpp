//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "MvrXchange.h"
#include "Utility.h"
#include "Include/VectorworksMVR.h"
#include "mvrxchange/mvrxchange_message.h"
#include <vector>
#include <array>
#include <cstring>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>

#include <iostream>

using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;

#define __checkifTrue(x) checkifTrue(#x, x)

MvrXChangeUnitTest::MvrXChangeUnitTest(const std::string& currentDir)
{
}

MvrXChangeUnitTest::~MvrXChangeUnitTest()
{
}

bool MvrXChangeUnitTest::ExecuteTest()
{
	std::cout << "=                                        MvrXchange                                       =" << std::endl;

    {

        // MVR_JOIN and MVR_COMMIT Test

        IMVRxchangeService::IMVRxchangeMessage join_in_msg;
        IMVRxchangeService::IMVRxchangeMessage join_out_msg;

        join_in_msg.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_JOIN;
        join_in_msg.JOIN.Provider = "Test Provider";
        join_in_msg.JOIN.StationName = "Test Station";
        join_in_msg.JOIN.StationUUID = VectorworksMVR::MvrUUID(1, 2, 3, 4);
        join_in_msg.JOIN.VersionMajor = 5;
        join_in_msg.JOIN.VersionMinor = 6;

        IMVRxchangeService::MVR_COMMIT_MESSAGE commit;
        commit.Comment = "TestCommit";
        commit.VersionMajor = 3;
        commit.VersionMinor = 2;
        commit.FileSize = 12312313556;
        commit.FileUUID = VectorworksMVR::MvrUUID(5, 6, 7, 8);
        commit.StationUUID = VectorworksMVR::MvrUUID(1, 2, 3, 4);
        commit.ForStationsUUID = {
            VectorworksMVR::MvrUUID(9, 9, 10, 1),
            VectorworksMVR::MvrUUID(5, 1, 4, 6)
        };

        IMVRxchangeService::MVR_COMMIT_MESSAGE commit2;
        commit2.Comment = "TestCommit";
        commit2.VersionMajor = 3;
        commit2.VersionMinor = 2;
        commit2.FileSize = 234234;
        commit2.FileUUID = VectorworksMVR::MvrUUID(1, 1, 1, 1);
        commit2.StationUUID = VectorworksMVR::MvrUUID(2, 2, 2, 2);
        commit2.ForStationsUUID = {};

        join_in_msg.JOIN.Commits = {commit, commit2};

        // ----------------------------

        {
            MVRxchangeNetwork::MVRxchangePacket outMsg;
            outMsg.FromExternalMessage(join_in_msg);

            std::vector<char> testBuffer;
            testBuffer.resize(outMsg.GetLength());
            std::memcpy(testBuffer.data(), outMsg.GetData(), outMsg.GetLength());

            MVRxchangeNetwork::MVRxchangePacket inMsg;
            std::memcpy(inMsg.GetData(), testBuffer.data(), testBuffer.size());
            inMsg.DecodeHeader();
            inMsg.ToExternalMessage(join_out_msg);
        }

        // ----------------------------

        

        __checkifTrue(join_in_msg.Type              ==  join_out_msg.Type              );
        __checkifTrue(join_in_msg.JOIN.Provider     ==  join_out_msg.JOIN.Provider     );
        __checkifTrue(join_in_msg.JOIN.StationName  ==  join_out_msg.JOIN.StationName  );
        __checkifTrue(join_in_msg.JOIN.StationUUID  ==  join_out_msg.JOIN.StationUUID  );
        __checkifTrue(join_in_msg.JOIN.VersionMajor ==  join_out_msg.JOIN.VersionMajor );
        __checkifTrue(join_in_msg.JOIN.VersionMinor ==  join_out_msg.JOIN.VersionMinor );

        bool eq = join_in_msg.JOIN.Commits.size() == join_out_msg.JOIN.Commits.size();
        checkifTrue("join_in_msg.JOIN.Commits.size() == join_out_msg.JOIN.Commits.size()", eq);
        if(eq)
        {
            for(size_t i = 0; i < join_in_msg.JOIN.Commits.size(); ++i)
            {
                auto& in = join_in_msg.JOIN.Commits[i];
                auto& ou = join_out_msg.JOIN.Commits[i];

                __checkifTrue(in.Comment         == ou.Comment        );
                __checkifTrue(in.VersionMajor    == ou.VersionMajor   );
                __checkifTrue(in.VersionMinor    == ou.VersionMinor   );
                __checkifTrue(in.FileSize        == ou.FileSize       );
                __checkifTrue(in.FileUUID        == ou.FileUUID       );
                __checkifTrue(in.StationUUID     == ou.StationUUID    );
                __checkifTrue(in.ForStationsUUID == ou.ForStationsUUID);
            }
        }

        const char* t="{\"Commits\":[{\"Comment\":\"TestCommit\",\"FileSize\":12312313556,\"FileUUID\":\"05000000-0600-0000-0700-000008000000\",\"ForStationsUUID\":[\"09000000-0900-0000-0A00-000001000000\",\"05000000-0100-0000-0400-000006000000\"],\"StationUUID\":\"01000000-0200-0000-0300-000004000000\",\"Type\":\"MVR_COMMIT\",\"verMajor\":3,\"verMinor\":2},{\"Comment\":\"TestCommit\",\"FileSize\":234234,\"FileUUID\":\"01000000-0100-0000-0100-000001000000\",\"ForStationsUUID\":[],\"StationUUID\":\"02000000-0200-0000-0200-000002000000\",\"Type\":\"MVR_COMMIT\",\"verMajor\":3,\"verMinor\":2}],\"Provider\":\"Test Provider\",\"StationName\":\"Test Station\",\"StationUUID\":\"01000000-0200-0000-0300-000004000000\",\"Type\":\"MVR_JOIN\",\"verMajor\":5,\"verMinor\":\"6\"}";
        
        {
            join_out_msg = IMVRxchangeService::IMVRxchangeMessage();
            MVRxchangeNetwork::MVRxchangePacket inMsg;
            inMsg.FromString(t);
            inMsg.ToExternalMessage(join_out_msg);
        }

        __checkifTrue(join_in_msg.Type              ==  join_out_msg.Type              );
        __checkifTrue(join_in_msg.JOIN.Provider     ==  join_out_msg.JOIN.Provider     );
        __checkifTrue(join_in_msg.JOIN.StationName  ==  join_out_msg.JOIN.StationName  );
        __checkifTrue(join_in_msg.JOIN.StationUUID  ==  join_out_msg.JOIN.StationUUID  );
        __checkifTrue(join_in_msg.JOIN.VersionMajor ==  join_out_msg.JOIN.VersionMajor );
        __checkifTrue(join_in_msg.JOIN.VersionMinor ==  join_out_msg.JOIN.VersionMinor );

        eq = join_in_msg.JOIN.Commits.size() == join_out_msg.JOIN.Commits.size();
        checkifTrue("join_in_msg.JOIN.Commits.size() == join_out_msg.JOIN.Commits.size()", eq);
        if(eq)
        {
            for(size_t i = 0; i < join_in_msg.JOIN.Commits.size(); ++i)
            {
                auto& in = join_in_msg.JOIN.Commits[i];
                auto& ou = join_out_msg.JOIN.Commits[i];

                __checkifTrue(in.Comment         == ou.Comment        );
                __checkifTrue(in.VersionMajor    == ou.VersionMajor   );
                __checkifTrue(in.VersionMinor    == ou.VersionMinor   );
                __checkifTrue(in.FileSize        == ou.FileSize       );
                __checkifTrue(in.FileUUID        == ou.FileUUID       );
                __checkifTrue(in.StationUUID     == ou.StationUUID    );
                __checkifTrue(in.ForStationsUUID == ou.ForStationsUUID);
            }
        }

    }

    {

        // MVR_REQUEST Test

        IMVRxchangeService::IMVRxchangeMessage request_in_msg;
        IMVRxchangeService::IMVRxchangeMessage request_out_msg;

        request_in_msg.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_REQUEST;
        request_in_msg.REQUEST.FileUUID = VectorworksMVR::MvrUUID(1, 2, 3, 4);
        request_in_msg.REQUEST.FromStationUUID = {
            VectorworksMVR::MvrUUID(4, 4, 4, 4),
            VectorworksMVR::MvrUUID(5, 5, 5, 5),
            VectorworksMVR::MvrUUID(6, 6, 6, 6)
        };

        // ----------------------------

        {
            MVRxchangeNetwork::MVRxchangePacket outMsg;
            outMsg.FromExternalMessage(request_in_msg);

            std::vector<char> testBuffer;
            testBuffer.resize(outMsg.GetLength());
            std::memcpy(testBuffer.data(), outMsg.GetData(), outMsg.GetLength());

            MVRxchangeNetwork::MVRxchangePacket inMsg;
            std::memcpy(inMsg.GetData(), testBuffer.data(), testBuffer.size());
            inMsg.DecodeHeader();
            inMsg.ToExternalMessage(request_out_msg);
        }

        __checkifTrue(request_in_msg.REQUEST.FileUUID        == request_out_msg.REQUEST.FileUUID        );
        __checkifTrue(request_in_msg.REQUEST.FromStationUUID == request_out_msg.REQUEST.FromStationUUID );

    }

    constexpr size_t hLength = MVRxchangeNetwork::MVRxchangePacket::total_header_length;
    std::array<char, hLength> headerTest; // for later use
    {
        // MVR_LEAVE Test;

        IMVRxchangeService::IMVRxchangeMessage leave_in_msg;
        IMVRxchangeService::IMVRxchangeMessage leave_out_msg;


        leave_in_msg.Type = VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_LEAVE;
        leave_in_msg.LEAVE.FromStationUUID = VectorworksMVR::MvrUUID(12, 12, 12, 12);

        // ----------------------------

        {
            MVRxchangeNetwork::MVRxchangePacket outMsg;
            outMsg.FromExternalMessage(leave_in_msg);

            std::vector<char> testBuffer;
            testBuffer.resize(outMsg.GetLength());
            std::memcpy(testBuffer.data(), outMsg.GetData(), outMsg.GetLength());
            std::memcpy(headerTest.data(), outMsg.GetData(), hLength);

            MVRxchangeNetwork::MVRxchangePacket inMsg;
            std::memcpy(inMsg.GetData(), testBuffer.data(), testBuffer.size());
            inMsg.DecodeHeader();
            inMsg.ToExternalMessage(leave_out_msg);
        }

        __checkifTrue(leave_in_msg.LEAVE.FromStationUUID == leave_out_msg.LEAVE.FromStationUUID);
    }


    {
        // Deserialization Test; -> SHOULD FAIL
        MVRxchangeNetwork::MVRxchangePacket outMsg;
        IMVRxchangeService::IMVRxchangeMessage out_msg;

        std::vector<char> testBuffer;
        testBuffer.resize(1000);
        std::memset(testBuffer.data(), 0, testBuffer.size());

        MVRxchangeNetwork::MVRxchangePacket inMsg;
        std::memcpy(inMsg.GetData(), testBuffer.data(), testBuffer.size());
        inMsg.DecodeHeader();
        inMsg.ToExternalMessage(out_msg);

        __checkifTrue(out_msg.Type == VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_UNDEFINED);
        __checkifTrue(!out_msg.RetIsOK);
    }

    {
        // Deserialization Test; -> SHOULD FAIL
        MVRxchangeNetwork::MVRxchangePacket outMsg;
        IMVRxchangeService::IMVRxchangeMessage out_msg;

        std::vector<char> testBuffer;
        testBuffer.resize(1000);
        std::memset(testBuffer.data(), 0, testBuffer.size());
        std::memcpy(testBuffer.data(), headerTest.data(), hLength);

        {
            // fill data-part (json) with random data
            std::independent_bits_engine<std::default_random_engine, CHAR_BIT, unsigned long> rbe;
            std::generate(testBuffer.begin() + hLength, testBuffer.end(), std::ref(rbe));
        }

        MVRxchangeNetwork::MVRxchangePacket inMsg;
        std::memcpy(inMsg.GetData(), testBuffer.data(), testBuffer.size());
        inMsg.DecodeHeader();
        inMsg.ToExternalMessage(out_msg);

        __checkifTrue(out_msg.Type == VectorworksMVR::IMVRxchangeService::MVRxchangeMessageType::MVR_UNDEFINED);
        __checkifTrue(!out_msg.RetIsOK);
    }

    {
        const char* t = "{\"Type\":\"MVR_LEAVE_RET\",\"OK\":\"true\",\"Message\":\"TestMessage\"}";

        IMVRxchangeService::IMVRxchangeMessage out_msg;
        MVRxchangeNetwork::MVRxchangePacket inMsg;
        inMsg.FromString(t);
        inMsg.ToExternalMessage(out_msg);

        __checkifTrue(out_msg.RetIsOK);
    }

    {
        const char* t ="{\"Type\":\"MVR_LEAVE_RET\",\"OK\": true,\"Message\":\"TestMessage\"}";

        IMVRxchangeService::IMVRxchangeMessage out_msg;
        MVRxchangeNetwork::MVRxchangePacket inMsg;
        inMsg.FromString(t);
        inMsg.ToExternalMessage(out_msg);

        __checkifTrue(out_msg.RetIsOK);
    }

    return true;
}
