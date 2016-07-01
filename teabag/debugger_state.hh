#pragma once

#include "types.hh"

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QMap>

#include <boost/optional.hpp>

#include <functional>


class QIODevice;

namespace Teabag {

class DebuggerState : public QObject
{
	Q_OBJECT
public:
	DebuggerState(QIODevice* process, QObject* p = nullptr);
	~DebuggerState();

	void processInput(const QList<InputRecord>& notifications, const boost::optional<InputRecord>& result);

signals:

	void fatalError(const QString& msg);

private:

	using ResultHandler = std::function<void(const InputRecord&)>;

	void sendCommand(const QString& cmd, ResultHandler h);

	bool started_ = false;
	QIODevice* process_ = nullptr;

	QMap<int, ResultHandler> resultHandlers_;
	int nextToken_ = 1;
	ResultHandler fatalError_;

};

}

