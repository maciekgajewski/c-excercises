#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

class ChatRoom;

// Echoes back all received WebSocket messages
class UserSession : public std::enable_shared_from_this<UserSession>
{
public:

	enum class State
	{
		Disconnected = 0,
		Connected,
		Authenticated,
	};

	// Take ownership of the socket
	explicit UserSession(ChatRoom& chatRoom, tcp::socket socket);

	void Run();
	void OnAccept(boost::system::error_code ec);

	void DoRead();
	void OnRead(boost::system::error_code ec, std::size_t bytes_transferred);
	void OnWrite(std::shared_ptr<std::string> msg, boost::system::error_code ec, std::size_t bytes_transferred);

	void SendChatMessage(const std::string& message);

	State GetState() const { return mState; }
	const std::string& GetName() const { return mUserName; }

private:
	void fail(boost::system::error_code ec, char const* what);

	ChatRoom& mChatRoom;
	websocket::stream<tcp::socket> mWebSocket;
	boost::asio::strand<boost::asio::io_context::executor_type> mStrand;
	boost::beast::multi_buffer mBuffer;

	State mState = State::Disconnected;
	std::string mUserName;
};

class ChatRoom : public std::enable_shared_from_this<ChatRoom>
{
public:
	ChatRoom(boost::asio::io_context& ioc, tcp::endpoint endpoint);

	void Run();

	void DoAccept();
	void OnAccept(boost::system::error_code ec);

	void OnChatMessage(UserSession* session, std::string message);
	void OnDisconnected(UserSession* session);

private:
	tcp::acceptor mAcceptor;
	tcp::socket mSocket;

	std::vector<std::shared_ptr<UserSession>> mUserSessions;

};
