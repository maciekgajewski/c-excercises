#pragma once

#include "types.hh"

#include <boost/optional.hpp>

#include <memory>

namespace Teabag {

class DebuggerState;
class IEventSink;

class Debugger
{
public:
	explicit Debugger(IEventSink& sink);
	~Debugger();

	void run(const char* binaryToDebug);

private:

	void mainLoop();
	void processLine(const std::string& line);

	boost::optional<InputRecord> result_;
	std::vector<InputRecord> notifications_;

	int inFile_ = -1;
	int outFile_ = -1;

	std::unique_ptr<DebuggerState> state_;
	IEventSink& sink_;
};

}
