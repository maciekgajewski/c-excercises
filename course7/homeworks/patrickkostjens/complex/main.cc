#include "calculator.hh"

#include <boost/filesystem.hpp>
#include <string>
#include <dlfcn.h>
#include <vector>

namespace fs = boost::filesystem;

int main(int argc, char** argv)
{
	Calculator c;
	for (const auto& it : fs::directory_iterator(fs::path(".")))
	{
		if (it.path().extension() == ".so" || it.path().extension() == ".dylib")
		{
			std::string name = "./" + it.path().filename().string();
			void* module = ::dlopen(name.c_str(), RTLD_NOW);
			if (!module)
			{
				std::cerr << "Error loading module " << name << " : " << ::dlerror() << std::endl;
				continue;
			}
			plugin p = reinterpret_cast<plugin>(::dlsym(module, "execute"));
			if (!p)
			{
				std::cerr << "Symbol not found from file " << name << ", : " << ::dlerror() << std::endl;
				continue;
			}
			c.add_plugin(it.path().stem().string(), p);
		}
	}

	std::string line;
	while(true)
	{
		std::getline(std::cin, line);
		try
		{
			c.process_line(line);
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		c.print_status(std::cout);
	}
}
