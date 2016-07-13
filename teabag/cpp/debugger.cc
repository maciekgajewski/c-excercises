#include "debugger.hh"

#include "debugger_state.hh"
#include "ievent_sink.hh"

#include <iostream>
#include <cassert>
#include <regex>

#include <unistd.h>

namespace Teabag {

Debugger::Debugger(IEventSink& sink) :
	state_(new DebuggerState(sink)), sink_(sink)
{
}

Debugger::~Debugger()
{
}

void Debugger::run(const char* binaryToDebug)
{
	assert(inFile_ == -1);
	assert(outFile_ == -1);

	int inPipe[2];
	int outPipe[2];

	::pipe(inPipe);
	::pipe(outPipe);

	if (::fork())
	{
		::close(inPipe[0]);
		::close(outPipe[1]);

		inFile_ = inPipe[1];
		outFile_ = outPipe[0];

		mainLoop();
	}
	else
	{
		::close(inPipe[1]);
		::dup2(inPipe[0], STDIN_FILENO);

		::close(outPipe[0]);
		::dup2(outPipe[1], STDOUT_FILENO);

		::execlp("gdb", "gdb", "--interpreter=mi", binaryToDebug, nullptr);
		throw std::runtime_error("Failed to start debugger");
	}

}

void Debugger::mainLoop()
{
	static const size_t BUFSIZE = 4096;
	char buf[BUFSIZE];

	std::string line;

	for(;;)
	{
		int bytesRead = ::read(outFile_, buf, BUFSIZE);
		if (bytesRead <= 0)
		{
			return;
		}

		// read lines
		char* begin = buf;
		char* end = buf + bytesRead;
		while(begin != end)
		{
			char* n = std::find(begin, end, '\n');
			if (n == end)
			{
				// remove any whitespace at the end
				while(n != begin && *(n-1) == ' ')
					--n;
				line.append(begin, end);
				break;
			}
			else
			{
				while(n != begin && *(n-1) == ' ')
					--n;
				line.append(begin, n);
				processLine(line);
				line.clear();
				begin = n+1;
			}
		}

	}
}

std::string parseCString(const std::string& result, size_t& pos)
{
	if (result[pos] != '"')
		throw std::runtime_error("Error parsing " + result + ", Expceting \" at pos " + std::to_string(pos));

	std::string out;

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
	if (result[pos] != '[')
		throw std::runtime_error("Error parsing " + result + ", Expceting \" at pos " + std::to_string(pos));

	Result out;

	for(;;)
	{
		pos ++;
		auto v = parseValue(result, pos);
		out.push_back({{}, v});
		//std::cout << "tuple, got field=" << kv.first << ", string forward is: " << (result.c_str() + pos) << std::endl;
		pos++;
		if (result[pos] == ',')
		{
			continue;
		}
		else if (result[pos] == ']')
		{
			break;
		}
		throw std::runtime_error("Error parsing " + result + ", Expceting ',' or ']' at pos " + std::to_string(pos) + ", found " + std::string(1, result[pos]) + " instead");
	}
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

void Debugger::processLine(const std::string& line)
{
	//std::cout << line << std::endl;
	if (line.length() < 1)
		return;

	if (line == "(gdb)")
	{
		std::string reply = state_->processInput(notifications_, result_);
		if (!reply.empty())
		{
			::write(inFile_, reply.data(), reply.size());
		}
		notifications_.clear();
		result_.reset();
		return;
	}

	if (line[0] == '~')
	{
		sink_.debuggerOutput(std::string(line.begin()+1, line.end()));
		return;
	}

	if (line[0] == '@')
	{
		sink_.targetOutput(std::string(line.begin()+1, line.end()));
		return;
	}

	std::regex regexp("(\\d+)?([*+=^])([^,]+)(,(.+))?");
	std::smatch match;
	if (!std::regex_match(line, match, regexp))
	{
		std::cerr << "Failed to parse: " << line << std::endl;
		return;
	}

	std::string token = match.str(1);
	std::string typeChar = match.str(2);
	std::string resultClass = match.str(3);
	std::string result = match.str(5);

	InputRecord record;
	record.token = token.empty() ? 0 : std::stoi(token);
	record.type = typeChar[0];
	record.inputClass = resultClass;
	size_t pos = 0;
	record.result.push_back(parseResult(result, pos));

	if (record.type == '^')
		result_ = record;
	else
		notifications_.push_back(record);
}

}

