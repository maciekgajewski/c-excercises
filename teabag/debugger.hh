#pragma once

#include "types.hh"

#include <QObject>

#include <boost/optional.hpp>

#include <memory>

class QProcess;

namespace Teabag {

class DebuggerState;

class Debugger : public QObject
{
	Q_OBJECT
public:
	explicit Debugger(QObject *p = nullptr);

	~Debugger();

	void start(const QString& binary);

signals:

	void finished();

	void consoleOutput(const QString&);
	void targetOutput(const QString&);

private slots:

	void onStdOutData();
	void onStdErrData();
	void onFinished();
	void onDebugerError(const QString& error);

private:

	void processLine(const QString& line);
	void processOutput();

	QProcess* debuggerProcess_ = nullptr;
	QList<InputRecord> notifications_;
	boost::optional<InputRecord> result_;

	DebuggerState* state_ = nullptr;

};

}
