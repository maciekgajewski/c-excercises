#include "chat_client.h"
#include "connection_exception.h"

#include <iostream>
#include <sstream>

void on_fail(client* c, websocketpp::connection_hdl hdl) {
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    throw ConnectionException(con->get_ec().message());
}

void on_close(client* c, websocketpp::connection_hdl hdl) {
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

    m_thread = websocketpp::lib::thread(&client::run, &m_endpoint);

    websocketpp::lib::error_code ec;
    client::connection_ptr con = m_endpoint.get_connection(uri, ec);
    if (ec) throw ConnectionException(ec.message());

    m_hdl = con->get_handle();

    namespace pl = websocketpp::lib::placeholders;
    con->set_open_handler(websocketpp::lib::bind(&ChatClient::on_open, this, pl::_1));
    con->set_message_handler(websocketpp::lib::bind(&ChatClient::on_message, this, pl::_1, pl::_2));
    con->set_fail_handler(websocketpp::lib::bind(&on_fail, &m_endpoint, pl::_1));
    con->set_close_handler(websocketpp::lib::bind(&on_close, &m_endpoint, pl::_1));

    m_endpoint.connect(con);
}

ChatClient::~ChatClient()
{
    m_endpoint.stop_perpetual();
    
    if (m_open)
    {
        std::cout << "> Closing connection" << std::endl;
    
        websocketpp::lib::error_code ec;
        m_endpoint.close(m_hdl, websocketpp::close::status::normal, "", ec);
        if (ec) std::cerr << "> Error closing connection: " << ec.message() << std::endl;
    }
    m_thread.join();
}

void ChatClient::on_open(websocketpp::connection_hdl hdl)
{
    m_open = true;
}

void ChatClient::on_message(websocketpp::connection_hdl, client::message_ptr msg)
{
    json message = json::parse(msg->get_payload());
    if (message["type"] == "handshake_reply")
    {
        handle_handshake_reply(message);
    }
    else if (message["type"] == "user_joined")
        std::cout << "< " << message["name"].get<std::string>() << " joined" << std::endl;
    else if (message["type"] == "user_left")
        std::cout << "< " << message["name"].get<std::string>() << " left" << std::endl;
    else if (message["type"] == "on_message")
        std::cout << "< " << message["username"].get<std::string>() << ": " << message["message"].get<std::string>() << std::endl;
    else
        std::cout << "< unknown message: " << msg->get_payload() << std::endl;
}

void ChatClient::send_json(const json& obj)
{
    websocketpp::lib::error_code ec;
    m_endpoint.send(m_hdl, obj.dump(), websocketpp::frame::opcode::text, ec);
    if (ec) std::cerr << "> Error sending message: " << ec.message() << std::endl;
}

void ChatClient::handle_handshake_reply(const json& message)
{
    if (message.find("user_list") != message.end())
    {
        m_is_registered = true;
        std::cout << "< Present users: ";
        for (int i = 0; i < message["user_list"].size(); ++i)
        {
            if (i != 0) std::cout << ", ";
            std::cout << message["user_list"][i]["name"].get<std::string>();
        }
        std::cout << std::endl;
    }
    else
    {
        std::cerr << "< Error during registration: " << message["error"].get<std::string>() << std::endl;
        std::cout << "< Please enter your name again: " << std::endl;
    }
}

void ChatClient::run()
{
    std::cout << "< Enter your name: " << std::endl;
    std::string input;
    while (std::getline(std::cin, input))
    {
        if (m_is_registered) send_json({{"type", "send_message"}, {"message", input}});
        else send_json({{"type", "handshake"}, {"name", input}});
    }
}
