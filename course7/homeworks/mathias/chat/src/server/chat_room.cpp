#include "chat_room.h"
#include "user_session.h"

#include <iostream>

static void fail(boost::system::error_code ec, char const* what)
{
	std::cerr << what << ": " << ec.message() << "\n";
}

ChatRoom::ChatRoom(boost::asio::io_context& ioc, boost::asio::ip::tcp::endpoint endpoint)
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

void ChatRoom::OnAuthenticated(UserSession* session)
{
	std::string username = session->GetName();
	for (auto& userSession : mUserSessions)
	{
		if (userSession.get() == session)
			continue;

		userSession->Send(ChatProtocol::UserJoined{ username });
	}
}

void ChatRoom::OnChatMessage(UserSession* session, std::string message)
{
	std::cout << "Relaying message from " << session->GetName() << " (" << session << "): " << message << std::endl;
	for (auto& userSession : mUserSessions)
	{
		userSession->Send(ChatProtocol::OnMessage{ session->GetName(), message });
	}
}

void ChatRoom::OnDisconnected(UserSession* session)
{
	std::cout << "Disconnecting " << session->GetName() << " (" << session << ")" << std::endl;
	std::string username = session->GetName();
	mUserSessions.erase(
		std::remove_if(std::begin(mUserSessions), std::end(mUserSessions),
			[&session](const auto& userSession)
			{
				return userSession.get() == session;
			}),
		std::end(mUserSessions));

	for (auto& userSession : mUserSessions)
	{
		userSession->Send(ChatProtocol::UserLeft{ username });
	}
}

std::vector<std::string> ChatRoom::GetUserList() const
{
	std::vector<std::string> userList;

	for (auto& userSession : mUserSessions)
	{
		userList.push_back(userSession->GetName());
	}

	return userList;
}
