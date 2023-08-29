//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_prefix.h"
#include "mvrxchange_session.h"
#include "Implementation/CMVRxchangeService.h"


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

    boost::asio::async_read(fSocket, boost::asio::buffer(freadmsg.GetData(), MVRxchangePacket::total_header_length),
    [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec && freadmsg.DecodeHeader())
        {
            boost::asio::async_read(fSocket, boost::asio::buffer(freadmsg.GetBody(), freadmsg.GetBodyLength()),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    IMVRxchangeService::IMVRxchangeMessage out;
                    freadmsg.ToExternalMessage(out);

                    IMVRxchangeService::IMVRxchangeMessage in = fImpl->TCP_OnIncommingMessage(out);
                    delete out.BufferToFile;
                    
                    MVRxchangePacket in_msg;
                    in_msg.FromExternalMessage(in);
                    Deliver(in_msg);
                }
                else
                {
                    std::string msg = ec.message();
                    std::string nam = ec.category().name();

                    std::cout << "!!" << msg << nam << std::endl;
                    fServer->CloseSession(self);
                }
            });
        }
        else
        {
            std::string msg = ec.message();
            std::string nam = ec.category().name();

            std::cout << "!!!" << msg << nam << std::endl;
            fServer->CloseSession(self);
        }
    });
}


void MVRxchangeSession::Deliver(const MVRxchangePacket& msg)
{
    bool write_in_progress;
    {
        std::lock_guard<std::mutex> l(fwrite_msgs_mutex);
        write_in_progress = !fwrite_msgs.empty();
        fwrite_msgs.push_back(msg);
    }
    if (!write_in_progress)
    {
        DoWrite();
    }
}

void MVRxchangeSession::DoWrite()
{
    auto self(shared_from_this());

    std::lock_guard<std::mutex> l(fwrite_msgs_mutex);
    if(!fwrite_msgs.size()){
        return;
    }

    MVRxchangePacket msg = std::move(fwrite_msgs.front());
    fwrite_msgs.pop_front();

    boost::asio::async_write(fSocket, boost::asio::buffer(msg.GetData(), msg.GetLength()),
    [this, self](boost::system::error_code ec, std::size_t /*length*/)
    {
        if (!ec)
        {
            DoWrite();
        }
        else
        {
            std::string msg = ec.message();
            std::string nam = ec.category().name();

            std::cout << "!!!!" << msg << nam << std::endl;
            fServer->CloseSession(self);
        }
    });
}
