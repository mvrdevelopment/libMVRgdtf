//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_server.h"
#include "mvrxchange_session.h"

using namespace MVRxchangeNetwork;

MVRxchangeServer::MVRxchangeServer(boost::asio::io_context& io_context, const tcp::endpoint& endpoint) 
    : fAcceptor(io_context, endpoint)
{
    DoAccept();

    fPort = fAcceptor.local_endpoint().port();
}

void MVRxchangeServer::DoAccept()
{
    fAcceptor.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            // XXX whats the point of making a shared pointer that directly leaves scop. Then just intstiate an object.
            std::make_shared<MVRxchangeSession>(std::move(socket))->Start();
        }

        DoAccept();
    });

    
    
}


short MVRxchangeServer::GetPort() const
{
    return fPort;
}

void MVRxchangeServer::Deliver(const MVRxchangeNetwork::MVRxchangeMessage& msg)
{
    // XXX TODO
}