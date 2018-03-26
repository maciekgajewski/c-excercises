#pragma once

#include "json.hpp"
using json = nlohmann::json;

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
        boost::optional<json> UserData;
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

    void to_json(json& obj, const Error& error)
    {
        obj = json{
            {
                "error", {
                    { "description", error.Description } 
                }
            }
        };
    }

    void from_json(const json& obj, Error& error)
    {
        error.Description = obj.at("description").get<std::string>();
    }

    void to_json(json& obj, const Handshake& handshake)
    {
        obj = json{
            {
                "handshake", {
                    { "username", handshake.Username } 
                }
            }
        };

        if (handshake.UserData)
        {
            obj["handshake"]["userdata"] = *handshake.UserData;
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
            {
                "handshake_reply", {

                }
            }
        };
    }

    void from_json(const json&, HandshakeReply&)
    {

    }

    void to_json(json& obj, const Message& message)
    {
        obj = json{
            {
                "message", {
                    { "text", message.Text }
                }
            }
        };
    }

    void from_json(const json& obj, Message& message)
    {
        message.Text = obj.at("text").get<std::string>();
    }

    void to_json(json& obj, const OnMessage& onMessage)
    {
        obj = json{
            {
                "on_message", {
                    { "username", onMessage.Username },
                    { "text", onMessage.Text }
                }
            }
        };
    }

    void from_json(const json& obj, OnMessage& onMessage)
    {
        onMessage.Username = obj.at("username").get<std::string>();
        onMessage.Text = obj.at("text").get<std::string>();
    }

    void to_json(json&, const UserJoined&)
    {
    }

    void from_json(const json&, UserJoined&)
    {
    }

    void to_json(json&, const UserLeft&)
    {
    }

    void from_json(const json&, UserLeft&)
    {
    }

    void from_json(const json& obj, ProtocolMessage& protocolMessage)
    {
	    const auto& firstObj = obj.begin();
    	const std::string& type = firstObj.key();
    
        protocolMessage.Valid = true;

        if (type == "handshake")
        {
            Handshake h = *firstObj;
            protocolMessage.Message = h;
        }
        else if (type == "handshake_reply")
        {
            HandshakeReply h = *firstObj;
            protocolMessage.Message = h;
        }
        else if (type == "message")
        {
            Message h = *firstObj;
            protocolMessage.Message = h;
        }
        else if (type == "on_message")
        {
            OnMessage h = *firstObj;
            protocolMessage.Message = h;
        }
        else if (type == "error")
        {
            Error h = *firstObj;
            protocolMessage.Message = h;
        }
        else
        {
            protocolMessage.Valid = false;
        }
    }

    class IProtocolHandler
    {
    public:

    protected:
        // void Parse(const std::string&)
        // {
        //     ChatProtocol::ProtocolMessage msg = json::parse(message);

        //     if (!msg.Valid)
        //         return Send(ChatProtocol::Error { "Message Type not know" } );

        //     boost::apply_visitor(ProtocolVisitor(*this), msg.Message);
        // }

        virtual void Handle(const ChatProtocol::Error&) = 0;
        virtual void Handle(const ChatProtocol::Handshake&) = 0;
        virtual void Handle(const ChatProtocol::HandshakeReply&) = 0;
        virtual void Handle(const ChatProtocol::Message&) = 0;
        virtual void Handle(const ChatProtocol::OnMessage&) = 0;
        virtual void Handle(const ChatProtocol::UserJoined&) = 0;
        virtual void Handle(const ChatProtocol::UserLeft&) = 0;

    //private:
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
};
