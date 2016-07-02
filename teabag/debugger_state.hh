#pragma once

#include "types.hh"

#include <boost/optional.hpp>

#include <functional>
#include <map>

namespace Teabag {

class DebuggerState
{
public:
	DebuggerState();
	~DebuggerState();

	void processInput(const std::vector<InputRecord>& notifications, const boost::optional<InputRecord>& result);

private:

	using ResultHandler = std::function<void(const InputRecord&)>;

	void sendCommand(const std::string& cmd, ResultHandler h);

	bool started_ = false;

	std::map<int, ResultHandler> resultHandlers_;
	int nextToken_ = 1;
	ResultHandler fatalError_;
};

}

