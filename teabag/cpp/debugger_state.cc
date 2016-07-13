#include "debugger_state.hh"

#include "ievent_sink.hh"

#include <iostream>

namespace Teabag {

DebuggerState::DebuggerState(IEventSink& s)
	: sink_(s)
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

std::string DebuggerState::processInput(const std::vector<InputRecord>& notifications, const boost::optional<InputRecord>& result)
{
	commandBuffer_.clear();
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

	if (!started_)
	{
		sendCommand("-break-insert main", fatalError_);
		sendCommand("-exec-run", fatalError_);
		started_ = true;
	}
	else
	{
		for(const InputRecord& ir : notifications)
		{
			std::cerr << "NOTIFICATION: " << ir.type << " " << ir.inputClass << " " << toJson(ir.result) << std::endl;
			if (ir.type == '*' && ir.inputClass == "stopped")
			{
				onStopped(ir);
			}
		}
	}

	return commandBuffer_;
}

void DebuggerState::sendCommand(const std::string& cmd, DebuggerState::ResultHandler h)
{
	int token = nextToken_++;

	commandBuffer_ += std::to_string(token);
	commandBuffer_ += cmd;
	commandBuffer_ += "\n";

	resultHandlers_[token] = h;
}

void DebuggerState::onStopped(const InputRecord&)
{
	// get: frame, backtrace?
}

}

