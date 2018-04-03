#pragma once

#include "plugin.h"

#include <unordered_map>
#include <string>

using PluginByName = std::unordered_map<std::string, Plugin>;

PluginByName LoadPlugins();
