#include "protocol.h"

namespace ChatProtocol
{
void to_json(json& obj, const Error& error)
{
	obj = json{
		{ "type", "error" },
		{ "description", error.Description }
	};
}

void from_json(const json& obj, Error& error)
{
	error.Description = obj.at("description").get<std::string>();
}

void to_json(json& obj, const Handshake& handshake)
{
	obj = json{
		{ "type", "handshake" },
		{ "username", handshake.Username }
	};

	if (handshake.UserData)
	{
		obj["userdata"] = *handshake.UserData;
	}
}

void from_json(const json& obj, Handshake& handshake)
{
	handshake.Username = obj.at("username").get<std::string>();

	auto userDataIt = obj.find("userdata");
	if (userDataIt != std::end(obj))
		handshake.UserData = userDataIt->get<json>();
}

void to_json(json& obj, const HandshakeReply&)
{
	obj = json{
		{ "type", "handshake_reply" },
	};
}

void from_json(const json&, HandshakeReply&)
{

}

void to_json(json& obj, const Message& message)
{
	obj = json{
		{ "type", "message" },
		{ "text", message.Text }
	};
}

void from_json(const json& obj, Message& message)
{
	message.Text = obj.at("text").get<std::string>();
}

void to_json(json& obj, const OnMessage& onMessage)
{
	obj = json{
		{ "type", "on_message" },
		{ "username", onMessage.Username },
		{ "text", onMessage.Text }
	};
}

void from_json(const json& obj, OnMessage& onMessage)
{
	onMessage.Username = obj.at("username").get<std::string>();
	onMessage.Text = obj.at("text").get<std::string>();
}

void to_json(json& obj, const UserJoined& userJoined)
{
	obj = json{
		{ "type", "user_joined" },
		{ "username", userJoined.Username}
	};
}

void from_json(const json& obj, UserJoined& userJoined)
{
	userJoined.Username = obj.at("username").get<std::string>();
}

void to_json(json& obj, const UserLeft& userLeft)
{
	obj = json{
		{ "type", "user_left" },
		{ "username", userLeft.Username }
	};
}

void from_json(const json& obj, UserLeft& userLeft)
{
	userLeft.Username = obj.at("username").get<std::string>();
}

void from_json(const json& obj, ProtocolMessage& protocolMessage)
{
	const auto& type = obj["type"];
	protocolMessage.Valid = true;

	if (type == "handshake")
	{
		Handshake h = obj;
		protocolMessage.Message = h;
	}
	else if (type == "handshake_reply")
	{
		HandshakeReply h = obj;
		protocolMessage.Message = h;
	}
	else if (type == "message")
	{
		Message h = obj;
		protocolMessage.Message = h;
	}
	else if (type == "on_message")
	{
		OnMessage h = obj;
		protocolMessage.Message = h;
	}
	else if (type == "error")
	{
		Error h = obj;
		protocolMessage.Message = h;
	}
	else
	{
		protocolMessage.Valid = false;
	}
}
}
