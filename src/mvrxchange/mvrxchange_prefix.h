//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once

#include "../Prefix/StdAfx.h"
#include <boost/asio.hpp>
#include <deque>
#include <set>

namespace VectorworksMVR
{
    class CMVRxchangeServiceImpl;
}

using namespace VectorworksMVR;

using namespace boost::asio;
using ip::tcp;


constexpr uint32_t kMVR_Package_Flag =  778682;
constexpr uint32_t kMVR_Package_JSON_TYPE   =  0;
constexpr uint32_t kMVR_Package_BUFFER_TYPE =  1;

#define MVRXChange_Service "_mvrxchange._tcp.local."