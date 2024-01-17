//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_server.h"
#include "mvrxchange_session.h"

using namespace MVRxchangeNetwork;

MVRxchangeServer::MVRxchangeServer(CMVRxchangeServiceImpl* impl) : 
    fImpl(impl), 
    fEndpoint(tcp::v4(), 0), 
    fContext(), 
    fAcceptor(fContext, fEndpoint)
{
    std::cout << "Port: " << fAcceptor.local_endpoint().port() << std::endl;

    fPort = fAcceptor.local_endpoint().port();
    fIp   = fAcceptor.local_endpoint().address().to_v4().to_ulong();

    DoAccept();
    fExecutionThread = std::thread(&MVRxchangeServer::ExecutionFunction, this);
}

MVRxchangeServer::~MVRxchangeServer()
{
    fContext.stop();
    if(fExecutionThread.joinable())
    {
        fExecutionThread.join();
    }
}

void MVRxchangeServer::DoAccept()
{
    fAcceptor.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec)
        {
            MVRXCHANGE_DEBUG("incoming message from: " << socket.remote_endpoint().address().to_string() << ":" << std::to_string(socket.remote_endpoint().port()));
            auto session = std::make_shared<MVRxchangeSession>(std::move(socket), fImpl, this);

            AddSession(session);

            session->Start();
        }else{
            MVRXCHANGE_ERROR(ec.message());
        }

        DoAccept();
    });
}

void MVRxchangeServer::ExecutionFunction()
{
    fContext.run();
}

void MVRxchangeServer::AddSession(const std::shared_ptr<MVRxchangeSession>& p) 
{
    std::unique_lock<std::mutex> mSession;
    fSession.insert(p);
}

void MVRxchangeServer::CloseSession(const std::shared_ptr<MVRxchangeSession>& p) 
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