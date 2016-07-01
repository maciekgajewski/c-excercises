#include "debugger_state.hh"

#include <QIODevice>

#include <QtGlobal>

#include <iostream>

namespace Teabag {

DebuggerState::DebuggerState(QIODevice* process, QObject* p)
	: QObject(p), process_(process)
{
	fatalError_ = [this](const InputRecord& input)
	{
		if (input.inputClass == "error")
		{
			emit fatalError(input.result.get<QString>("msg"));
		}
	};
}

DebuggerState::~DebuggerState()
{
}

void DebuggerState::processInput(const QList<InputRecord>& notifications, const boost::optional<InputRecord>& result)
{
	if (result)
	{
		if (result->token > 0)
		{
			auto it = resultHandlers_.find(result->token);
			Q_ASSERT(it != resultHandlers_.end());
			(*it)(*result);
			resultHandlers_.erase(it);
		}
	}
	foreach(const InputRecord& ir, notifications)
	{
		std::cout << "NOTIFICATION: " << ir.type.toLatin1() << " " << ir.inputClass.toStdString() << " " << toJson(ir.result).toStdString() << std::endl;
	}

	// ignore input
	if (!started_)
	{
		sendCommand("-break-insert main", fatalError_);
		sendCommand("-exec-run", fatalError_);
		started_ = true;
	}
}

void DebuggerState::sendCommand(const QString& cmd, DebuggerState::ResultHandler h)
{
	int token = nextToken_++;

	QString withToken = QString::number(token) + cmd;

	process_->write(withToken.toLocal8Bit());
	process_->write("\n");

	resultHandlers_[token] = h;

}

}

