#pragma once

#include "types.hh"

#include <boost/optional.hpp>

#include <functional>
#include <map>

namespace Teabag {

class IEventSink;

class DebuggerState
{
public:
	DebuggerState(IEventSink& s);
	~DebuggerState();

	// Recrevies parsed input from debugger, returns output
	std::string processInput(const std::vector<InputRecord>& notifications, const boost::optional<InputRecord>& result);

private:

	using ResultHandler = std::function<void(const InputRecord&)>;

	struct Frame
	{
		void* addr;
		std::string function;
		// TODO
	};

	void sendCommand(const std::string& cmd, ResultHandler h);
	void onStopped(const InputRecord&);

	bool started_ = false;

	std::map<int, ResultHandler> resultHandlers_;
	int nextToken_ = 1;
	ResultHandler fatalError_;
	std::string commandBuffer_;
	IEventSink& sink_;
};

}

