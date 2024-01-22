//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_prefix.h"
#include "mvrxchange_session.h"
#include "CMVRxchangeService.h"


using namespace MVRxchangeNetwork;

MVRxchangeSession::MVRxchangeSession(tcp::socket socket, CMVRxchangeServiceImpl* impl, MVRxchangeServer* s)
    : fSocket(std::move(socket)),
      fImpl(impl),
      fServer(s)
{
    
}

void MVRxchangeSession::Start()
{
    DoRead();
}

void MVRxchangeSession::DoRead()
{
    auto self(shared_from_this());

    boost::asio::async_read(fSocket, boost::asio::buffer(fReadMsg.GetData(), MVRxchangePacket::total_header_length),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec && fReadMsg.DecodeHeader())
        {
            boost::asio::async_read(fSocket, boost::asio::buffer(fReadMsg.GetBody(), fReadMsg.GetBodyLength()),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    IMVRxchangeService::IMVRxchangeMessage out;
                    fReadMsg.ToExternalMessage(out);

                    TCPMessageInfo info {
                        this->fSocket.remote_endpoint().port(),
                        this->fSocket.remote_endpoint().address().to_string()
                    };
                    IMVRxchangeService::IMVRxchangeMessage in = fImpl->TCP_OnIncommingMessage(out, info);
                    delete[] out.BufferToFile;
                    
                    MVRxchangePacket in_msg;
                    in_msg.FromExternalMessage(in);
                    Deliver(in_msg);
                }
                else
                {
                    fServer->CloseSession(self);
                }
            });
        }
        else
        {
            fServer->CloseSession(self);
        }
    });
}


void MVRxchangeSession::Deliver(const MVRxchangePacket& msg)
{
    auto self(shared_from_this());

    // msg is passed, so the lifetime of the underlying buffer ist extended apropriately;
    boost::asio::async_write(fSocket, boost::asio::buffer(msg.GetData(), msg.GetLength()),
    [this, self, msg](boost::system::error_code ec, std::size_t /*length*/)
    {
        // Reply sent, close connection
        fServer->CloseSession(self);

        // buffer is now deleted
    });
}

