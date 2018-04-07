#pragma once

#include <boost/asio/ip/tcp.hpp>

class UserSession;

class ChatRoom : public std::enable_shared_from_this<ChatRoom>
{
public:
	ChatRoom(boost::asio::io_context& ioc, boost::asio::ip::tcp::endpoint endpoint);

	void Run();

	void DoAccept();
	void OnAccept(boost::system::error_code ec);

	void OnAuthenticated(UserSession* session);
	void OnChatMessage(UserSession* session, std::string message);
	void OnDisconnected(UserSession* session);

	std::vector<std::string> GetUserList() const;

private:
	boost::asio::ip::tcp::acceptor mAcceptor;
	boost::asio::ip::tcp::socket mSocket;

	std::vector<std::shared_ptr<UserSession>> mUserSessions;

};