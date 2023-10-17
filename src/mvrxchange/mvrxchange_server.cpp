//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_server.h"
#include "mvrxchange_session.h"

using namespace MVRxchangeNetwork;

MVRxchangeServer::MVRxchangeServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint, CMVRxchangeServiceImpl* impl) 
    : fAcceptor(io_context, endpoint),
      fImpl(impl)
{
    DoAccept();

    std::cout << "Port: " << fAcceptor.local_endpoint().port() << std::endl;

    fPort = fAcceptor.local_endpoint().port();
    fIp   = fAcceptor.local_endpoint().address().to_v4().to_ulong();
}

void MVRxchangeServer::DoAccept()
{
    fAcceptor.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            std::cout << "Start Session" << std::endl;
            // XXX whats the point of making a shared pointer that directly leaves scop. Then just intstiate an object.
            auto session = std::make_shared<MVRxchangeSession>(std::move(socket), fImpl, this);

            AddSession(session);

            session->Start();
        }

        DoAccept();
    });

}


void MVRxchangeServer::AddSession(std::shared_ptr<MVRxchangeSession> p) 
{
    std::unique_lock<std::mutex> mSession;
    fSession.insert(p);
}

void MVRxchangeServer::CloseSession(std::shared_ptr<MVRxchangeSession> p) 
{
    std::unique_lock<std::mutex> mSession;
    fSession.erase(p);
}

uint16_t MVRxchangeServer::GetPort() const
{
    return fPort;
}

uint32_t MVRxchangeServer::GetIP() const
{
    return fIp;
}