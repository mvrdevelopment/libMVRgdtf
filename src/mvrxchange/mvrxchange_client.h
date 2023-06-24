//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#pragma once
#include "mvrxchange_prefix.h"

namespace MVRxchangeNetwork
{
    class MVRxchangeClient
    {
    public:
    MVRxchangeClient(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints);

    virtual void Deliver(const MVRxchangeMessage& msg);
    void         Close();

    private:
    void DoConnect(const tcp::resolver::results_type& endpoints);
    void DoReadHeader();
    void DoReadBody();
    void DoWrite();

    private:
    boost::asio::io_context&  fIo_context;
    tcp::socket               fSocket;
    MVRxchangeMessage         fRead_msg;
    MVRxchangeMessageDeque    fWrite_msgs;
    };
}