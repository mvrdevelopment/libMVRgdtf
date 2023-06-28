//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once

#include "../Prefix/StdAfx.h"
#include <boost/asio.hpp>
#include <deque>

namespace VectorworksMVR
{
    class CMVRxchangeServiceImpl;
}

using namespace boost::asio;
using ip::tcp;


constexpr uint32_t kMVR_Package_Flag =  778682;
constexpr uint32_t kMVR_Package_JSON_TYPE   =  0;
constexpr uint32_t kMVR_Package_BUFFER_TYPE =  1;
