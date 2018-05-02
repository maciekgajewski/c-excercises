#include "plugin_loader.h"

#include <boost/filesystem.hpp>
#include <vector>
#include <iostream>
#include <dlfcn.h>

namespace {

std::vector<std::string> GetPluginsNames()
{
  std::vector<std::string> pluginsNames;

  auto currentPath = boost::filesystem::path(".");
  for (const auto& entry : boost::filesystem::directory_iterator(currentPath))
  {
    const auto& path = entry.path();
    if (!boost::filesystem::is_directory(path) && path.extension() == ".so")
    {
      pluginsNames.push_back(entry.path().stem().string());
    }
  }

  return pluginsNames;
}

}

PluginByName LoadPlugins()
{
  PluginByName pluginByName;

  for (const auto& pluginName : GetPluginsNames())
  {
    auto filename = "./" + pluginName + ".so";

    void* pluginHandler = ::dlopen(filename.c_str(), RTLD_NOW);
    if (pluginHandler)
    {
      void* functionHandler = ::dlsym(pluginHandler, pluginName.c_str());
      if (functionHandler)
      {
        auto plugin = reinterpret_cast<Plugin>(functionHandler);
        pluginByName.emplace(pluginName, plugin);
      }
      else
      {
        std::cerr << "Could not find symbol in '" << filename << "' with the name '"
            << pluginName << "': " << ::dlerror() << std::endl;
      }
    }
    else
    {
      std::cerr << "Error loading plugin '" << pluginName << "': "
          << ::dlerror() << std::endl;
    }
  }

  return pluginByName;
}
