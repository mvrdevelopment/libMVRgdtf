//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------


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
            std::make_shared<LRNetSession>(std::move(socket))->Start();
        }

        DoAccept();
    });

    
    
}

short MVRxchangeServer::GetPort() const
{
    return fPort;
}

void MVRxchangeServer::Deliver(const LRNetMessage& msg)
{
    // TODO
}