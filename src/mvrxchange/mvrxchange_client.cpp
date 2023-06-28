//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_prefix.h"
#include "mvrxchange_client.h"
#include "Implementation/CMVRxchangeService.h"


using namespace MVRxchangeNetwork;

MVRxchangeClient::MVRxchangeClient(boost::asio::io_context& io_context, const tcp::resolver::results_type& endpoints, CMVRxchangeServiceImpl* impl)
    : fIo_context(io_context),
      fSocket(io_context),
      fImpl(impl)
{
    DoConnect(endpoints);
}

void MVRxchangeClient::Deliver(const MVRxchangePacket& msg)
{
    boost::asio::post(fIo_context, [this, msg]()
    {
        bool write_in_progress = !fWrite_msgs.empty();
        fWrite_msgs.push_back(msg);
        if (!write_in_progress)
        {
            DoWrite();
        }
    });
}

void MVRxchangeClient::Close()
{
    boost::asio::post(fIo_context, [this]()
                      {
        fSocket.close();
        
    });
}

void MVRxchangeClient::DoConnect(const tcp::resolver::results_type& endpoints)
{
    boost::asio::async_connect(fSocket, endpoints,
    [this](boost::system::error_code ec, tcp::endpoint)
    {
        if (!ec)
        {
            DoReadHeader();
        }
    });
}

void MVRxchangeClient::DoReadHeader()
{
    boost::asio::async_read(fSocket,
    boost::asio::buffer(fRead_msg.GetData(), MVRxchangePacket::total_header_length),
    [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            if(fRead_msg.DecodeHeader())
            {
                DoReadBody();
                
                IMVRxchangeService::IMVRxchangeMessage out;
                fRead_msg.ToExternalMessage(out);

                IMVRxchangeService::IMVRxchangeMessage in = fImpl->TCP_OnIncommingMessage(out);

                MVRxchangePacket in_msg;
                in_msg.FromExternalMessage(in);
                Deliver(in_msg);

            }
        }
        else
        {
            fSocket.close();
        }
    });
}

void MVRxchangeClient::DoReadBody()
{
    boost::asio::async_read(fSocket,
    boost::asio::buffer(fRead_msg.GetBody(), fRead_msg.GetBodyLength()),
    [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {   
            // TODO
            DoReadHeader();
        }
        else
        {
            fSocket.close();
        }
    });
}

void MVRxchangeClient::DoWrite()
{
    boost::asio::async_write(fSocket,
    boost::asio::buffer(fWrite_msgs.front().GetData(), fWrite_msgs.front().GetLength()),
    [this](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            fWrite_msgs.pop_front();
            if (!fWrite_msgs.empty())
            {
                DoWrite();
            }
        }
        else
        {
            fSocket.close();
        }
    });
}
