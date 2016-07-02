#pragma once

#include <string>

namespace Teabag {


class IEventSink
{
public:

	virtual void debuggerOutput(const std::string&) = 0;
	virtual void targetOutput(const std::string&) = 0;
};

}
