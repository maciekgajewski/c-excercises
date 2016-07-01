#include "debugger.hh"

#include "debugger_state.hh"

#include <QProcess>

#include <iostream>

namespace Teabag {

Debugger::Debugger(QObject *p) : QObject(p)
{
	debuggerProcess_ = new QProcess(this);

	connect(debuggerProcess_, SIGNAL(finished(int)), SLOT(onFinished()));
	connect(debuggerProcess_, SIGNAL(readyReadStandardOutput()), SLOT(onStdOutData()));
	connect(debuggerProcess_, SIGNAL(readyReadStandardError()), SLOT(onStdErrData()));
}

Debugger::~Debugger()
{
}

void Debugger::start(const QString& binary)
{
	QString gdb = "gdb";
	QStringList args = {"--interpreter=mi", binary};

	debuggerProcess_->start(gdb, args);
	delete state_;
	state_ = new DebuggerState(debuggerProcess_, this);
	connect(state_, SIGNAL(fatalError(QString)), SLOT(onDebugerError(QString)));
}

void Debugger::onStdOutData()
{
	QByteArray line = debuggerProcess_->readLine(4096);
	while(!line.isEmpty())
	{
		processLine(line.simplified());
		line = debuggerProcess_->readLine(4096);
	}
}

void Debugger::onStdErrData()
{
	std::cerr << debuggerProcess_->readAllStandardError().data() << std::endl;
}

void Debugger::onFinished()
{
	// TODO
	emit finished();
}

void Debugger::onDebugerError(const QString& error)
{
	std::cerr << "Fatal debugger error :" << error.toStdString() << std::endl;
	emit finished();
}

std::string parseCString(const std::string& result, size_t& pos)
{
	if (result[pos] != '"')
		throw std::runtime_error("Error parsing " + result + ", Expceting \" at pos " + std::to_string(pos));

	std::string out;

	pos++;
	for(pos++; result[pos] != '"'; ++pos)
	{
		if (result[pos] == '\\')
		{
			++pos;
		}
		out.push_back(result[pos]);
	}

	return out;
}

static Result parseValue(const std::string& result, size_t& pos);
static std::pair<std::string, Result> parseResult(const std::string& result, size_t& pos);

static Result parseTuple(const std::string& result, size_t& pos)
{
	if (result[pos] != '{')
		throw std::runtime_error("Error parsing " + result + ", Expceting \" at pos " + std::to_string(pos));

	Result out;

	for(;;)
	{
		pos ++;
		auto kv = parseResult(result, pos);
		out.push_back(kv);
		std::cout << "tuple, got field=" << kv.first << ", string forward is: " << (result.c_str() + pos) << std::endl;
		pos++;
		if (result[pos] == ',')
		{
			continue;
		}
		else if (result[pos] == '}')
		{
			break;
		}
		throw std::runtime_error("Error parsing " + result + ", Expceting , or } at pos " + std::to_string(pos) + ", found " + std::string(1, result[pos]) + " instead");
	}

	return out;
}

static Result parseArray(const std::string& result, size_t& pos)
{
	Result out;
	// TODO
	return out;
}

static Result parseValue(const std::string& result, size_t& pos)
{
	Result value;
	if (result[pos] == '"')
		value = Result(parseCString(result, pos));
	else if (result[pos] == '{')
		return parseTuple(result, pos);
	else if (result[pos] == '[')
		return parseArray(result, pos);
	else
		throw std::runtime_error("Error parsing " + result + ", unknown data type at pos " + std::to_string(pos));

	return value;
}

static std::pair<std::string, Result> parseResult(const std::string& result, size_t& pos)
{
	if (result.empty())
		return {{}, {}};

	auto eqIdx = result.find_first_of('=', pos);
	if (eqIdx == std::string::npos)
	{
		throw std::runtime_error("Error parsing " + result + " : expected key=value at pos " + std::to_string(pos));
	}

	std::string key = result.substr(pos, eqIdx - pos);

	pos = eqIdx + 1;
	return {key, parseValue(result, pos)};
}

void Debugger::processLine(const QString& line)
{
	if (line.length() < 1)
		return;

	if (line == "(gdb)")
	{
		processOutput();
		notifications_.clear();
		result_.reset();
		return;
	}

	if (line[0] == '~')
	{
		emit consoleOutput(line.right(line.length()-1));
		return;
	}

	if (line[0] == '@')
	{
		emit targetOutput(line.right(line.length()-1));
		return;
	}

	QRegExp regexp("(\\d+)?([*+=^])([^,]+)(,(.+))?");

	if (!regexp.exactMatch(line))
	{
		std::cerr << "Failed to parse: " << line.toStdString() << std::endl;
		return;
	}

	QString token = regexp.cap(1);
	QString typeChar = regexp.cap(2);
	QString resultClass = regexp.cap(3);
	QString result = regexp.cap(5);

	InputRecord record;
	record.token = token.toInt();
	record.type = typeChar[0];
	record.inputClass = resultClass;
	size_t pos = 0;
	record.result.push_back(parseResult(result.toStdString(), pos));

	if (record.type == '^')
		result_ = record;
	else
		notifications_.append(record);
}

void Debugger::processOutput()
{
	state_->processInput(notifications_, result_);
}


}

