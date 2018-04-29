#include "json.hpp"
#include "protocol.h"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;
using json = nlohmann::json;

std::string buildHandshakeRequest(const std::string& nick)
{
	ChatProtocol::Handshake handshakeObj { nick };
	json handshake = handshakeObj;
	return handshake.dump();
}

std::string buildMessage(const std::string& text)
{
	ChatProtocol::Message sendMessage { text };
	json message = sendMessage;
	return message.dump();
}

void write(websocket::stream<tcp::socket>& ws, const std::string& msg)
{
	ws.write(boost::asio::buffer(msg));
	std::cout << "> " << msg << std::endl;
}

std::string readFromWebSocket(websocket::stream<tcp::socket>& ws)
{
	boost::beast::multi_buffer buffer;
	ws.read(buffer);
	//std::string str = boost::beast::buffers(buffer.data());
	std::string str = boost::beast::buffers_to_string(buffer.data());
	//buffer.consume(buffer.size());
	return str;
}

int main(int argc, char** argv)
{
	try
	{
		if(argc != 5)
		{
			std::cerr <<
				"Usage: websocket-client-sync <host> <port> <nick> <text>\n" <<
				"Example:\n" <<
				"    websocket-client-sync echo.websocket.org 80 \"Hello, world!\"\n";
			return EXIT_FAILURE;
		}
		auto const host = argv[1];
		auto const port = argv[2];
		auto const nick = argv[3];
		auto const text = argv[4];

		boost::asio::io_context ioc;

		tcp::resolver resolver{ioc};
		websocket::stream<tcp::socket> ws{ioc};

		auto const results = resolver.resolve(host, port);
		boost::asio::connect(ws.next_layer(), results.begin(), results.end());
		ws.handshake(host, "/");

		write(ws, buildHandshakeRequest(std::string(nick)));

		std::cout << "< " << readFromWebSocket(ws) << std::endl;

		write(ws, buildMessage(text));

		while (true)
		{
			std::cout << "< " << readFromWebSocket(ws) << std::endl;
		}
		ws.close(websocket::close_code::normal);
	}
	catch(std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}