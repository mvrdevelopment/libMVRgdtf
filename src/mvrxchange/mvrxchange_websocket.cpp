#include "mvrxchange_websocket.h"
#include <iostream>

WebSocketClient::WebSocketClient(net::io_context& ioc, const std::string& url)
    : ioc_(ioc)
    , resolver_(net::make_strand(ioc))
    , url_(url)
    , ping_timer_(ioc)
    , work_guard_(net::make_work_guard(ioc))
{
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
        throw std::invalid_argument("Invalid URL protocol");
    }

    protocol_ = protocol;
    host_ = host;
    port_ = port;
    target_ = target;
    running_ = true;

    if (protocol_ == "wss") 
    {
        port_ = "443";
        ssl_ctx_ = std::make_shared<ssl::context>(ssl::context::sslv23_client);
        ws_ssl_ = std::make_unique<websocket::stream<beast::ssl_stream<beast::tcp_stream>>>(net::make_strand(ioc), *ssl_ctx_);
    } else {
        ws_plain_ = std::make_unique<websocket::stream<beast::tcp_stream>>(net::make_strand(ioc));
    }

    fThread_ = std::thread(&WebSocketClient::RunClient, this);
}

void WebSocketClient::Connect(std::function<void(const MVRxchangeNetwork::MVRxchangePacket& msg)> on_message)
{
    on_message_ = on_message;

    if (protocol_ == "wss") {
        this->run_ssl_websocket_client();
    } 
    else 
    {
        this->run_websocket_client();
    }
}

void WebSocketClient::RunClient()
{
    while (running_) 
    {
        ioc_.run_for(std::chrono::seconds(1));
    }
}

void WebSocketClient::send_message(const char* data, const size_t& size, bool clean_json)
{
    {
        std::unique_lock<std::mutex> lock(connection_mutex_);
        connection_cv_.wait(lock, [this] { return connection_ready_; });
    }

    auto buffer = std::make_shared<std::vector<char>>(data, data + size);

    {
        std::lock_guard<std::mutex> lock(send_mutex_);
        send_queue_.push_back(buffer);
    }

    if (send_queue_.size() == 1)
        do_write(clean_json);
}

void WebSocketClient::do_write(bool clean_json)
{
    if (send_queue_.empty())
        return;

    std::shared_ptr<std::vector<char>> msg;
    {
        std::lock_guard<std::mutex> lock(send_mutex_);
        msg = send_queue_.front();

        if (clean_json) {
            std::string json_string(msg->begin(), msg->end());
            std::string cleaned_json = this->clean_json(json_string);
            msg = std::make_shared<std::vector<char>>(cleaned_json.begin(), cleaned_json.end());
        }
    }

    auto write_callback = [this, msg, clean_json](beast::error_code ec, std::size_t bytes_transferred) 
        {
            if (!ec) 
            {
                {
                    std::lock_guard<std::mutex> lock(send_mutex_);
                    send_queue_.pop_front();
                }

                this->do_write(clean_json);
            } else {
                std::string msg = ec.message();
            }
        };

    try 
    {
        if (protocol_ == "wss" && ws_ssl_) 
        {
            ws_ssl_->async_write(net::buffer(*msg), write_callback);
        } 
        else if (protocol_ == "ws" && ws_plain_) 
        {
            ws_plain_->async_write(net::buffer(*msg), write_callback);
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception caught in async_write: " << e.what() << std::endl;
    }
}

void WebSocketClient::read_message()
{
    auto read_callback = [this](beast::error_code ec, std::size_t bytes_transferred) {
        if (!ec) 
        {
            std::string data = beast::buffers_to_string(buffer_.data());
            buffer_.consume(buffer_.size());

            MVRxchangeNetwork::MVRxchangePacket packet;
            packet.SetBody(bytes_transferred, const_cast<char*>(data.c_str()));
            packet.DecodeHeader();
            if (on_message_)
                on_message_(packet);

            this->read_message();
        } 
        else 
        {
            std::string msg = ec.message();

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            this->read_message();
        }
        };

    try 
    {
        if (protocol_ == "wss" && ws_ssl_) 
        {
            ws_ssl_->async_read(buffer_, read_callback);
        } 
        else if (protocol_ == "ws" && ws_plain_ ) 
        {
            ws_plain_->async_read(buffer_, read_callback);
        }
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Exception caught in async_read: " << e.what() << std::endl;
    }
}

void WebSocketClient::send_ping()
{
    auto self = shared_from_this();
    ping_timer_.expires_after(std::chrono::seconds(1));
    ping_timer_.async_wait([this, self](beast::error_code ec) 
        {
            if (!ec) 
            {
                auto ping_callback = [this, self](beast::error_code ec) 
                    {
                        if (!ec) 
                        {
                            this->send_ping();
                        } 
                        else 
                        {
                            std::string msg = ec.message();
                        }
                    };

                try 
                {
                    if (protocol_ == "wss") 
                    {
                        ws_ssl_->async_ping({}, ping_callback);
                    } 
                    else 
                    {
                        ws_plain_->async_ping({}, ping_callback);
                    }
                }
                catch (const std::exception& e) 
                {
                    std::cerr << "Exception caught in async_ping: " << e.what() << std::endl;
                }
            }
            else 
            {
                std::string msg = ec.message();
            }
        });
}

void WebSocketClient::close()
{
    if (protocol_ == "wss") 
    {
        ws_ssl_->async_close(websocket::close_code::normal,
            [this](beast::error_code ec) {
                if (ec) {
                    std::string msg = ec.message();
                }
            });
    } 
    else 
    {
        ws_plain_->async_close(websocket::close_code::normal,
            [this](beast::error_code ec) {
                if (ec) {
                    std::string msg = ec.message();
                }
            });
    }
    running_ = false;
    if (fThread_.joinable()) 
    {
        fThread_.join();
    }
}

void WebSocketClient::run_ssl_websocket_client()
{
    try 
    {
        tcp::resolver resolver(ioc_);
        auto const results = resolver.resolve(host_, port_);

        beast::get_lowest_layer(*ws_ssl_).connect(results);

        ws_ssl_->next_layer().handshake(ssl::stream_base::client);

        ws_ssl_->set_option(websocket::stream_base::decorator(
            [](websocket::request_type& req) {
                req.set(beast::http::field::user_agent, "Boost.Beast WebSocket Client");
            }));
        ws_ssl_->handshake(host_, target_);

        {
            std::lock_guard<std::mutex> lock(connection_mutex_);
            connection_ready_ = true;
        }
        connection_cv_.notify_all();

        this->read_message();
        this->send_ping();
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error in run_websocket_client: " << e.what() << std::endl;
    }
}

void WebSocketClient::run_websocket_client()
{
    try 
    {
        auto const results = resolver_.resolve(host_, port_);
        auto& ws_plain = *ws_plain_;
        beast::get_lowest_layer(ws_plain).expires_never();
        beast::get_lowest_layer(ws_plain).async_connect(results,
            [this, &ws_plain](beast::error_code ec, tcp::resolver::results_type::endpoint_type) {
                if (!ec) {
                    ws_plain.async_handshake(host_ + ":" + port_, target_,
                        [this, &ws_plain](beast::error_code ec) {
                            if (!ec) {
                                {
                                    std::lock_guard<std::mutex> lock(connection_mutex_);
                                    connection_ready_ = true;
                                }
                                connection_cv_.notify_all();
                                this->read_message();
                                this->send_ping();
                            } else {
                                std::string msg = ec.message();
                            }
                        });
                } else {
                    std::string msg = ec.message();
                }
            });
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error in run_websocket_client: " << e.what() << std::endl;
    }
}

std::string WebSocketClient::clean_json(const std::string& json) {
    std::string cleaned;

    for (char c : json) 
    {
        if ((c >= 32 && c <= 126) || c == '\n' || c == '\t' || c == '\r') {
            cleaned += c;
        }
    }

    return cleaned;
}
