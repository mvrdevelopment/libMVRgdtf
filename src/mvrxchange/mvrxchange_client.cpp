//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------

#include "mvrxchange_client.h"
#include "CMVRxchangeService.h"

using namespace MVRxchangeNetwork;

MVRxchangeClient::MVRxchangeClient(const MVRxchangePacket& packet) : fMsg_send(packet)
{

}

MVRxchangeClient::~MVRxchangeClient()
{

}

MVRxchangeClient::SendResult MVRxchangeClient::SendMessage(std::chrono::steady_clock::duration timeout)
{
    MVRxchangeClient::SendResult result;

    if(WriteMessage(result, timeout))
    {
        ReadMessage(result, timeout);
    }
    
    return result;
}

bool MVRxchangeClient::ReadMessage(SendResult& res, std::chrono::steady_clock::duration timeout)
{
    boost::asio::async_read(fSocket,
    boost::asio::buffer(res.message.GetData(), MVRxchangePacket::total_header_length),
    [&](const boost::system::error_code& result_error,
        std::size_t result_n)
    {
        res.error = result_error;
    });

    // Run the operation until it completes, or until the timeout.
    Run(timeout);

    res.success = !res.error.failed();
    
    if(res.success)
    {
        res.message.DecodeHeader();

        boost::asio::async_read(fSocket,
        boost::asio::buffer(res.message.GetBody(), res.message.GetBodyLength()),
        [&](const boost::system::error_code& result_error,
            std::size_t result_n)
        {
            res.error = result_error;
        });
        Run(timeout);
        res.success = !res.error.failed();
    }

    if(res.success)
    {
        res.messageInfo = TCPMessageInfo {
            this->fSocket.remote_endpoint().port(),
            this->fSocket.remote_endpoint().address().to_string()
        };
    }

    return res.success;
  }

bool MVRxchangeClient::WriteMessage(SendResult& res, std::chrono::steady_clock::duration timeout)
  {

    // Start the asynchronous operation itself. The lambda that is used as a
    // callback will update the error variable when the operation completes.
    // The blocking_udp_client.cpp example shows how you can use std::bind
    // rather than a lambda.
    boost::asio::async_write(fSocket, 
    boost::asio::buffer(fMsg_send.GetData(), fMsg_send.GetLength()),
    [&](const boost::system::error_code& result_error,
        std::size_t /*result_n*/)
    {
        res.error = result_error;
    });

    // Run the operation until it completes, or until the timeout.
    Run(timeout);
    res.success = !res.error.failed();

    return res.success;
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

bool MVRxchangeClient::Connect(SendResult& res, const std::string& host, const std::string& service, std::chrono::steady_clock::duration timeout)
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
            res.error = result_error;
        });


    // Run the operation until it completes, or until the timeout.
    Run(timeout);

    return res.success = !res.error.failed();
}
