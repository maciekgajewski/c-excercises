#include "calculator.hh"

#include <boost/filesystem.hpp>
#include <string>
#include <dlfcn.h>

namespace fs = boost::filesystem;

int main(int argc, char** argv)
{
	Calculator c;
	int plugin_count = 0;
	for (const auto& it : fs::directory_iterator(fs::path(".")))
		if (it.path().extension() == ".so" || it.path().extension() == ".dylib")
			plugin_count++;

	plugin *plugins = new plugin[plugin_count];
	plugin_count = 0;
	for (const auto& it : fs::directory_iterator(fs::path(".")))
	{
		if (it.path().extension() == ".so" || it.path().extension() == ".dylib")
		{
			void* module = dlopen(it.path().filename().c_str(), RTLD_NOW);
			plugins[plugin_count] = reinterpret_cast<plugin>(dlsym(module, "execute"));
			c.add_plugin(it.path().stem().string(), &plugins[plugin_count]);
			plugin_count++;
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
