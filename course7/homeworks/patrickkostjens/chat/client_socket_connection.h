#pragma once

#include "connection_exception.h"

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

class ClientSocketConnection {
public:
    ClientSocketConnection (const std::string& uri);
    ~ClientSocketConnection();

    void send(std::string message);

private:
    void on_open(websocketpp::connection_hdl hdl);

    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

    websocketpp::connection_hdl m_hdl;
    bool m_open;
};