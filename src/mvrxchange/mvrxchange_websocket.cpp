#include "mvrxchange_websocket.h"
#include <iostream>

WebSocketClient::WebSocketClient(boost::asio::io_context& ioc, const std::string& url)
    : resolver_(ioc), ws_(ioc), url_(url), ioc(ioc) {
    std::string protocol, host, port = "80", target = "/";
    std::string::size_type pos = url.find("://");
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid URL");
    }
    protocol = url.substr(0, pos);
    std::string remainder = url.substr(pos + 3);

    pos = remainder.find('/');
    if (pos != std::string::npos) {
        target = remainder.substr(pos);
        remainder = remainder.substr(0, pos);
    }

    pos = remainder.find(':');
    if (pos != std::string::npos) {
        host = remainder.substr(0, pos);
        port = remainder.substr(pos + 1);
    } else {
        host = remainder;
    }

    if (protocol != "ws" && protocol != "wss") {
        throw std::invalid_argument("Invalid URL");
    }

    protocol_ = protocol;
    host_ = host;
    port_ = port;
    target_ = target;
    running = true;

    fThread = std::thread(&WebSocketClient::RunClient, this);
}

void WebSocketClient::Connect(std::function<void(const MVRxchangeNetwork::MVRxchangePacket& msg)> on_message) {
    on_message_ = on_message;
    auto const results = resolver_.resolve(host_, port_);
    boost::asio::async_connect(ws_.next_layer(), results.begin(), results.end(),
        [this](boost::system::error_code ec, tcp::resolver::iterator) {
            if (!ec) {
                ws_.async_handshake(host_ + ":" + port_, target_,
                    [this](boost::system::error_code ec) {
                        if (!ec) {
                            {
                                std::lock_guard<std::mutex> lock(connection_mutex_);
                                connection_ready_ = true;
                            }
                            connection_cv_.notify_all();
                            read_message();
                        } else {
                            std::cerr << "Handshake error: " << ec.message() << std::endl;
                        }
                    });
            } else {
                std::cerr << "Connect error: " << ec.message() << std::endl;
            }
        });
}

void WebSocketClient::RunClient() {
    while (running) {
        ioc.run_for(std::chrono::seconds(1));
    }
}

void WebSocketClient::send_message(const char* data, const size_t& size) {
    std::unique_lock<std::mutex> lock(connection_mutex_);
    connection_cv_.wait(lock, [this] { return connection_ready_; });

    auto buffer = std::make_shared<std::vector<char>>(data, data + size);

    ws_.async_write(boost::asio::buffer(*buffer),
        [this, buffer](boost::system::error_code ec, std::size_t bytes_transferred) {
            if (ec) {
                std::cerr << "Error sending message: " << ec.message() << std::endl;
            } else {
                std::cout << "Message sent successfully, bytes transferred: " << bytes_transferred << std::endl;
            }
        });
}

void WebSocketClient::close() {
    ws_.async_close(websocket::close_code::normal,
        [this](boost::system::error_code ec) {
            if (ec) {
                // Handle error
            }
        });
	running = false;

	if ( fThread.joinable() )
	{
		fThread.join();
	}
}

void WebSocketClient::read_message() {
    ws_.async_read(buffer_,
        [this](boost::system::error_code ec, std::size_t bytes_transferred) {
            if (!ec) {
                MVRxchangeNetwork::MVRxchangePacket buf;
                auto data = boost::asio::buffer_cast<const char*>(buffer_.data());
                buf.SetBody(bytes_transferred, const_cast<char*>(data));
				buf.DecodeHeader();
                on_message_(buf);
                buffer_.consume(buffer_.size());
                read_message();
            }
        });
}