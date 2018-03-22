#include "server.h"

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

void fail(boost::system::error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}

UserSession::UserSession(ChatRoom& chatRoom, tcp::socket socket)
	: mChatRoom(chatRoom)
	, mWebSocket(std::move(socket))
	, mStrand(mWebSocket.get_executor())
{
}

void UserSession::fail(boost::system::error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
	mChatRoom.OnDisconnected(this);
}

void UserSession::Run()
{
	mWebSocket.async_accept(
		boost::asio::bind_executor(
			mStrand,
			std::bind(
				&UserSession::OnAccept,
				shared_from_this(),
				std::placeholders::_1)));
}

void UserSession::OnAccept(boost::system::error_code ec)
{
	if (ec)
		return fail(ec, "accept");

	DoRead();
}

void UserSession::DoRead()
{
	mWebSocket.async_read(
		mBuffer,
		boost::asio::bind_executor(
			mStrand,
			std::bind(
				&UserSession::OnRead,
				shared_from_this(),
				std::placeholders::_1,
				std::placeholders::_2)));
}

void UserSession::OnRead(boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	// This indicates that the session was closed
	if (ec == websocket::error::closed)
	{
		mChatRoom.OnDisconnected(this);
		return;
	}

	if (ec)
		return fail(ec, "read");

	mWebSocket.text(mWebSocket.got_text());

	mChatRoom.OnChatMessage(this, boost::beast::buffers_to_string(mBuffer.data()));
	mBuffer.consume(mBuffer.size());

	DoRead();
}

void UserSession::OnWrite(std::shared_ptr<std::string>, boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec)
		return fail(ec, "write");
}

void UserSession::SendChatMessage(const std::string& message)
{
	auto msg = std::make_shared<std::string>(message);
	mWebSocket.async_write(
		boost::asio::buffer(*msg),
		boost::asio::bind_executor(
			mStrand,
			std::bind(
				&UserSession::OnWrite,
				shared_from_this(),
				msg,
				std::placeholders::_1,
				std::placeholders::_2)));
}

ChatRoom::ChatRoom(boost::asio::io_context& ioc, tcp::endpoint endpoint)
	: mAcceptor(ioc)
	, mSocket(ioc)
{
	boost::system::error_code ec;

	mAcceptor.open(endpoint.protocol(), ec);
	if (ec)
	{
		fail(ec, "open");
		return;
	}

	mAcceptor.bind(endpoint, ec);
	if (ec)
	{
		fail(ec, "bind");
		return;
	}

	mAcceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
	if (ec)
	{
		fail(ec, "listen");
		return;
	}
}

void ChatRoom::Run()
{
	if (!mAcceptor.is_open())
		return;
	DoAccept();
}

void ChatRoom::DoAccept()
{
	mAcceptor.async_accept(
		mSocket,
		std::bind(
			&ChatRoom::OnAccept,
			shared_from_this(),
			std::placeholders::_1));
}

void ChatRoom::OnAccept(boost::system::error_code ec)
{
	if (ec)
	{
		fail(ec, "accept");
	}
	else
	{
		auto userSession = std::make_shared<UserSession>(*this, std::move(mSocket));
		mUserSessions.push_back(std::move(userSession));
		mUserSessions.back()->Run();
	}

	DoAccept();
}

void ChatRoom::OnChatMessage(UserSession* session, std::string message)
{
	std::cout << "Relaying message from " << session->GetName() << " (" << session << "): " << message << std::endl;
	for (auto& userSession : mUserSessions)
	{
		userSession->SendChatMessage(message);
	}
}

void ChatRoom::OnDisconnected(UserSession* session)
{
	std::cout << "Disconnecting " << session->GetName() << " (" << session << ")" << std::endl;
	mUserSessions.erase(
		std::remove_if(std::begin(mUserSessions), std::end(mUserSessions), 
			[&session](const auto& userSession) 
			{ 
				return userSession.get() == session; 
			}),
		std::end(mUserSessions));
}

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

	std::make_shared<ChatRoom>(ioc, tcp::endpoint{ address, port })->Run();
	
	ioc.run();

	return EXIT_SUCCESS;
}
