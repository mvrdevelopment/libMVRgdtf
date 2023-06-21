//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------
#pragma once
#include "../Prefix/StdAfx.h"
#include <boost/asio.hpp>
#include <deque>

using boost::asio::ip::tcp;


constexpr uint32_t kMVR_Package_Flag =  778682;

#include "mvrxchange_dynamic_buffer.h"
#include "mvrxchange_message.h"
#include "mvrxchange_client.h"
#include "mvrxchange_server.h"
#include "mvrxchange_session.h"
