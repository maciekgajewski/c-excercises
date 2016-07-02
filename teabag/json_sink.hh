#pragma once

#include "ievent_sink.hh"

#include <ostream>

namespace Teabag {

class JsonSink : public IEventSink
{
public:
	JsonSink(std::ostream& s);

	void debuggerOutput(const std::string&) override;
	void targetOutput(const std::string&) override;

private:

	std::ostream& stream_;
};

}
