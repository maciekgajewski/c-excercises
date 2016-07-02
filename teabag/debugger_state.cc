#include "debugger_state.hh"

#include <iostream>

namespace Teabag {

DebuggerState::DebuggerState()
{
	fatalError_ = [this](const InputRecord& input)
	{
		if (input.inputClass == "error")
		{
			throw std::runtime_error(input.result.get<std::string>("msg"));
		}
	};
}

DebuggerState::~DebuggerState()
{
}

void DebuggerState::processInput(const std::vector<InputRecord>& notifications, const boost::optional<InputRecord>& result)
{
	if (result)
	{
		if (result->token > 0)
		{
			auto it = resultHandlers_.find(result->token);
			assert(it != resultHandlers_.end());
			it->second(*result);
			resultHandlers_.erase(it);
		}
	}
	for(const InputRecord& ir : notifications)
	{
		std::cout << "NOTIFICATION: " << ir.type << " " << ir.inputClass << " " << toJson(ir.result) << std::endl;
	}

	// ignore input
	if (!started_)
	{
		sendCommand("-break-insert main", fatalError_);
		sendCommand("-exec-run", fatalError_);
		started_ = true;
	}
}

void DebuggerState::sendCommand(const std::string& cmd, DebuggerState::ResultHandler h)
{
	int token = nextToken_++;

	std::string withToken = std::to_string(token) + cmd;

//	process_->write(withToken.toLocal8Bit());
//	process_->write("\n");
	// TODO

	resultHandlers_[token] = h;

}

}

