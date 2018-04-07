//#include "server.h"
#include "protocol.h"

#include "chat_room.h"

#include <boost/asio/ip/tcp.hpp>

int main(int, char*) //int argc, char* argv[])
{
#if 0
	// Check command line arguments.
	if (argc != 3)
	{
		std::cerr <<
			"Usage: websocket-server-async <address> <port>\n" <<
			"Example:\n" <<
			"    websocket-server-async 0.0.0.0 8080\n";
		return EXIT_FAILURE;
	}
	auto const address = boost::asio::ip::make_address(argv[1]);
	auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
#endif

	auto const address = boost::asio::ip::make_address("0.0.0.0");
	auto const port = static_cast<unsigned short>(1337);

	boost::asio::io_context ioc{ 1 };

	std::make_shared<ChatRoom>(ioc, boost::asio::ip::tcp::endpoint{ address, port })->Run();
	
	ioc.run();

	return EXIT_SUCCESS;
}
