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
			void* module = dlopen(it.path().filename().c_str(), RTLD_NOW);
			plugin p = reinterpret_cast<plugin>(dlsym(module, "execute"));
			std::shared_ptr<plugin> plugin_ptr = std::make_unique<plugin>(p);
			c.add_plugin(it.path().stem().string(), plugin_ptr);
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
