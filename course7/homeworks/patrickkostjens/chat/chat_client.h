#pragma once

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include "njson/json.hpp"

#include <string>

typedef websocketpp::client<websocketpp::config::asio_client> client;
using json = nlohmann::json;

class ChatClient {
public:
    ChatClient (const std::string& uri);
    ~ChatClient();

    void run();

private:
    void on_open(websocketpp::connection_hdl hdl);
    void on_message(websocketpp::connection_hdl, client::message_ptr msg);
    void send_json(const json& obj);
    void handle_handshake_reply(const json& obj);

    client m_endpoint;
    websocketpp::lib::thread m_thread;
    websocketpp::connection_hdl m_hdl;

    bool m_open = false;
    bool m_is_registered = false;
};