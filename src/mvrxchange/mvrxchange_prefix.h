//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once

#include "../Prefix/StdAfx.h"
#include <boost/asio.hpp>
#include <deque>
#include <set>
#include <iostream>

#ifndef MVRXCHANGE_LOG
    #define MVRXCHANGE_LOG(x) std::cout << "[MvrXChange] [LOG] " << x << std::endl
#endif

#ifndef MVRXCHANGE_ERROR
    #define MVRXCHANGE_ERROR(x) std::cerr << "[MvrXChange] [ERR] " << x << std::endl
#endif

#ifndef MVRXCHANGE_DEBUG
    #ifndef NDEBUG
        #define MVRXCHANGE_DEBUG(x) std::cout << "[MvrXChange] [DBG] " << x << std::endl
    #else
        #define MVRXCHANGE_DEBUG(x)
    #endif
#endif

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