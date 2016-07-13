#include "debugger.hh"
#include "json_sink.hh"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <binary-file>" << std::endl;
		return 2;
	}

	Teabag::JsonSink sink(std::cout);
	Teabag::Debugger debugger(sink);
	debugger.run(argv[0]);



	return 0;
}

