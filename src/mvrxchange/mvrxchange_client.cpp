//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_prefix.h"
#include "mvrxchange_client.h"
#include "Implementation/CMVRxchangeService.h"


using namespace MVRxchangeNetwork;

MVRxchangeClient::MVRxchangeClient(CMVRxchangeServiceImpl* impl, const MVRxchangePacket& packet) : fImpl(impl), fMsg_send(packet)
{

}

MVRxchangeClient::~MVRxchangeClient()
{

}

bool MVRxchangeClient::ReadMessage(std::chrono::steady_clock::duration timeout)
{
    boost::system::error_code error;
    std::size_t n = 0;
    boost::asio::async_read(fSocket,
    boost::asio::buffer(fMsg_ret.GetData(), MVRxchangePacket::total_header_length),
    [&](const boost::system::error_code& result_error,
        std::size_t result_n)
    {
        error = result_error;
        n = result_n;
    });

    // Run the operation until it completes, or until the timeout.
    Run(timeout);
    
    fMsg_ret.DecodeHeader();

    boost::asio::async_read(fSocket,
    boost::asio::buffer(fMsg_ret.GetBody(), fMsg_ret.GetBodyLength()),
    [&](const boost::system::error_code& result_error,
        std::size_t result_n)
    {
        error = result_error;
        n = result_n;
    });

    Run(timeout);

    if(! error)
    {
        IMVRxchangeService::IMVRxchangeMessage out;
        fMsg_ret.ToExternalMessage(out);
        fImpl->TCP_OnIncommingMessage(out);
        delete[] out.BufferToFile;
    }

    // Determine whether the read completed successfully
    return ! error;;
  }

bool MVRxchangeClient::WriteMessage(std::chrono::steady_clock::duration timeout)
  {

    // Start the asynchronous operation itself. The lambda that is used as a
    // callback will update the error variable when the operation completes.
    // The blocking_udp_client.cpp example shows how you can use std::bind
    // rather than a lambda.
    boost::system::error_code error;
    boost::asio::async_write(fSocket, 
    boost::asio::buffer(fMsg_send.GetData(), fMsg_send.GetLength()),
    [&](const boost::system::error_code& result_error,
        std::size_t /*result_n*/)
    {
        error = result_error;
    });

    // Run the operation until it completes, or until the timeout.
    Run(timeout);

    bool ok = false;
    if(!error)
    {   
        ok = ReadMessage(timeout);   
    }   

    // Determine whether the read completed successfully.
    return ok;
  }

void MVRxchangeClient::Run(std::chrono::steady_clock::duration timeout)
{
    // Restart the io_context, as it may have been left in the "stopped" state
    // by a previous operation.
    fio_context.restart();

    // Block until the asynchronous operation has completed, or timed out. If
    // the pending asynchronous operation is a composed operation, the deadline
    // applies to the entire operation, rather than individual operations on
    // the socket.
    fio_context.run_for(timeout);

    // If the asynchronous operation completed successfully then the io_context
    // would have been stopped due to Running out of work. If it was not
    // stopped, then the io_context::Run_for call must have timed out.
    if (!fio_context.stopped())
    {
        // Close the socket to cancel the outstanding asynchronous operation.
        fSocket.close();

        // Run the io_context again until the operation completes.
        fio_context.run();
    }
}

bool MVRxchangeClient::Connect(const std::string& host, const std::string& service, std::chrono::steady_clock::duration timeout)
{
    // Resolve the host name and service to a list of endpoints.
    auto endpoints = tcp::resolver(fio_context).resolve(host, service);

    // Start the asynchronous operation itself. The lambda that is used as a
    // callback will update the error variable when the operation completes.
    // The blocking_udp_client.cpp example shows how you can use std::bind
    // rather than a lambda.
    boost::system::error_code error;
    boost::asio::async_connect(fSocket, endpoints,
        [&](const boost::system::error_code& result_error,
            const tcp::endpoint& /*result_endpoint*/)
        {
            error = result_error;
        });


    // Run the operation until it completes, or until the timeout.
    Run(timeout);

    // Determine whether a connection was successfully established.
    std::string msg = error.message();
    std::string nam = error.category().name();

    std::cout << msg << nam << std::endl;

    return ! error;
}
