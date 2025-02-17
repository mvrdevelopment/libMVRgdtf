#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <functional>
#include <memory>
#include <string>
#include <condition_variable>
#include <mutex>
#include "mvrxchange_client.h"

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

class WebSocketClient {
public:
    WebSocketClient(boost::asio::io_context& ioc, const std::string& url);
    void Connect(std::function<void(const MVRxchangeNetwork::MVRxchangePacket& msg)> on_message);
    void send_message(const char* data, const size_t& size);
    void close();

private:
    void RunClient();
    void read_message();

    boost::asio::io_context& ioc;
    tcp::resolver resolver_;
    websocket::stream<tcp::socket> ws_;
    std::string url_;
    std::string protocol_, host_, port_, target_;
    std::thread fThread;
    bool running;
    std::function<void(const MVRxchangeNetwork::MVRxchangePacket& msg)> on_message_;
    boost::beast::flat_buffer buffer_;

    std::mutex connection_mutex_;
    std::condition_variable connection_cv_;
    bool connection_ready_ = false;
};

#endif // WEBSOCKETCLIENT_H
