#include "chat_client.h"
#include "connection_exception.h"

#include "njson/json.hpp"

#include <iostream>
#include <sstream>

using json = nlohmann::json;

void on_fail(client * c, websocketpp::connection_hdl hdl) {
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    throw ConnectionException(con->get_ec().message());
}

void on_close(client * c, websocketpp::connection_hdl hdl) {
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    if (con->get_remote_close_code() == websocketpp::close::status::abnormal_close)
    {
        std::stringstream s;
        s << "close code: " << con->get_remote_close_code() << " (" 
            << websocketpp::close::status::get_string(con->get_remote_close_code()) 
            << "), close reason: " << con->get_remote_close_reason();
        throw ConnectionException(s.str());
    }
}

ChatClient::ChatClient(const std::string& uri)
{
    m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
    m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

    m_endpoint.init_asio();
    m_endpoint.start_perpetual();

    m_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &m_endpoint);

    websocketpp::lib::error_code ec;

    client::connection_ptr con = m_endpoint.get_connection(uri, ec);

    if (ec)
        throw ConnectionException(ec.message());

    m_hdl = con->get_handle();

    con->set_open_handler(websocketpp::lib::bind(&ChatClient::on_open, this, websocketpp::lib::placeholders::_1));
    con->set_message_handler(websocketpp::lib::bind(&ChatClient::on_message, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
    con->set_fail_handler(websocketpp::lib::bind(&on_fail, &m_endpoint, websocketpp::lib::placeholders::_1));
    con->set_close_handler(websocketpp::lib::bind(&on_close, &m_endpoint, websocketpp::lib::placeholders::_1));

    m_endpoint.connect(con);
}

ChatClient::~ChatClient()
{
    m_endpoint.stop_perpetual();
    
    if (m_open)
    {
        std::cout << "> Closing connection " << std::endl;
    
        websocketpp::lib::error_code ec;
        m_endpoint.close(m_hdl, websocketpp::close::status::normal, "", ec);
        if (ec)
            std::cerr << "> Error closing connection: " << ec.message() << std::endl;
    }
    m_thread->join();
}

void ChatClient::send(const std::string& message)
{
    websocketpp::lib::error_code ec;
    
    m_endpoint.send(m_hdl, message, websocketpp::frame::opcode::text, ec);
    if (ec) {
        std::cout << "> Error sending message: " << ec.message() << std::endl;
    }
}

void ChatClient::on_open(websocketpp::connection_hdl hdl)
{
    m_open = true;
    std::cout << "< Connected" << std::endl;
}

void ChatClient::on_message(websocketpp::connection_hdl, client::message_ptr msg)
{
    json message = json::parse(msg->get_payload());
    if (message["type"] == "handshake_reply")
    {
        if (message.find("user_list") != message.end())
        {
            is_registered = true;
            std::cout << "< Welcome" << std::endl;
            std::cout << "< Present users: " << message["user_list"].dump() << std::endl;
        }
        else
        {
            std::cerr << "< Error during registration: " << message["error"].get<std::string>() << std::endl;
        }
    }
    else if (message["type"] == "user_joined")
    {
        std::cout << "< " << message["name"].get<std::string>() << " joined" << std::endl;
    }
    else if (message["type"] == "user_left")
    {
        std::cout << "<" << message["name"].get<std::string>() << " left" << std::endl;
    }
    else if (message["type"] == "on_message")
    {
        std::cout << "< " << message["username"].get<std::string>() << ": " << message["message"].get<std::string>() << std::endl;
    }
    else
    {
        std::cout << "< unknown message: " << msg->get_payload() << std::endl;
    }
}

void ChatClient::set_name(const std::string& name)
{
    send("{\"type\": \"handshake\", \"name\": \"" + name + "\"}");
}
