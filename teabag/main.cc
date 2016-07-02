#include "debugger.hh"

#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <binary-file>" << std::endl;
		return 2;
	}

	Teabag::Debugger debugger;
	debugger.run(argv[0]);

	return 0;
}

