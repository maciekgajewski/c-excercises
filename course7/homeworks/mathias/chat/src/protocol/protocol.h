#pragma once

#include "json.hpp"

#include <boost/optional.hpp>
#include <boost/variant.hpp>

namespace ChatProtocol 
{

struct Error
{
	std::string Description;
};

struct Handshake
{
	std::string Username;
	boost::optional<nlohmann::json> UserData;
};

struct HandshakeReply
{
	std::vector<std::string> Users;
};

struct Message
{
	std::string Text;
};

struct OnMessage
{
	std::string Username;
	std::string Text;
};

struct UserJoined
{
	std::string Username;
};

struct UserLeft
{
	std::string Username;
};

struct ProtocolMessage
{
	boost::variant<Error, Handshake, HandshakeReply, Message, OnMessage, UserJoined, UserLeft> Message;
	bool Valid;
};

void to_json(nlohmann::json& obj, const Error& error);
void from_json(const nlohmann::json& obj, Error& error);

void to_json(nlohmann::json& obj, const Handshake& handshake);
void from_json(const nlohmann::json& obj, Handshake& handshake);

void to_json(nlohmann::json& obj, const HandshakeReply&);
void from_json(const nlohmann::json&, HandshakeReply&);

void to_json(nlohmann::json& obj, const Message& message);
void from_json(const nlohmann::json& obj, Message& message);

void to_json(nlohmann::json& obj, const OnMessage& onMessage);
void from_json(const nlohmann::json& obj, OnMessage& onMessage);

void to_json(nlohmann::json& obj, const UserJoined& userJoined);
void from_json(const nlohmann::json& obj, UserJoined& userJoined);

void to_json(nlohmann::json& obj, const UserLeft& userLeft);
void from_json(const nlohmann::json& obj, UserLeft& userLeft);

void from_json(const nlohmann::json& obj, ProtocolMessage& protocolMessage);

class IProtocolHandler
{
public:
	struct ParseError : std::exception {};
	struct MessageTypeUnknownError : std::exception	{};

protected:
	void ParseProtocolMessage(const std::string& message)
	{
		ChatProtocol::ProtocolMessage msg;

		try
		{
			msg = nlohmann::json::parse(message);
		}
		catch (const nlohmann::json::exception&)
		{
			throw ParseError();
		}

		if (!msg.Valid)
			throw MessageTypeUnknownError();

		boost::apply_visitor(ProtocolVisitor(*this), msg.Message);
	}

	virtual void Handle(const ChatProtocol::Error&) = 0;
	virtual void Handle(const ChatProtocol::Handshake&) = 0;
	virtual void Handle(const ChatProtocol::HandshakeReply&) = 0;
	virtual void Handle(const ChatProtocol::Message&) = 0;
	virtual void Handle(const ChatProtocol::OnMessage&) = 0;
	virtual void Handle(const ChatProtocol::UserJoined&) = 0;
	virtual void Handle(const ChatProtocol::UserLeft&) = 0;

private:
	struct ProtocolVisitor : public boost::static_visitor<>
	{
		ProtocolVisitor(IProtocolHandler& session)
			: Session(session)
		{}

		template<typename T>
		void operator()(T& t) const
		{
			Session.Handle(t);
		}

	private:
		IProtocolHandler& Session;
	};
};

}
