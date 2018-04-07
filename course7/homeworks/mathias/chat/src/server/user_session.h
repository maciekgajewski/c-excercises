#pragma once

#include "protocol.h"

#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include <memory>

class ChatRoom;

class UserSession : public ChatProtocol::IProtocolHandler, public std::enable_shared_from_this<UserSession>
{
public:
	enum class State
	{
		Disconnected = 0,
		Connected,
		Authenticated,
	};

	explicit UserSession(ChatRoom& chatRoom, boost::asio::ip::tcp::socket socket);

	void Run();
	void OnAccept(boost::system::error_code ec);

	void DoRead();
	void OnRead(boost::system::error_code ec, std::size_t bytes_transferred);
	void OnWrite(std::shared_ptr<std::string> msg, boost::system::error_code ec, std::size_t bytes_transferred);


	template<typename ProtocolMessage>
	void Send(const ProtocolMessage& protocolMessage)
	{
		json obj = protocolMessage;
		SendMessage(obj.dump());
	}

	State GetState() const { return mState; }
	const std::string& GetName() const { return mUserName; }

private:
	void fail(boost::system::error_code ec, char const* what);

	void SendMessage(const std::string& message);

	void ParseMessage(const std::string& message);

	void Handle(const ChatProtocol::Handshake&) override;
	void Handle(const ChatProtocol::HandshakeReply&) override;
	void Handle(const ChatProtocol::Message&) override;
	void Handle(const ChatProtocol::OnMessage&) override;
	void Handle(const ChatProtocol::Error&) override;
	void Handle(const ChatProtocol::UserJoined&) override;
	void Handle(const ChatProtocol::UserLeft&) override;

	ChatRoom& mChatRoom;
	boost::beast::websocket::stream<boost::asio::ip::tcp::socket> mWebSocket;
	boost::asio::strand<boost::asio::io_context::executor_type> mStrand;
	boost::beast::multi_buffer mBuffer;

	State mState = State::Disconnected;
	std::string mUserName;
};
