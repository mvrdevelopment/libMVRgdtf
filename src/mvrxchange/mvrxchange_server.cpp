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
    fIp   = fAcceptor.local_endpoint().address().to_v4().to_uint();

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

    // No handler runs anymore, so sockets can be closed safely before the io_context is destroyed.
    // Otherwise the sessions kept alive by pending handlers would be destroyed inside the
    // io_context shutdown, which can block forever.
    boost::system::error_code ec;
    fAcceptor.close(ec);
    this->CloseAllSessions();
}

void MVRxchangeServer::CloseAllSessions()
{
    std::set<std::shared_ptr<MVRxchangeSession>> sessions;
    {
        std::unique_lock<std::mutex> lock(mSession);
        sessions.swap(fSession);
    }

    for(const auto& session : sessions)
    {
        session->Close();
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
    std::unique_lock<std::mutex> lock(mSession);
    fSession.insert(p);
}

void MVRxchangeServer::CloseSession(const std::shared_ptr<MVRxchangeSession>& p) 
{
    std::unique_lock<std::mutex> lock(mSession);
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