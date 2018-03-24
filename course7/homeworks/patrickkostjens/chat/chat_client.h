#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <string>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class ChatClient {
public:
    ChatClient (const std::string& uri);
    ~ChatClient();

    void set_name(const std::string& name);
    void send(const std::string& message);
    bool is_registered;

private:
    void on_open(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl, client::message_ptr msg);

    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

    websocketpp::connection_hdl m_hdl;
    bool m_open;
};