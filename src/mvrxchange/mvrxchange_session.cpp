//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_prefix.h"
#include "mvrxchange_session.h"

using namespace MVRxchangeNetwork;

MVRxchangeSession::MVRxchangeSession(tcp::socket socket)
    : fSocket(std::move(socket))
{
    
}

void MVRxchangeSession::Start()
{
    DoReadHeader();
}

void MVRxchangeSession::Deliver(const MVRxchangeMessage& msg)
{
    bool write_in_progress = !fwrite_msgs.empty();
    fwrite_msgs.push_back(msg);
    if (!write_in_progress)
    {
        DoWrite();
    }
}

void MVRxchangeSession::DoReadHeader()
{
    auto self(shared_from_this());
    boost::asio::async_read(fSocket,boost::asio::buffer(freadmsg.GetData(), MVRxchangeMessage::total_header_length),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec && freadmsg.DecodeHeader())
        {
            DoReadBody();
        }
        else
        {
            // Leave TODO
        }
    });
}

void MVRxchangeSession::DoReadBody()
{
    auto self(shared_from_this());
    boost::asio::async_read(fSocket, boost::asio::buffer(freadmsg.GetBody(), freadmsg.GetBodyLength()),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            DoReadHeader();
        }
        else
        {
            // LEAVE TODO
        }
    });
}

void MVRxchangeSession::DoWrite()
{
    auto self(shared_from_this());

    MVRxchangeMessage& msg = fwrite_msgs.front();


    boost::asio::async_write(fSocket, boost::asio::buffer(msg.GetData(), msg.GetLength()),
    [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            fwrite_msgs.pop_front();
            if ( ! fwrite_msgs.empty())
            {
                DoWrite();
            }
        }
        else
        {
            // TODO Leave
        }
    });
}
