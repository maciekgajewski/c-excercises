#pragma once

#include "complex.h"
#include <stack>

namespace complex {
extern "C" char get_command_name();
extern "C" void invoke_command(std::stack<Complex>&);
}
