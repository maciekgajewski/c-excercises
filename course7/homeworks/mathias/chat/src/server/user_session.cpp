#include "user_session.h"
#include "chat_room.h"

#include <boost/asio/bind_executor.hpp>

UserSession::UserSession(ChatRoom& chatRoom, boost::asio::ip::tcp::socket socket)
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

	mState = State::Connected;

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

	if (ec == boost::beast::websocket::error::closed)
	{
		mState = State::Disconnected;
		mChatRoom.OnDisconnected(this);
		return;
	}

	if (ec)
		return fail(ec, "read");

	mWebSocket.text(mWebSocket.got_text());
	auto msg = boost::beast::buffers_to_string(mBuffer.data());

	try
	{
		ParseProtocolMessage(msg);
	}
	catch (const IProtocolHandler::MessageTypeUnknownError)
	{
		return Send(ChatProtocol::Error{ "Message Type not know" });
	}

	mBuffer.consume(mBuffer.size());

	DoRead();
}

void UserSession::OnWrite(std::shared_ptr<std::string>, boost::system::error_code ec, std::size_t bytes_transferred)
{
	boost::ignore_unused(bytes_transferred);

	if (ec)
		return fail(ec, "write");
}

void UserSession::Handle(const ChatProtocol::Handshake& handshake)
{
	if (mState != State::Connected)
		return Send(ChatProtocol::Error{ "Already authenticated" });

	mState = State::Authenticated;
	mUserName = handshake.Username;
	mChatRoom.OnAuthenticated(this);

	Send(ChatProtocol::HandshakeReply{ mChatRoom.GetUserList() });
}

void UserSession::Handle(const ChatProtocol::HandshakeReply&)
{
	Send(ChatProtocol::Error{ "Message not supported" });
}

void UserSession::Handle(const ChatProtocol::Message& message)
{
	if (mState != State::Authenticated)
		return Send(ChatProtocol::Error{ "Not authenticated" });

	mChatRoom.OnChatMessage(this, message.Text);
}

void UserSession::Handle(const ChatProtocol::OnMessage&)
{
	Send(ChatProtocol::Error{ "Message not supported" });
}

void UserSession::Handle(const ChatProtocol::Error&)
{
	Send(ChatProtocol::Error{ "Message not supported" });
}

void UserSession::Handle(const ChatProtocol::UserJoined&)
{
	Send(ChatProtocol::Error{ "Message not supported" });
}

void UserSession::Handle(const ChatProtocol::UserLeft&)
{
	Send(ChatProtocol::Error{ "Message not supported" });
}

void UserSession::SendMessage(const std::string& message)
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