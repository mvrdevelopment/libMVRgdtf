#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/connect.hpp>
#include "mvrxchange_client.h"

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

class WebSocketClient : public std::enable_shared_from_this<WebSocketClient> {
public:
    // Constructor: takes an io_context and URL (e.g. "wss://example.com:443/path")
    WebSocketClient(net::io_context& ioc, const std::string& url);

    void Connect(std::function<void(const MVRxchangeNetwork::MVRxchangePacket& msg)> on_message);

    void send_message(const char* data, const size_t& size, bool cleanJSON);

    void close();

private:
    void RunClient();
    void read_message();
    void send_ping();
    void run_ssl_websocket_client();
    void run_websocket_client();
    void do_write(bool cleanJSON);
    std::string clean_json( const std::string& json );

private:

    net::executor_work_guard<net::io_context::executor_type> work_guard_;
    net::io_context& ioc_;
    tcp::resolver resolver_;
    std::string url_;

    std::string protocol_;
    std::string host_;
    std::string port_;
    std::string target_;

    bool running_;
    bool connection_ready_ = false;
    std::mutex connection_mutex_;
    std::condition_variable connection_cv_;

    // Queue for outgoing messages (to avoid overlapping writes)
    std::deque<std::shared_ptr<std::vector<char>>> send_queue_;
    std::mutex send_mutex_;

    // Ping timer to keep the connection alive
    net::steady_timer ping_timer_;

    // WebSocket streams for plain or SSL
    std::unique_ptr<websocket::stream<beast::tcp_stream>> ws_plain_;
    std::unique_ptr<websocket::stream<beast::ssl_stream<beast::tcp_stream>>> ws_ssl_;
    std::shared_ptr<ssl::context> ssl_ctx_;

    // Buffer for incoming data
    beast::flat_buffer buffer_;

    // Callback for received messages
    std::function<void(const MVRxchangeNetwork::MVRxchangePacket& msg)> on_message_;

    // Thread to run the io_context
    std::thread fThread_;

    bool use_clean_json_;
};
#endif // WEBSOCKETCLIENT_H
